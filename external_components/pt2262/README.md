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

PT2262 is constant-period PWM: every pulse plus its gap lasts ~1624µs, so a
short pulse is followed by a long gap and a long pulse by a short gap. Each
tri-state symbol is TWO such pulses:

| Symbol | Encoding | Pulse Pattern |
|--------|----------|---------------|
| `0` | LOW | short pulse, long gap, short pulse, long gap |
| `1` | HIGH | long pulse, short gap, long pulse, short gap |
| `X` | FLOAT | long pulse, short gap, short pulse, long gap |
| `Z` | 4th state | short pulse, long gap, long pulse, short gap |

A frame is the 24 data pulses followed by a short sync pulse and a ~12ms sync
gap; frames are repeated back to back.

### Timing Parameters

Based on RTL_433 analysis of original remote:

```cpp
PULSE_SHORT = 420µs   // Short pulse, followed by GAP_LONG
PULSE_LONG  = 1216µs  // Long pulse, followed by GAP_SHORT
GAP_SHORT   = 408µs
GAP_LONG    = 1204µs
SYNC_GAP    = 12032µs // After the trailing short sync pulse
```

## Configuration

### Basic Setup

```yaml
# Configure the PT2262 transmitter
pt2262:
  id: rf_transmitter
  pin: GPIO4
  repeat: 5  # Frames per press (one press of the original remote = 5)
```

### Parameters

- **id** (Required): Component ID for referencing in actions
- **pin** (Required): GPIO pin connected to RF transmitter
- **repeat** (Optional, default=4, range 1-20): Number of frames per press

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

Each frame consists of:

1. **Data**: 12 tri-state symbols = 24 pulses, each pulse+gap ~1624µs
2. **Sync**: Short pulse (420µs) followed by a very long gap (12032µs)
3. **Repeat**: Frames sent back to back `repeat` times (default 4; this project uses 5)

### Watchdog Handling

- `InterruptLock` is held per frame for the data and sync pulse only (~40ms)
- It is released during the 12ms sync gap, which isn't timing-critical
- Total for 5 frames: ~257ms

### Example Transmission Timeline

For code `0X00Z1XZ00ZZ` (Red button):

```
Frame 1:
  [Symbol '0': 420µs HIGH, 1204µs LOW, 420µs HIGH, 1204µs LOW]
  [Symbol 'X': 1216µs HIGH, 408µs LOW, 420µs HIGH, 1204µs LOW]
  ... (10 more symbols)
  [SYNC: 420µs HIGH, 12032µs LOW]
Frame 2:
  [Same sequence...]
... (3 more frames)
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

Original remote, one press (`docs/buttons/BRIGHT.txt`). Note the single
~1624µs pulse period; a transmitter matching it should show the same gap mix:

```
Pulse width distribution:
 [ 0] count:   90,  width:  420 us (short)
 [ 1] count:   35,  width: 1216 us (long)

Gap width distribution:
 [ 0] count:   85,  width: 1204 us (long)
 [ 1] count:   35,  width:  408 us (short)
 [ 2] count:    4,  width: 12032 us (sync)
```

Before the 2026-10-17 fix this component produced the following. The pulses
matched, but the gaps did not (72 short / 77 long), which made the lights
respond only intermittently:

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
- Lock duration: ~40ms per frame
- Released during each sync gap

### Performance

- Frame time: ~51ms (39ms data + 12ms sync)
- Total with 5 repeats: ~257ms
- API warning: "took a long time" (expected and safe)
- No impact on device stability

## License

MIT License - See project root LICENSE file

## Credits

Developed for sauna LED light control via Home Assistant.
Timing parameters derived from RTL_433 analysis of original remote.
