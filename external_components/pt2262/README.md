# PT2262 Custom Component for ESPHome

A custom ESPHome component for transmitting PT2262/PT2272 encoded RF signals with proper tri-state encoding.

## Overview

This component implements the PT2262 remote control protocol, commonly used in 433MHz RF remotes for LED lights, garage doors, and other wireless devices. Unlike ESPHome's built-in `remote_transmitter`, this component:

- ✅ Properly encodes tri-state symbols as pulse pairs
- ✅ Sends tri-state codes directly (no binary conversion needed)
- ✅ Matches original remote timing exactly
- ✅ Avoids watchdog timeouts with proper interrupt handling
- ✅ Recognized by RTL_433 as "Generic-Remote"

## Tri-State Encoding

PT2262 uses 4-state tri-state encoding where each symbol is transmitted as TWO pulses:

| Symbol | Encoding | Pulse Pattern |
|--------|----------|---------------|
| `0` | LOW | short pulse, short gap, short pulse, long gap |
| `1` | HIGH | long pulse, short gap, long pulse, long gap |
| `X` | FLOAT | long pulse, short gap, short pulse, long gap |
| `Z` | 4th state | short pulse, short gap, long pulse, long gap |

### Timing Parameters

Based on RTL_433 analysis of original remote:

```cpp
PULSE_SHORT = 432µs   // Short pulse duration
PULSE_LONG  = 1232µs  // Long pulse duration
GAP_SHORT   = 392µs   // Short gap between pulses in a pair
GAP_LONG    = 1192µs  // Long gap after symbol complete
SYNC_PULSE  = 432µs   // Sync pulse (short)
SYNC_GAP    = 12020µs // Sync gap (very long)
```

## Configuration

### Basic Setup

```yaml
# Configure the PT2262 transmitter
pt2262:
  id: rf_transmitter
  pin: GPIO4
  repeat: 4  # Number of transmissions (match original remote)
```

### Parameters

- **id** (Required): Component ID for referencing in actions
- **pin** (Required): GPIO pin connected to RF transmitter
- **repeat** (Optional, default=4): Number of times to transmit each code

## Usage

### Button Example

```yaml
button:
  - platform: template
    name: "Power"
    on_press:
      - pt2262.send:
          id: rf_transmitter
          code: "0X00Z1XZ00Z0"  # Tri-state code as string
```

### Tri-State Code Format

- Codes are 12-character strings (typical for PT2262)
- Valid characters: `0`, `1`, `X`, `Z` (case-sensitive)
- Example: `0X00Z1XZ00ZZ` for Red button
- House code typically in first 8 characters
- Command code in last 4 characters

## How It Works

### Signal Structure

Each transmission consists of:

1. **Sync pulse**: Short pulse (432µs) followed by very long gap (12020µs)
2. **Symbol pairs**: Each tri-state symbol encoded as 2 pulses
3. **Trailing pulse**: Short pulse (432µs) followed by long gap (1192µs)
4. **Repeat**: Entire sequence repeated 6 times (configurable)

### Watchdog Handling

To prevent ESP32 watchdog timeouts:
- `InterruptLock` applied **per transmission** (~57ms each)
- `yield()` called between transmissions
- Total time: ~345ms for 6 transmissions (safe for watchdog)

### Example Transmission Timeline

For code `0X00Z1XZ00ZZ` (Red button):

```
Transmission 1:
  [SYNC: 432µs HIGH, 12020µs LOW]
  [Symbol '0': 432µs HIGH, 392µs LOW, 432µs HIGH, 1192µs LOW]
  [Symbol 'X': 1232µs HIGH, 392µs LOW, 432µs HIGH, 1192µs LOW]
  ... (10 more symbols)
  [TRAILING: 432µs HIGH, 1192µs LOW]

[yield()]

Transmission 2:
  [Same sequence...]

... (4 more transmissions)
```

## Verification

### RTL_433 Decoding

Successful transmission shows:

```
model     : Generic-Remote
House Code: 8313
Command   : 5
Tri-State : 0X00Z1XZ00ZZ
```

### Pulse Analysis

```
Pulse width distribution:
 [ 0] count:  107,  width:  436 us (short)
 [ 1] count:   48,  width: 1236 us (long)

Gap width distribution:
 [ 0] count:   72,  width:  392 us (short)
 [ 1] count:   77,  width: 1192 us (long)
 [ 2] count:    5,  width: 12028 us (sync)
```

## Component Files

- `pt2262.h` - Component class definition and timing constants
- `pt2262.cpp` - Implementation with pulse pair encoding
- `__init__.py` - ESPHome Python integration
- `action.h` - Template action for button integration

## Troubleshooting

### RTL_433 Shows Generic PWM Instead of Generic-Remote

**Cause**: Timing or encoding issue
**Fix**: Verify tri-state code format and timing constants

### Device Reboots After Button Press

**Cause**: Watchdog timeout (if still occurring)
**Fix**: Ensure `yield()` is called between transmissions and `InterruptLock` is scoped per transmission

### Wrong Tri-State Decoded

**Cause**: X/Z symbols swapped or 0/1 inverted
**Fix**: Verify encoding in `pt2262.cpp` matches:
- `0` = short/short
- `1` = long/long
- `X` = long/short
- `Z` = short/long

### Lights Don't Respond

**Possible causes**:
1. Wrong tri-state code - verify against original remote capture
2. Insufficient range - add antenna or increase repeat count
3. Incorrect timing - compare RTL_433 output with original

## Technical Notes

### Why Not Use Built-in remote_transmitter?

ESPHome's `remote_transmitter.transmit_rc_switch_raw` has limitations:
1. Sends flat binary sequences, not pulse pairs
2. Doesn't properly implement PT2262 tri-state structure
3. RTL_433 decodes it as generic PWM, not Generic-Remote
4. LED receivers don't recognize the signal

### Interrupt Handling

The component uses `InterruptLock` for precise timing but scopes it carefully:
- Lock duration: ~57ms per transmission
- Well under 300ms watchdog timeout
- `yield()` between transmissions keeps system responsive

### Performance

- Transmission time: ~57ms per code
- Total with 6 repeats: ~345ms
- API warning: "took a long time" (expected and safe)
- No impact on device stability

## License

MIT License - See project root LICENSE file

## Credits

Developed for sauna LED light control via Home Assistant.
Timing parameters derived from RTL_433 analysis of original remote.
