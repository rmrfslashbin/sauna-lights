# Home Assistant Entity Reference

**Device**: Sauna Lights 356F
**ESPHome Device Name**: `sauna-lights-356f`
**Purpose**: 433MHz RF transmitter for sauna LED light control

This document lists all entities exported to Home Assistant for dashboard creation.

---

## Button Entities (RF Commands)

All button entities trigger 433MHz RF transmissions to control the sauna LED lights. Service calls follow the pattern: `button.sauna_lights_<button_name>`

### Power & Brightness (4 buttons)

| Entity ID | Name | Icon | Function |
|-----------|------|------|----------|
| `button.sauna_lights_power` | Power | mdi:power | Toggle lights on/off |
| `button.sauna_lights_brightness_up` | Brightness Up | mdi:brightness-7 | Increase brightness |
| `button.sauna_lights_brightness_down` | Brightness Down | mdi:brightness-5 | Decrease brightness |
| `button.sauna_lights_fast_forward` | Fast Forward | mdi:fast-forward | Fast forward through modes |

### Primary Colors (4 buttons)

| Entity ID | Name | Icon | Function |
|-----------|------|------|----------|
| `button.sauna_lights_red` | Red | mdi:palette | Set solid red |
| `button.sauna_lights_green` | Green | mdi:palette | Set solid green |
| `button.sauna_lights_blue` | Blue | mdi:palette | Set solid blue |
| `button.sauna_lights_white` | White | mdi:palette | Set solid white |

### Color Variants - Red Tones (4 buttons)

| Entity ID | Name | Icon | Function |
|-----------|------|------|----------|
| `button.sauna_lights_r_1` | R+1 | mdi:palette-advanced | Red variant 1 |
| `button.sauna_lights_r_2` | R+2 | mdi:palette-advanced | Red variant 2 |
| `button.sauna_lights_r_3` | R+3 | mdi:palette-advanced | Red variant 3 |
| `button.sauna_lights_r_4` | R+4 | mdi:palette-advanced | Red variant 4 |

### Color Variants - Green Tones (4 buttons)

| Entity ID | Name | Icon | Function |
|-----------|------|------|----------|
| `button.sauna_lights_g_1` | G+1 | mdi:palette-advanced | Green variant 1 |
| `button.sauna_lights_g_2` | G+2 | mdi:palette-advanced | Green variant 2 |
| `button.sauna_lights_g_3` | G+3 | mdi:palette-advanced | Green variant 3 |
| `button.sauna_lights_g_4` | G+4 | mdi:palette-advanced | Green variant 4 |

### Color Variants - Blue Tones (4 buttons)

| Entity ID | Name | Icon | Function |
|-----------|------|------|----------|
| `button.sauna_lights_b_1` | B+1 | mdi:palette-advanced | Blue variant 1 |
| `button.sauna_lights_b_2` | B+2 | mdi:palette-advanced | Blue variant 2 |
| `button.sauna_lights_b_3` | B+3 | mdi:palette-advanced | Blue variant 3 |
| `button.sauna_lights_b_4` | B+4 | mdi:palette-advanced | Blue variant 4 |

### Color Variants - White Tones (4 buttons)

| Entity ID | Name | Icon | Function |
|-----------|------|------|----------|
| `button.sauna_lights_w_1` | W+1 | mdi:palette-advanced | White variant 1 (warm) |
| `button.sauna_lights_w_2` | W+2 | mdi:palette-advanced | White variant 2 |
| `button.sauna_lights_w_3` | W+3 | mdi:palette-advanced | White variant 3 |
| `button.sauna_lights_w_4` | W+4 | mdi:palette-advanced | White variant 4 (cool) |

### Color Adjustment (6 buttons)

| Entity ID | Name | Icon | Function |
|-----------|------|------|----------|
| `button.sauna_lights_r_up` | R-Up | mdi:arrow-up-bold | Increase red channel |
| `button.sauna_lights_r_dn` | R-Dn | mdi:arrow-down-bold | Decrease red channel |
| `button.sauna_lights_g_up` | G-Up | mdi:arrow-up-bold | Increase green channel |
| `button.sauna_lights_g_dn` | G-Dn | mdi:arrow-down-bold | Decrease green channel |
| `button.sauna_lights_b_up` | B-Up | mdi:arrow-up-bold | Increase blue channel |
| `button.sauna_lights_b_dn` | B-Dn | mdi:arrow-down-bold | Decrease blue channel |

### Speed Control (2 buttons)

| Entity ID | Name | Icon | Function |
|-----------|------|------|----------|
| `button.sauna_lights_quick` | Quick | mdi:speedometer | Increase effect speed |
| `button.sauna_lights_slow` | Slow | mdi:speedometer-slow | Decrease effect speed |

### DIY Presets (6 buttons)

| Entity ID | Name | Icon | Function |
|-----------|------|------|----------|
| `button.sauna_lights_diy1` | DIY1 | mdi:palette-outline | Custom preset 1 |
| `button.sauna_lights_diy2` | DIY2 | mdi:palette-outline | Custom preset 2 |
| `button.sauna_lights_diy3` | DIY3 | mdi:palette-outline | Custom preset 3 |
| `button.sauna_lights_diy4` | DIY4 | mdi:palette-outline | Custom preset 4 |
| `button.sauna_lights_diy5` | DIY5 | mdi:palette-outline | Custom preset 5 |
| `button.sauna_lights_diy6` | DIY6 | mdi:palette-outline | Custom preset 6 |

### Effect Modes (6 buttons)

| Entity ID | Name | Icon | Function |
|-----------|------|------|----------|
| `button.sauna_lights_auto` | Auto | mdi:autorenew | Auto color cycling |
| `button.sauna_lights_flash` | Flash | mdi:flash | Strobe effect |
| `button.sauna_lights_jump3` | Jump3 | mdi:skip-forward | Jump between 3 colors |
| `button.sauna_lights_jump7` | Jump7 | mdi:skip-forward | Jump between 7 colors |
| `button.sauna_lights_fade3` | Fade3 | mdi:gradient-vertical | Fade between 3 colors |
| `button.sauna_lights_fade7` | Fade7 | mdi:gradient-vertical | Fade between 7 colors |

**Total RF Buttons**: 44

---

## System Control Buttons (3 buttons)

| Entity ID | Name | Icon | Function | Category |
|-----------|------|------|----------|----------|
| `button.sauna_lights_restart` | Restart | mdi:restart | Restart ESP32 device | Config |
| `button.sauna_lights_factory_reset` | Factory Reset | mdi:factory | Reset to factory defaults (disabled by default) | Config |
| `button.sauna_lights_safe_mode_boot` | Safe Mode Boot | mdi:security | Boot into safe mode (disabled by default) | Config |

**Note**: Factory Reset and Safe Mode Boot are disabled by default to prevent accidental activation.

---

## Sensor Entities

### Numeric Sensors

| Entity ID | Name | Icon | Unit | Device Class | Function |
|-----------|------|------|------|--------------|----------|
| `sensor.sauna_lights_wifi_signal` | WiFi Signal | mdi:wifi | dBm | signal_strength | WiFi signal strength |
| `sensor.sauna_lights_uptime` | Uptime | mdi:clock-outline | s | duration | Device uptime in seconds |
| `sensor.sauna_lights_internal_temperature` | Internal Temperature | mdi:thermometer | °C | temperature | ESP32 internal temperature |

**Update Interval**: All sensors update every 60 seconds

---

## Text Sensor Entities

### Network Information

| Entity ID | Name | Icon | Function |
|-----------|------|------|----------|
| `sensor.sauna_lights_ip_address` | IP Address | mdi:ip-network | Device IP address |
| `sensor.sauna_lights_connected_ssid` | Connected SSID | mdi:wifi | WiFi network name |
| `sensor.sauna_lights_connected_bssid` | Connected BSSID | mdi:wifi-star | WiFi AP MAC address |
| `sensor.sauna_lights_mac_address` | MAC Address | mdi:network-outline | Device MAC address |

### Firmware Information

| Entity ID | Name | Icon | Category | Function |
|-----------|------|------|----------|----------|
| `sensor.sauna_lights_esphome_build_version` | ESPHome Build Version | mdi:numeric | Diagnostic | ESPHome version number |
| `sensor.sauna_lights_esphome_config_hash` | ESPHome Config Hash | mdi:fingerprint | Diagnostic | Configuration fingerprint |
| `sensor.sauna_lights_firmware_build_date` | Firmware Build Date | mdi:calendar-clock | Diagnostic | Date firmware was compiled |
| `sensor.sauna_lights_firmware_build_time` | Firmware Build Time | mdi:clock-outline | Diagnostic | Time firmware was compiled |

**Example Values**:
- ESPHome Build Version: `2026.1.3`
- ESPHome Config Hash: `0xf373cfc5`
- Firmware Build Date: `Feb 1 2026`
- Firmware Build Time: `16:05:05`

**Note**: These diagnostic entities are set once at boot and help identify the exact firmware build running on the device. The config hash changes when the YAML configuration is modified.

---

## Binary Sensor Entities

| Entity ID | Name | Icon | Device Class | Function |
|-----------|------|------|--------------|----------|
| `binary_sensor.sauna_lights_status` | Status | mdi:check-circle | connectivity | Online/offline status |

**States**:
- `on` = Device connected
- `off` = Device disconnected

---

## Light Entities

| Entity ID | Name | Function |
|-----------|------|----------|
| `light.sauna_lights_status_led` | Status LED | Onboard RGB LED (GPIO38) - indicates connection status |

**Note**: This controls the ESP32 onboard LED, NOT the sauna lights. Sauna lights are controlled via RF button entities.

---

## Dashboard Recommendations

### Suggested Card Layouts

#### Primary Control Card
**Purpose**: Quick access to most-used functions
**Entities**:
- `button.sauna_lights_power`
- `button.sauna_lights_brightness_up`
- `button.sauna_lights_brightness_down`
- `button.sauna_lights_red`
- `button.sauna_lights_green`
- `button.sauna_lights_blue`
- `button.sauna_lights_white`

#### Color Palette Card
**Purpose**: Color selection and variants
**Sections**:
1. Primary colors (Red, Green, Blue, White)
2. Red tones (R+1-4)
3. Green tones (G+1-4)
4. Blue tones (B+1-4)
5. White tones (W+1-4)

#### Effects & Presets Card
**Purpose**: Dynamic effects and custom presets
**Entities**:
- Auto, Flash
- Jump3, Jump7
- Fade3, Fade7
- DIY1-6
- Quick/Slow speed controls

#### Advanced Controls Card
**Purpose**: Fine-tuning color channels
**Entities**:
- R-Up/Dn, G-Up/Dn, B-Up/Dn

#### Device Status Card
**Purpose**: Monitor ESP32 device health
**Entities**:
- `binary_sensor.sauna_lights_status`
- `sensor.sauna_lights_wifi_signal`
- `sensor.sauna_lights_uptime`
- `sensor.sauna_lights_internal_temperature`
- `sensor.sauna_lights_ip_address`
- `sensor.sauna_lights_esphome_build_version`
- `sensor.sauna_lights_firmware_build_date`
- `sensor.sauna_lights_firmware_build_time`

#### System Management Card (Collapsed by default)
**Purpose**: Device maintenance
**Entities**:
- `button.sauna_lights_restart`
- `button.sauna_lights_factory_reset` (show_state: false)
- `button.sauna_lights_safe_mode_boot` (show_state: false)

---

## Entity Naming Convention

All entities follow the pattern: `<domain>.sauna_lights_<entity_name>`

**Domains**:
- `button.*` - RF transmit buttons and system controls
- `sensor.*` - Numeric sensors (WiFi, uptime, temperature) and ESPHome
  `text_sensor`s (IP, version, etc.); HA has no separate text_sensor domain
- `binary_sensor.*` - On/off state sensors (status)
- `light.*` - Onboard RGB status LED

---

## Technical Notes

### RF Transmission
- **Protocol**: PT2262 tri-state encoding
- **Frequency**: 433.92 MHz
- **Transmissions per button press**: 4 (matches original remote)
- **GPIO**: GPIO4
- **Range**: ~10-30 feet (varies with environment)

### Button Press Behavior
- Each button press triggers a single RF transmission burst
- No visual feedback on the ESP32 device (RF transmission only)
- Buttons are momentary (no state retention)

### Update Intervals
- **Sensors**: 60 seconds
- **Text Sensors**: Static or event-driven (IP updates on network change)
- **Binary Sensor**: Real-time status updates

### Areas/Rooms
Suggested Home Assistant area: **Sauna** or **Bathroom**

---

## Automation Examples

### Turn on lights when entering sauna
```yaml
automation:
  - alias: "Sauna Lights - Auto On"
    trigger:
      - platform: state
        entity_id: binary_sensor.sauna_door
        to: "on"
    action:
      - action: button.press
        target:
          entity_id: button.sauna_lights_power
```

### Dim lights at night
```yaml
automation:
  - alias: "Sauna Lights - Night Mode"
    trigger:
      - platform: time
        at: "22:00:00"
    condition:
      - condition: state
        entity_id: binary_sensor.sauna_lights_status
        state: "on"
    action:
      - action: button.press
        target:
          entity_id: button.sauna_lights_brightness_down
      - delay:
          seconds: 1
      - action: button.press
        target:
          entity_id: button.sauna_lights_brightness_down
```

### Cycle through colors
```yaml
script:
  sauna_color_cycle:
    sequence:
      - action: button.press
        target:
          entity_id: button.sauna_lights_red
      - delay:
          seconds: 5
      - action: button.press
        target:
          entity_id: button.sauna_lights_green
      - delay:
          seconds: 5
      - action: button.press
        target:
          entity_id: button.sauna_lights_blue
```

---

## Entity Count Summary

| Type | Count | Category |
|------|-------|----------|
| RF Button Entities | 44 | Light Control |
| System Buttons | 3 | Device Management |
| Numeric Sensors | 3 | Monitoring |
| Text Sensors | 8 | Information |
| Binary Sensors | 1 | Status |
| Light Entities | 1 | ESP32 Status |
| **Total** | **60** | **All Entities** |

---

**Document Version**: 1.0
**Last Updated**: 2026-02-01
**ESPHome Version**: 2026.1.3
**Firmware Build**: Feb 1 2026 16:04:34
