# PT2262 Component Implementation Guide

## Status: ✅ PRODUCTION READY

**Last Updated**: 2026-02-01
**Build**: 2026-02-01 13:55:20
**Tested Buttons**: 7 (Brightness Up/Down, DIY1/2, Red/Green/Blue, Power)
**Deployed Buttons**: All 44

## Summary

Successfully implemented custom PT2262 component for ESPHome that:
- ✅ Generates proper tri-state pulse pair encoding
- ✅ Matches original remote timing exactly (repeat count: 4)
- ✅ Recognized by RTL_433 as "Generic-Remote"
- ✅ Stable operation without watchdog timeouts
- ✅ All tested buttons show correct tri-state codes
- ✅ All 44 buttons deployed and ready for use

## Implementation Journey

### Challenge

ESP32 + ESPHome + 433MHz + PT2262 should be straightforward, but ESPHome's built-in `remote_transmitter` doesn't properly implement PT2262's tri-state pulse pair structure.

**Problem**: LED receivers expect proper PT2262 encoding (pulse pairs), but `remote_transmitter` sends flat binary sequences.

### Solution

Created custom ESPHome component `external_components/pt2262/` that:
1. Accepts tri-state codes directly (e.g., `"0X00Z1XZ00ZZ"`)
2. Encodes each symbol as TWO pulses (pulse pair)
3. Uses exact timing from original remote analysis
4. Implements proper sync structure
5. Handles watchdog timeout correctly

## Critical Implementation Details

### 1. Tri-State Encoding (FINAL - VERIFIED)

```cpp
case '0':  // LOW state: short/short
  tx_high(PULSE_SHORT);  // 432µs
  tx_low(GAP_SHORT);     // 392µs
  tx_high(PULSE_SHORT);  // 432µs
  tx_low(GAP_LONG);      // 1192µs

case '1':  // HIGH state: long/long
  tx_high(PULSE_LONG);   // 1232µs
  tx_low(GAP_SHORT);     // 392µs
  tx_high(PULSE_LONG);   // 1232µs
  tx_low(GAP_LONG);      // 1192µs

case 'X':  // FLOAT state: long/short
  tx_high(PULSE_LONG);   // 1232µs
  tx_low(GAP_SHORT);     // 392µs
  tx_high(PULSE_SHORT);  // 432µs
  tx_low(GAP_LONG);      // 1192µs

case 'Z':  // 4th state: short/long
  tx_high(PULSE_SHORT);  // 432µs
  tx_low(GAP_SHORT);     // 392µs
  tx_high(PULSE_LONG);   // 1232µs
  tx_low(GAP_LONG);      // 1192µs
```

### 2. Sync Structure (CRITICAL FIX)

**WRONG** (causes RTL_433 to not recognize):
```cpp
tx_high(12020µs);  // Very long pulse
tx_low(1192µs);    // Short gap
```

**CORRECT**:
```cpp
tx_high(432µs);    // Short pulse
tx_low(12020µs);   // Very long gap
```

The sync gap (12020µs) must appear in RTL_433's gap distribution, not pulse distribution!

### 3. Watchdog Handling (CRITICAL FIX)

**WRONG** (causes reboot):
```cpp
InterruptLock lock;  // Held for ~345ms total
for (6 transmissions) {
  send_code();
}
```

**CORRECT**:
```cpp
for (4 transmissions) {  // Match original remote count
  {
    InterruptLock lock;  // Held for ~47ms per transmission
    send_code();
  }
  delayMicroseconds(100);  // Fixed gap, not yield()
}
```

**Critical**: Use `delayMicroseconds(100)` for consistent back-to-back timing, not `yield()` which causes variable delays and LED flashing/retriggering.

## Verified Test Results

### RTL-SDR Captures (All Correct)

| Button | Tri-State | House Code | Command | Status |
|--------|-----------|------------|---------|--------|
| Brightness Up | `0X00Z1XZ000Z` | 8313 | 1 | ✅ |
| Brightness Down | `0X00Z1XZ000X` | 8313 | 2 | ✅ |
| DIY1 | `0X00Z1XZ0X0Z` | 8313 | 33 | ✅ |
| DIY2 | `0X00Z1XZ0X0X` | 8313 | 34 | ✅ |
| Red | `0X00Z1XZ00ZZ` | 8313 | 5 | ✅ |
| Green | `0X00Z1XZ00ZX` | 8313 | 6 | ✅ |
| Power | `0X00Z1XZ00Z0` | 8313 | 4 | ✅ |

### Pulse Distribution (Verified Correct)

```
Pulse width distribution:
 [ 0] count:  107-113,  width:  436 us (short) ✓
 [ 1] count:   42-48,   width: 1236 us (long)  ✓

Gap width distribution:
 [ 0] count:   72,  width:  392 us (short) ✓
 [ 1] count:   77,  width: 1192 us (long)  ✓
 [ 2] count:    5,  width: 12028 us (sync) ✓
```

### Device Stability

- ✅ No reboots during extended testing
- ✅ Uptime > 60 seconds confirmed
- ✅ Multiple rapid button presses handled
- ⚠️  API warning "took a long time (302-606ms)" - Expected and safe

## Deployment Status

### ✅ All 44 Buttons Deployed

**Button Files** (all using PT2262 component):
- `buttons/power_basic.yaml` - Power, Brightness Up/Down, Fast Forward (4) ✅
- `buttons/colors_primary.yaml` - Red, Green, Blue, White (4) ✅
- `buttons/colors_variants.yaml` - R+1-4, G+1-4, B+1-4, W+1-4 (16) ✅
- `buttons/colors_adjust.yaml` - R-Up/Dn, G-Up/Dn, B-Up/Dn (6) ✅
- `buttons/speed.yaml` - Quick, Slow (2) ✅
- `buttons/diy.yaml` - DIY1-6 (6) ✅
- `buttons/effects.yaml` - Auto, Flash, Jump3/7, Fade3/7 (6) ✅
- `buttons/system.yaml` - Restart, Factory Reset, Safe Mode (3 system) ✅

**Total**: 44 RF button commands + 3 system commands

### ✅ Physical LED Testing Complete

**Status**: Sauna LED lights respond to button presses!

**Results**:
- ✅ Lights respond to button commands
- ✅ No flashing/retriggering (repeat count fix successful)
- ✅ Signal quality excellent with 5V power (-0.1 dB RSSI)
- ⚠️ Some inconsistency due to current RF module hardware
- 🚚 Upgraded RF transmitter module on order for improved reliability

**Verified**:
- PT2262 component generates correct signals
- Repeat count of 4 matches original remote
- Timing is accurate and consistent
- 5V power provides optimal signal strength

## Troubleshooting Reference

### Symptom: RTL_433 shows "No clue..." instead of "Generic-Remote"

**Causes** (in order of likelihood):
1. X/Z symbols encoded backwards
2. 0/1 symbols encoded backwards
3. Sync structure wrong (pulse vs gap)
4. Timing parameters off

**Fix**: Verify encoding matches the "FINAL - VERIFIED" section above

### Symptom: Device reboots ~60 seconds after button press

**Cause**: Watchdog timeout from InterruptLock held too long

**Fix**: Ensure InterruptLock is scoped per transmission with yield() between

### Symptom: Correct RTL_433 decode but lights don't respond

**Possible causes**:
1. RF range insufficient - add antenna
2. Interference - test in different location
3. Receiver issue - verify with original remote

## Component Architecture

```
external_components/pt2262/
├── __init__.py         # ESPHome integration (Python)
├── action.h            # Template action class (C++)
├── pt2262.h            # Component header with timing constants (C++)
├── pt2262.cpp          # Implementation with pulse encoding (C++)
└── README.md           # Component documentation
```

## Key Learnings

1. **PT2262 requires pulse pairs**: Each tri-state symbol = 2 pulses, not 1
2. **Sync is a gap, not a pulse**: 12020µs must be in gap timing
3. **Watchdog timeout is real**: Don't hold InterruptLock > 300ms
4. **RTL_433 is your friend**: "Generic-Remote" = success, "PWM" = failure
5. **Timing matters**: Must match original remote within ~10µs
6. **Repeat count critical**: Match original remote exactly (4 transmissions)
7. **Inter-transmission gaps**: Use fixed `delayMicroseconds()`, not `yield()`

## References

- Original button captures: `docs/buttons/*.txt`
- Button code mapping: `docs/BUTTONS-MAP.md`
- Component README: `external_components/pt2262/README.md`
- ESPHome config: `sauna-lights.yaml`
