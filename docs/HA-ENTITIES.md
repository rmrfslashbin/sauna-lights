# Home Assistant Entity Reference

**Device**: Sauna Lights 356F
**ESPHome Device Name**: `sauna-lights-356f`
**Purpose**: 433MHz RF transmitter for sauna LED light control

This document lists all entities exported to Home Assistant for dashboard creation.

---

## Button Entities (RF Commands)

All button entities trigger 433MHz RF transmissions to control the sauna LED lights. Service calls follow the pattern: `button.sauna_lights_356f_<button_name>`

### Power & Brightness (4 buttons)

| Entity ID | Name | Icon | Function |
|-----------|------|------|----------|
| `button.sauna_lights_356f_power` | Power | mdi:power | Toggle lights on/off |
| `button.sauna_lights_356f_brightness_up` | Brightness Up | mdi:brightness-7 | Increase brightness |
| `button.sauna_lights_356f_brightness_down` | Brightness Down | mdi:brightness-5 | Decrease brightness |
| `button.sauna_lights_356f_fast_forward` | Fast Forward | mdi:fast-forward | Fast forward effect sequence |

### Primary Colors (4 buttons)

| Entity ID | Name | Icon | Function |
|-----------|------|------|----------|
| `button.sauna_lights_356f_red` | Red | mdi:palette | Set solid red |
| `button.sauna_lights_356f_green` | Green | mdi:palette | Set solid green |
| `button.sauna_lights_356f_blue` | Blue | mdi:palette | Set solid blue |
| `button.sauna_lights_356f_white` | White | mdi:palette | Set solid white |

### Color Variants - Red Tones (4 buttons)

| Entity ID | Name | Icon | Function |
|-----------|------|------|----------|
| `button.sauna_lights_356f_r_plus_1` | R+1 | mdi:palette-advanced | Red variant 1 |
| `button.sauna_lights_356f_r_plus_2` | R+2 | mdi:palette-advanced | Red variant 2 |
| `button.sauna_lights_356f_r_plus_3` | R+3 | mdi:palette-advanced | Red variant 3 |
| `button.sauna_lights_356f_r_plus_4` | R+4 | mdi:palette-advanced | Red variant 4 |

### Color Variants - Green Tones (4 buttons)

| Entity ID | Name | Icon | Function |
|-----------|------|------|----------|
| `button.sauna_lights_356f_g_plus_1` | G+1 | mdi:palette-advanced | Green variant 1 |
| `button.sauna_lights_356f_g_plus_2` | G+2 | mdi:palette-advanced | Green variant 2 |
| `button.sauna_lights_356f_g_plus_3` | G+3 | mdi:palette-advanced | Green variant 3 |
| `button.sauna_lights_356f_g_plus_4` | G+4 | mdi:palette-advanced | Green variant 4 |

### Color Variants - Blue Tones (4 buttons)

| Entity ID | Name | Icon | Function |
|-----------|------|------|----------|
| `button.sauna_lights_356f_b_plus_1` | B+1 | mdi:palette-advanced | Blue variant 1 |
| `button.sauna_lights_356f_b_plus_2` | B+2 | mdi:palette-advanced | Blue variant 2 |
| `button.sauna_lights_356f_b_plus_3` | B+3 | mdi:palette-advanced | Blue variant 3 |
| `button.sauna_lights_356f_b_plus_4` | B+4 | mdi:palette-advanced | Blue variant 4 |

### Color Variants - White Tones (4 buttons)

| Entity ID | Name | Icon | Function |
|-----------|------|------|----------|
| `button.sauna_lights_356f_w_plus_1` | W+1 | mdi:palette-advanced | White variant 1 (warm) |
| `button.sauna_lights_356f_w_plus_2` | W+2 | mdi:palette-advanced | White variant 2 |
| `button.sauna_lights_356f_w_plus_3` | W+3 | mdi:palette-advanced | White variant 3 |
| `button.sauna_lights_356f_w_plus_4` | W+4 | mdi:palette-advanced | White variant 4 (cool) |

### Color Adjustment (6 buttons)

| Entity ID | Name | Icon | Function |
|-----------|------|------|----------|
| `button.sauna_lights_356f_r_up` | R-Up | mdi:arrow-up-bold | Increase red channel |
| `button.sauna_lights_356f_r_dn` | R-Dn | mdi:arrow-down-bold | Decrease red channel |
| `button.sauna_lights_356f_g_up` | G-Up | mdi:arrow-up-bold | Increase green channel |
| `button.sauna_lights_356f_g_dn` | G-Dn | mdi:arrow-down-bold | Decrease green channel |
| `button.sauna_lights_356f_b_up` | B-Up | mdi:arrow-up-bold | Increase blue channel |
| `button.sauna_lights_356f_b_dn` | B-Dn | mdi:arrow-down-bold | Decrease blue channel |

### Speed Control (2 buttons)

| Entity ID | Name | Icon | Function |
|-----------|------|------|----------|
| `button.sauna_lights_356f_quick` | Quick | mdi:speedometer | Increase effect speed |
| `button.sauna_lights_356f_slow` | Slow | mdi:speedometer-slow | Decrease effect speed |

### DIY Presets (6 buttons)

| Entity ID | Name | Icon | Function |
|-----------|------|------|----------|
| `button.sauna_lights_356f_diy1` | DIY1 | mdi:palette-outline | Custom preset 1 |
| `button.sauna_lights_356f_diy2` | DIY2 | mdi:palette-outline | Custom preset 2 |
| `button.sauna_lights_356f_diy3` | DIY3 | mdi:palette-outline | Custom preset 3 |
| `button.sauna_lights_356f_diy4` | DIY4 | mdi:palette-outline | Custom preset 4 |
| `button.sauna_lights_356f_diy5` | DIY5 | mdi:palette-outline | Custom preset 5 |
| `button.sauna_lights_356f_diy6` | DIY6 | mdi:palette-outline | Custom preset 6 |

### Effect Modes (6 buttons)

| Entity ID | Name | Icon | Function |
|-----------|------|------|----------|
| `button.sauna_lights_356f_auto` | Auto | mdi:autorenew | Auto color cycling |
| `button.sauna_lights_356f_flash` | Flash | mdi:flash | Strobe effect |
| `button.sauna_lights_356f_jump3` | Jump3 | mdi:skip-forward | Jump between 3 colors |
| `button.sauna_lights_356f_jump7` | Jump7 | mdi:skip-forward | Jump between 7 colors |
| `button.sauna_lights_356f_fade3` | Fade3 | mdi:gradient-vertical | Fade between 3 colors |
| `button.sauna_lights_356f_fade7` | Fade7 | mdi:gradient-vertical | Fade between 7 colors |

**Total RF Buttons**: 44

---

## System Control Buttons (3 buttons)

| Entity ID | Name | Icon | Function | Category |
|-----------|------|------|----------|----------|
| `button.sauna_lights_356f_restart` | Restart | mdi:restart | Restart ESP32 device | Config |
| `button.sauna_lights_356f_factory_reset` | Factory Reset | mdi:factory | Reset to factory defaults | Config |
| `button.sauna_lights_356f_safe_mode_boot` | Safe Mode Boot | mdi:security | Boot into safe mode | Config |

**Note**: Factory Reset and Safe Mode Boot are disabled by default to prevent accidental activation.

---

## Sensor Entities

### Numeric Sensors

| Entity ID | Name | Icon | Unit | Device Class | Function |
|-----------|------|------|------|--------------|----------|
| `sensor.sauna_lights_356f_wifi_signal` | WiFi Signal | mdi:wifi | dBm | signal_strength | WiFi signal strength |
| `sensor.sauna_lights_356f_uptime` | Uptime | mdi:clock-outline | s | duration | Device uptime in seconds |
| `sensor.sauna_lights_356f_internal_temperature` | Internal Temperature | mdi:thermometer | °C | temperature | ESP32 internal temperature |

**Update Interval**: All sensors update every 60 seconds

---

## Text Sensor Entities

### Network Information

| Entity ID | Name | Icon | Function |
|-----------|------|------|----------|
| `text_sensor.sauna_lights_356f_ip_address` | IP Address | mdi:ip-network | Device IP address |
| `text_sensor.sauna_lights_356f_connected_ssid` | Connected SSID | mdi:wifi | WiFi network name |
| `text_sensor.sauna_lights_356f_connected_bssid` | Connected BSSID | mdi:wifi-star | WiFi AP MAC address |
| `text_sensor.sauna_lights_356f_mac_address` | MAC Address | mdi:network-outline | Device MAC address |

### Firmware Information

| Entity ID | Name | Icon | Function |
|-----------|------|------|----------|
| `text_sensor.sauna_lights_356f_esphome_version` | ESPHome Version | mdi:code-tags | ESPHome version + config hash |
| `text_sensor.sauna_lights_356f_firmware_build_time` | Firmware Build Time | mdi:clock-check-outline | Firmware compilation timestamp |

**Example Values**:
- ESPHome Version: `2026.1.3 (config hash 0xd758464d)`
- Firmware Build Time: `Feb  1 2026 16:04:34`

---

## Binary Sensor Entities

| Entity ID | Name | Icon | Device Class | Function |
|-----------|------|------|--------------|----------|
| `binary_sensor.sauna_lights_356f_status` | Status | mdi:check-circle | connectivity | Online/offline status |

**States**:
- `on` = Device connected
- `off` = Device disconnected

---

## Light Entities

| Entity ID | Name | Function |
|-----------|------|----------|
| `light.sauna_lights_356f_status_led` | Status LED | Onboard RGB LED (GPIO38) - indicates connection status |

**Note**: This controls the ESP32 onboard LED, NOT the sauna lights. Sauna lights are controlled via RF button entities.

---

## Dashboard Recommendations

### Suggested Card Layouts

#### Primary Control Card
**Purpose**: Quick access to most-used functions
**Entities**:
- `button.sauna_lights_356f_power`
- `button.sauna_lights_356f_brightness_up`
- `button.sauna_lights_356f_brightness_down`
- `button.sauna_lights_356f_red`
- `button.sauna_lights_356f_green`
- `button.sauna_lights_356f_blue`
- `button.sauna_lights_356f_white`

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
- `binary_sensor.sauna_lights_356f_status`
- `sensor.sauna_lights_356f_wifi_signal`
- `sensor.sauna_lights_356f_uptime`
- `sensor.sauna_lights_356f_internal_temperature`
- `text_sensor.sauna_lights_356f_ip_address`
- `text_sensor.sauna_lights_356f_firmware_build_time`

#### System Management Card (Collapsed by default)
**Purpose**: Device maintenance
**Entities**:
- `button.sauna_lights_356f_restart`
- `button.sauna_lights_356f_factory_reset` (show_state: false)
- `button.sauna_lights_356f_safe_mode_boot` (show_state: false)

---

## Entity Naming Convention

All entities follow the pattern: `<domain>.sauna_lights_356f_<entity_name>`

**Domains**:
- `button.*` - RF transmit buttons and system controls
- `sensor.*` - Numeric sensors (WiFi, uptime, temperature)
- `text_sensor.*` - String-based sensors (IP, version, etc.)
- `binary_sensor.*` - On/off state sensors (status)
- `light.*` - Light controls (status LED)

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
      - service: button.press
        target:
          entity_id: button.sauna_lights_356f_power
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
        entity_id: binary_sensor.sauna_lights_356f_status
        state: "on"
    action:
      - service: button.press
        target:
          entity_id: button.sauna_lights_356f_brightness_down
      - delay:
          seconds: 1
      - service: button.press
        target:
          entity_id: button.sauna_lights_356f_brightness_down
```

### Cycle through colors
```yaml
script:
  sauna_color_cycle:
    sequence:
      - service: button.press
        target:
          entity_id: button.sauna_lights_356f_red
      - delay:
          seconds: 5
      - service: button.press
        target:
          entity_id: button.sauna_lights_356f_green
      - delay:
          seconds: 5
      - service: button.press
        target:
          entity_id: button.sauna_lights_356f_blue
```

---

## Entity Count Summary

| Type | Count | Category |
|------|-------|----------|
| RF Button Entities | 44 | Light Control |
| System Buttons | 3 | Device Management |
| Numeric Sensors | 3 | Monitoring |
| Text Sensors | 6 | Information |
| Binary Sensors | 1 | Status |
| Light Entities | 1 | ESP32 Status |
| **Total** | **58** | **All Entities** |

---

**Document Version**: 1.0
**Last Updated**: 2026-02-01
**ESPHome Version**: 2026.1.3
**Firmware Build**: Feb 1 2026 16:04:34
