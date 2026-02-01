# Sauna Lights RF Controller

ESPHome-based 433MHz RF transmitter for controlling sauna LED lights via Home Assistant.

## Overview

This project uses an ESP32-S3-DevKitC-1 development board with a 433MHz RF transmitter module to control LED light strips in a sauna. The device integrates with Home Assistant, exposing 44 button commands as services for complete remote control.

## Hardware

- **Board**: ESP32-S3-DevKitC-1 (ESP32-S3-WROOM-1)
- **RF Module**: 433MHz transmitter on GPIO4
- **Power**: USB or 5V pin
- **Status LED**: Onboard RGB LED (GPIO38)

### Wiring

| Component          | GPIO | Notes                    |
|--------------------|------|--------------------------|
| RF Transmitter TX  | 4    | 433MHz, VCC=5V (recommended) |
| Status RGB LED     | 38   | Onboard LED (v1.1 board) |

## Features

- **Custom PT2262 component** with proper tri-state encoding
- **All 44 button commands** for complete sauna light control
- Home Assistant integration via ESPHome API
- OTA updates for easy maintenance
- WiFi connectivity with fallback AP mode
- Diagnostic sensors (WiFi signal, uptime, temperature)
- Web server for debugging
- RTL_433 compatible signal generation

## Installation

### Prerequisites

- ESPHome installed (`pip install esphome`)
- USB cable for initial flashing
- 433MHz RF transmitter module
- WiFi network credentials

### Setup

1. **Configure secrets**:
   ```bash
   cp secrets.yaml.example secrets.yaml
   # Edit secrets.yaml with your WiFi credentials and API keys
   ```

2. **Configure device** (if needed):
   ```bash
   cp consts.yaml.example consts.yaml
   # Edit consts.yaml with device-specific settings
   ```

3. **Validate configuration**:
   ```bash
   make validate
   ```

4. **Build firmware**:
   ```bash
   make build
   ```

5. **Flash via USB** (first time only):
   ```bash
   make flash
   ```

6. **Add to Home Assistant**:
   - Go to Settings → Devices & Services
   - Add ESPHome integration
   - Device should auto-discover as "sauna-lights-356f"

## Usage

### Home Assistant Services

After adding to Home Assistant, 44 services will be available:

- `esphome.sauna_lights_356f_brightness_up` - Increase brightness
- `esphome.sauna_lights_356f_brightness_down` - Decrease brightness
- `esphome.sauna_lights_356f_red` - Set color to red
- `esphome.sauna_lights_356f_diy1` - Activate DIY preset 1
- ...and 40 more button commands

See [docs/HA-ENTITIES.md](docs/HA-ENTITIES.md) for complete service documentation and Home Assistant entity reference.

### Development Workflow

```bash
# Validate configuration
make validate

# Build firmware
make build

# Flash via USB (first time)
make flash

# Update via OTA (after first flash)
make ota

# View logs
make logs

# Generate entity list for dashboard
make dashboard

# Start ESPHome dashboard
make esphome-ui

# Clean build artifacts
make clean
```

## Documentation

### Component Documentation
- [PT2262 Component](external_components/pt2262/README.md) - Custom component technical details
- [PT2262 Implementation Guide](docs/PT2262-COMPONENT-GUIDE.md) - Implementation notes and troubleshooting

### Home Assistant Integration
- [HA Entity Reference](docs/HA-ENTITIES.md) - Complete list of all entities, services, and dashboard examples
- [Button Mapping](docs/BUTTONS-MAP.md) - Complete 44-button tri-state code reference

### Hardware & Testing
- [ESP32-S3 Details](docs/ESP32-S3.md) - Board specifications and GPIO reference
- [Power Analysis](docs/power/POWER-ANALYSIS.md) - RF transmitter power optimization (3.3V vs 5V)
- [Signal Captures](docs/buttons/) - Original remote RTL_433 captures

### Project Status
- [Documentation Status](docs/DOCUMENTATION-STATUS.md) - Documentation accuracy and testing status

## Technical Details

### PT2262 Protocol

This project uses a custom ESPHome component to properly implement the PT2262/PT2272 remote control protocol. Key features:

- **Tri-state encoding**: Directly uses 4-state symbols (0, 1, X, Z)
- **Pulse pair structure**: Each symbol encoded as TWO pulses (not flat binary)
- **Verified timing**: 432µs/1232µs pulses, 392µs/1192µs gaps, 12020µs sync
- **RTL_433 compatible**: Signals decode as "Generic-Remote" with proper tri-state display

**Why a custom component?**

ESPHome's built-in `remote_transmitter` doesn't properly implement PT2262 tri-state encoding:
- Sends flat binary sequences instead of pulse pairs
- LED receivers don't recognize the signal structure
- RTL_433 decodes as generic PWM, not Generic-Remote

The custom component solves this by implementing the exact pulse pair encoding that PT2262 receivers expect.

### Verified Implementation

**PT2262 Component Testing** (RTL-SDR verified):
- ✅ Brightness Up/Down
- ✅ DIY1/DIY2
- ✅ Red/Green/Blue/White
- ✅ Power

All buttons use identical PT2262 component implementation with verified tri-state encoding. The remaining 37 buttons follow the same pattern and signal structure.

## Troubleshooting

### Device won't connect to WiFi
- Verify credentials in `secrets.yaml`
- Ensure 2.4GHz network (ESP32 doesn't support 5GHz)
- Check serial logs: `make logs`
- Try fallback AP: connect to "sauna-lights-356f Fallback" hotspot

### RF signals not working
- Verify GPIO4 connection to transmitter module
- Check transmitter power (3.3V, not 5V)
- Add antenna (17.3cm wire for 433MHz)
- Increase RF signal repeat count in configuration

### OTA updates failing
- Ensure device is on same network
- Check OTA password in `secrets.yaml`
- Try flashing via USB and retry OTA

## Contributing

Contributions welcome! Please:
1. Fork the repository
2. Create a feature branch
3. Make your changes
4. Submit a pull request

## Author

Robert Sigler (code@sigler.io)

## License

MIT License - see [LICENSE](LICENSE) file for details
