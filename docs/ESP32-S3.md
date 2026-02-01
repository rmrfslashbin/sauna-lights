# ESP32-S3-DevKitC-1 Development Board - Implementation Reference

> **Manufacturer:** Espressif Systems | **Version:** v1.1 | **Release:** master

This document provides a complete implementation reference for the ESP32-S3-DevKitC-1 development board, an entry-level development platform for ESP32-S3 series Wi-Fi + Bluetooth Low Energy applications.

---

## Table of Contents

1. [Board Overview](#1-board-overview)
2. [Hardware Specifications](#2-hardware-specifications)
3. [Module Variants](#3-module-variants)
4. [Pinout Reference](#4-pinout-reference)
5. [Power Supply](#5-power-supply)
6. [Getting Started](#6-getting-started)
7. [Component Description](#7-component-description)
8. [Hardware Considerations](#8-hardware-considerations)
9. [Related Documentation](#9-related-documentation)

---

## 1. Board Overview

### 1.1 Description

The ESP32-S3-DevKitC-1 is an entry-level development board equipped with one of the following modules:
- **ESP32-S3-WROOM-1** (PCB antenna)
- **ESP32-S3-WROOM-1U** (external antenna connector)
- **ESP32-S3-WROOM-2** (PCB antenna, higher memory)

These are general-purpose Wi-Fi + Bluetooth Low Energy MCU modules with:
- Complete Wi-Fi (802.11 b/g/n, 2.4GHz) and Bluetooth Low Energy functions
- Neural network computing acceleration
- Signal processing workload acceleration
- Rich peripheral set

### 1.2 Key Features

- Most I/O pins broken out to dual pin headers (breadboard compatible)
- Dual USB ports:
  - **USB-to-UART Port** (Micro-USB) - programming and debugging
  - **ESP32-S3 USB Port** (USB Type-C) - native USB OTG
- Onboard RGB LED (addressable, GPIO38 on v1.1)
- Boot and Reset buttons
- 3.3V LDO regulator
- USB-to-UART bridge (up to 3 Mbps)

### 1.3 Version Notes

**Current Version:** v1.1

| Version | RGB LED GPIO | Notes                              |
|---------|--------------|-------------------------------------|
| v1.0    | GPIO48       | Initial release                     |
| v1.1    | GPIO38       | Current version (since mid-2023)    |

Both versions available on market. Check your board's GPIO assignment for RGB LED control.

---

## 2. Hardware Specifications

### 2.1 ESP32-S3 Core Specifications

| Parameter                  | Value                                      |
|----------------------------|--------------------------------------------|
| CPU                        | Xtensa dual-core 32-bit LX7, up to 240 MHz |
| SRAM                       | 512 KB SRAM (in chip)                      |
| ROM                        | 384 KB ROM (in chip)                       |
| RTC Memory                 | 16 KB SRAM in RTC                          |
| External Flash             | 8 MB or 32 MB (module dependent)           |
| External PSRAM             | 8 MB or 16 MB (module dependent)           |
| Wi-Fi                      | 802.11 b/g/n, 2.4 GHz, up to 150 Mbps      |
| Bluetooth                  | Bluetooth 5, Bluetooth mesh                |
| GPIO                       | 45 programmable GPIOs                      |
| SPI                        | 4 (SPI2 used for flash/PSRAM)              |
| UART                       | 3                                          |
| I2C                        | 2                                          |
| I2S                        | 2                                          |
| ADC                        | 2 × 12-bit SAR ADCs, up to 20 channels     |
| Touch Sensors              | 14                                         |
| Temperature Sensor         | 1 (on-chip)                                |
| USB                        | 1 × USB OTG (full-speed, USB 1.1)          |
| JTAG                       | Built-in JTAG interface                    |

### 2.2 Board Physical Specifications

| Parameter              | Value                          |
|------------------------|--------------------------------|
| Dimensions             | ~55mm × 25mm (typical)         |
| Pin Headers            | 2.54mm pitch, dual row         |
| USB Connectors         | 1× Micro-USB, 1× USB Type-C    |
| Operating Temperature  | -40°C to +85°C                 |
| Power Input Voltage    | 5V via USB or 5V pin           |

---

## 3. Module Variants

### 3.1 Ordering Information

The development board comes in several variants depending on integrated module:

| Ordering Code              | Module                  | Flash    | PSRAM   | SPI Voltage | Antenna      |
|----------------------------|-------------------------|----------|---------|-------------|--------------|
| ESP32-S3-DevKitC-1-N8R8    | ESP32-S3-WROOM-1-N8R8   | 8 MB QD  | 8 MB OT | 3.3V        | PCB          |
| ESP32-S3-DevKitC-1-N32R16V | ESP32-S3-WROOM-2-N32R16V| 32 MB OT | 16 MB OT| 1.8V        | PCB          |
| ESP32-S3-DevKitC-1U-N8R8   | ESP32-S3-WROOM-1U-N8R8  | 8 MB QD  | 8 MB OT | 3.3V        | External     |

**Legend:**
- **QD** = Quad SPI (4-bit interface)
- **OT** = Octal SPI (8-bit interface)

### 3.2 Reserved GPIO Pins (Octal Flash/PSRAM)

**IMPORTANT:** For boards with Octal SPI flash/PSRAM (ESP32-S3-WROOM-1/1U with Octal memory, or ESP32-S3-WROOM-2):

**GPIO35, GPIO36, GPIO37** are used for internal communication with SPI flash/PSRAM and **not available for external use**.

---

## 4. Pinout Reference

### 4.1 Pin Header J1 (Left Side)

| No. | Name | Type  | Function                                                          |
|-----|------|-------|-------------------------------------------------------------------|
| 1   | 3V3  | P     | 3.3V power supply                                                 |
| 2   | 3V3  | P     | 3.3V power supply                                                 |
| 3   | RST  | I     | EN (chip enable, active high)                                     |
| 4   | 4    | I/O/T | RTC_GPIO4, GPIO4, TOUCH4, ADC1_CH3                                |
| 5   | 5    | I/O/T | RTC_GPIO5, GPIO5, TOUCH5, ADC1_CH4                                |
| 6   | 6    | I/O/T | RTC_GPIO6, GPIO6, TOUCH6, ADC1_CH5                                |
| 7   | 7    | I/O/T | RTC_GPIO7, GPIO7, TOUCH7, ADC1_CH6                                |
| 8   | 15   | I/O/T | RTC_GPIO15, GPIO15, U0RTS, ADC2_CH4, XTAL_32K_P                   |
| 9   | 16   | I/O/T | RTC_GPIO16, GPIO16, U0CTS, ADC2_CH5, XTAL_32K_N                   |
| 10  | 17   | I/O/T | RTC_GPIO17, GPIO17, U1TXD, ADC2_CH6                               |
| 11  | 18   | I/O/T | RTC_GPIO18, GPIO18, U1RXD, ADC2_CH7, CLK_OUT3                     |
| 12  | 8    | I/O/T | RTC_GPIO8, GPIO8, TOUCH8, ADC1_CH7, SUBSPICS1                     |
| 13  | 3    | I/O/T | RTC_GPIO3, GPIO3, TOUCH3, ADC1_CH2                                |
| 14  | 46   | I/O/T | GPIO46                                                            |
| 15  | 9    | I/O/T | RTC_GPIO9, GPIO9, TOUCH9, ADC1_CH8, FSPIHD, SUBSPIHD              |
| 16  | 10   | I/O/T | RTC_GPIO10, GPIO10, TOUCH10, ADC1_CH9, FSPICS0, FSPIIO4, SUBSPICS0|
| 17  | 11   | I/O/T | RTC_GPIO11, GPIO11, TOUCH11, ADC2_CH0, FSPID, FSPIIO5, SUBSPID   |
| 18  | 12   | I/O/T | RTC_GPIO12, GPIO12, TOUCH12, ADC2_CH1, FSPICLK, FSPIIO6, SUBSPICLK|
| 19  | 13   | I/O/T | RTC_GPIO13, GPIO13, TOUCH13, ADC2_CH2, FSPIQ, FSPIIO7, SUBSPIQ   |
| 20  | 14   | I/O/T | RTC_GPIO14, GPIO14, TOUCH14, ADC2_CH3, FSPIWP, FSPIDQS, SUBSPIWP |
| 21  | 5V   | P     | 5V power supply                                                   |
| 22  | G    | G     | Ground                                                            |

### 4.2 Pin Header J3 (Right Side)

| No. | Name | Type  | Function                                                          |
|-----|------|-------|-------------------------------------------------------------------|
| 1   | G    | G     | Ground                                                            |
| 2   | TX   | I/O/T | U0TXD, GPIO43, CLK_OUT1                                           |
| 3   | RX   | I/O/T | U0RXD, GPIO44, CLK_OUT2                                           |
| 4   | 1    | I/O/T | RTC_GPIO1, GPIO1, TOUCH1, ADC1_CH0                                |
| 5   | 2    | I/O/T | RTC_GPIO2, GPIO2, TOUCH2, ADC1_CH1                                |
| 6   | 42   | I/O/T | MTMS, GPIO42                                                      |
| 7   | 41   | I/O/T | MTDI, GPIO41, CLK_OUT1                                            |
| 8   | 40   | I/O/T | MTDO, GPIO40, CLK_OUT2                                            |
| 9   | 39   | I/O/T | MTCK, GPIO39, CLK_OUT3, SUBSPICS1                                 |
| 10  | 38   | I/O/T | GPIO38, FSPIWP, SUBSPIWP, **RGB LED** (v1.1)                      |
| 11  | 37   | I/O/T | SPIDQS, GPIO37, FSPIQ, SUBSPIQ                                    |
| 12  | 36   | I/O/T | SPIIO7, GPIO36, FSPICLK, SUBSPICLK                                |
| 13  | 35   | I/O/T | SPIIO6, GPIO35, FSPID, SUBSPID                                    |
| 14  | 0    | I/O/T | RTC_GPIO0, GPIO0                                                  |
| 15  | 45   | I/O/T | GPIO45                                                            |
| 16  | 48   | I/O/T | GPIO48, SPICLK_N, SUBSPICLK_N_DIFF, **RGB LED** (v1.0)            |
| 17  | 47   | I/O/T | GPIO47, SPICLK_P, SUBSPICLK_P_DIFF                                |
| 18  | 21   | I/O/T | RTC_GPIO21, GPIO21                                                |
| 19  | 20   | I/O/T | RTC_GPIO20, GPIO20, U1CTS, ADC2_CH9, CLK_OUT1, USB_D+             |
| 20  | 19   | I/O/T | RTC_GPIO19, GPIO19, U1RTS, ADC2_CH8, CLK_OUT2, USB_D-             |
| 21  | G    | G     | Ground                                                            |
| 22  | G    | G     | Ground                                                            |

**Type Legend:**
- **P** = Power supply
- **I** = Input
- **O** = Output
- **T** = High impedance (tri-state)
- **G** = Ground

### 4.3 Special Function Pins

| Function               | GPIO Pin(s)       | Notes                                      |
|------------------------|-------------------|--------------------------------------------|
| UART0 (USB-to-UART)    | GPIO43 (TX), GPIO44 (RX) | Default serial programming port |
| USB OTG                | GPIO19 (D-), GPIO20 (D+) | Native USB functionality       |
| RGB LED (v1.1)         | GPIO38            | WS2812/SK6812 compatible                   |
| RGB LED (v1.0)         | GPIO48            | WS2812/SK6812 compatible                   |
| Boot Button            | GPIO0             | Pull low for download mode                 |
| JTAG                   | GPIO39-42         | MTCK, MTDO, MTDI, MTMS                     |
| ADC1                   | GPIO1-10          | 10 channels                                |
| ADC2                   | GPIO11-20         | 10 channels (shared with Wi-Fi)            |
| Touch                  | GPIO1-14          | Capacitive touch sensing                   |
| 32.768 kHz Crystal     | GPIO15, GPIO16    | Optional external RTC crystal              |

### 4.4 Strapping Pins

**Important:** These pins have pull-up/pull-down resistors and affect boot mode:

| GPIO | Default   | Function                                   |
|------|-----------|---------------------------------------------|
| 0    | Pull-up   | Boot mode selection (low = download mode)   |
| 3    | Floating  | JTAG signal source selection                |
| 45   | Pull-down | VDD_SPI voltage                             |
| 46   | Pull-down | Boot mode, ROM message printing             |

Avoid using these pins for external pull-up/pull-down circuits unless you understand boot requirements.

---

## 5. Power Supply

### 5.1 Power Input Options

Three mutually exclusive power supply methods:

| Method                  | Input Pins       | Voltage | Recommended | Notes                          |
|-------------------------|------------------|---------|-------------|--------------------------------|
| USB-to-UART Port        | Micro-USB        | 5V      | Yes         | Default, includes UART bridge  |
| ESP32-S3 USB Port       | USB Type-C       | 5V      | Yes         | Native USB, programming capable|
| 5V Pin                  | 5V + G (GND)     | 5V      | Alternative | External 5V regulated supply   |
| 3.3V Pin                | 3V3 + G (GND)    | 3.3V    | Not recommended | Bypasses LDO, use with caution |

### 5.2 Power Specifications

| Parameter                      | Value                |
|--------------------------------|----------------------|
| Input Voltage (USB/5V pin)     | 5V DC ±5%            |
| Input Voltage (3V3 pin)        | 3.3V DC ±5%          |
| Operating Current (typical)    | ~80-200mA            |
| Peak Current (Wi-Fi TX)        | ~350-500mA           |
| 3.3V LDO Output                | Max 600mA            |

**Note:** Ensure USB cable and power supply can provide sufficient current (≥500mA recommended).

---

## 6. Getting Started

### 6.1 Required Hardware

- ESP32-S3-DevKitC-1 board
- USB 2.0 cable:
  - **Standard-A to Micro-B** (for USB-to-UART port)
  - **Standard-A to USB-C** (for ESP32-S3 USB port)
- Computer running Windows, Linux, or macOS

**Important:** Use a data-capable USB cable. Charge-only cables will not work for programming.

### 6.2 Hardware Setup

1. **Connect USB Cable:**
   - Connect **USB-to-UART Port** (Micro-USB) for initial setup
   - Alternatively, use **ESP32-S3 USB Port** (Type-C) for native USB support

2. **Verify Power:**
   - 3.3V Power LED should illuminate
   - Computer should detect USB device

3. **Enter Download Mode (if needed):**
   - Hold **Boot** button
   - Press and release **Reset** button
   - Release **Boot** button
   - Board is now in firmware download mode

### 6.3 Software Setup

#### ESP-IDF (Official Framework)

1. **Install ESP-IDF:**
   ```bash
   git clone --recursive https://github.com/espressif/esp-idf.git
   cd esp-idf
   ./install.sh esp32s3
   . ./export.sh
   ```

2. **Create Project:**
   ```bash
   idf.py create-project my_project
   cd my_project
   idf.py set-target esp32s3
   ```

3. **Build and Flash:**
   ```bash
   idf.py build
   idf.py -p /dev/ttyUSB0 flash monitor
   ```

#### Arduino IDE

1. **Install ESP32 Board Support:**
   - Open Arduino IDE
   - Go to: File → Preferences
   - Add to "Additional Board Manager URLs":
     ```
     https://espressif.github.io/arduino-esp32/package_esp32_index.json
     ```
   - Tools → Board → Boards Manager → Search "esp32" → Install

2. **Select Board:**
   - Tools → Board → esp32 → ESP32S3 Dev Module

3. **Configure Settings:**
   - USB CDC On Boot: "Enabled" (for native USB)
   - Upload Mode: "UART0 / Hardware CDC"
   - USB Mode: "Hardware CDC and JTAG"
   - Flash Size: "8MB" or "32MB" (match your module)
   - PSRAM: "OPI PSRAM"

4. **Select Port and Upload:**
   - Tools → Port → (select COM/tty port)
   - Upload sketch

### 6.4 First Program - RGB LED Blink

```c
// ESP32-S3-DevKitC-1 v1.1 RGB LED test
#define RGB_LED_PIN 38  // GPIO38 for v1.1 (GPIO48 for v1.0)

void setup() {
  pinMode(RGB_LED_PIN, OUTPUT);
}

void loop() {
  digitalWrite(RGB_LED_PIN, HIGH);
  delay(500);
  digitalWrite(RGB_LED_PIN, LOW);
  delay(500);
}
```

**Note:** For addressable RGB LED (WS2812), use appropriate library (FastLED, Adafruit NeoPixel, etc.)

---

## 7. Component Description

### 7.1 Key Components (Counter-Clockwise from Top)

| Component              | Description                                                  |
|------------------------|--------------------------------------------------------------|
| **ESP32-S3-WROOM-1/1U/2** | Main MCU module with Wi-Fi + BLE                          |
| **3.3V Power LED**     | Indicates board is powered                                   |
| **USB-to-UART Bridge** | CP2102N or similar, up to 3 Mbps transfer rate               |
| **RGB LED**            | Addressable RGB LED (WS2812), GPIO38 (v1.1) or GPIO48 (v1.0)|
| **USB-to-UART Port**   | Micro-USB connector for power, programming, serial comm      |
| **Boot Button**        | GPIO0, pull low for download mode                            |
| **Reset Button**       | Chip reset (EN pin)                                          |
| **USB Port**           | USB Type-C connector, native USB OTG (full-speed USB 1.1)    |
| **5V to 3.3V LDO**     | Voltage regulator, converts 5V to 3.3V                       |
| **Pin Headers**        | 2× 22-pin headers (J1, J3) for GPIO access                   |

### 7.2 Connectors

#### USB-to-UART Port (Micro-USB)
- Power supply to board
- Firmware flashing via UART
- Serial communication with chip
- Uses onboard USB-to-UART bridge

#### ESP32-S3 USB Port (USB Type-C)
- Power supply to board
- Firmware flashing via USB (CDC/DFU)
- USB 1.1 communication
- JTAG debugging over USB
- Requires USB CDC to be enabled in firmware

### 7.3 Buttons

#### Boot Button
- Connected to GPIO0
- Function: Enter download mode
- Usage: Hold Boot, press Reset, release Boot → enters download mode

#### Reset Button
- Connected to EN (chip enable) pin
- Function: Hardware reset of ESP32-S3
- Usage: Press to restart the chip

---

## 8. Hardware Considerations

### 8.1 GPIO Usage Restrictions

#### Reserved/Internal Pins (Octal Flash/PSRAM Modules)

**Do not use externally:**
- **GPIO26** - SPICS1
- **GPIO27** - SPIHD
- **GPIO28** - SPIWP
- **GPIO29** - SPICS0
- **GPIO30** - SPICLK
- **GPIO31** - SPIQ
- **GPIO32** - SPID

**Additionally for Octal SPI:**
- **GPIO33** - SPIIO4
- **GPIO34** - SPIIO5
- **GPIO35** - SPIIO6
- **GPIO36** - SPIIO7
- **GPIO37** - SPIDQS

#### Strapping Pins

Use carefully (affects boot behavior):
- **GPIO0** - Boot mode selection
- **GPIO3** - JTAG signal source
- **GPIO45** - VDD_SPI voltage
- **GPIO46** - Boot mode and ROM printing

### 8.2 ADC2 Limitations

**ADC2 channels (GPIO11-20) cannot be used when Wi-Fi is active.**

Use ADC1 (GPIO1-10) for analog readings in Wi-Fi applications.

### 8.3 USB Pin Conflicts

If using native USB functionality (GPIO19/20), these pins are not available for other purposes:
- **GPIO19** - USB D-
- **GPIO20** - USB D+

### 8.4 Boot Mode Selection

| Boot Mode | GPIO0 | GPIO45 | GPIO46 |
|-----------|-------|--------|--------|
| SPI Boot (normal) | 1 | Any | Any |
| Download Mode (UART/USB) | 0 | Any | Any |

### 8.5 Power Design Considerations

- Provide adequate decoupling capacitors near power pins
- Ensure stable 5V supply during flash writing
- Wi-Fi operation causes current spikes (~350mA peaks)
- Use short, thick traces for power distribution
- Add bulk capacitance (100-220µF) near power input for Wi-Fi stability

---

## 9. Related Documentation

### 9.1 Datasheets

- [ESP32-S3 Series Datasheet](https://www.espressif.com/sites/default/files/documentation/esp32-s3_datasheet_en.pdf)
- [ESP32-S3-WROOM-1 & ESP32-S3-WROOM-1U Datasheet](https://www.espressif.com/sites/default/files/documentation/esp32-s3-wroom-1_wroom-1u_datasheet_en.pdf)
- [ESP32-S3-WROOM-2 Datasheet](https://www.espressif.com/sites/default/files/documentation/esp32-s3-wroom-2_datasheet_en.pdf)

### 9.2 Schematics and Design Files

- [ESP32-S3-DevKitC-1 Schematic (PDF)](https://dl.espressif.com/dl/schematics/SCH_ESP32-S3-DEVKITC-1_V1.1_20221130.pdf)
- [ESP32-S3-DevKitC-1 PCB Layout (PDF)](https://dl.espressif.com/dl/schematics/PCB_ESP32-S3-DevKitC-1_V1.1_20221130.pdf)
- [ESP32-S3-DevKitC-1 Dimensions (PDF)](https://dl.espressif.com/dl/schematics/DIM_ESP32-S3-DEVKITC-1_V1.1_20221130.pdf)
- [ESP32-S3-DevKitC-1 Dimensions DXF](https://dl.espressif.com/dl/schematics/DXF_ESP32-S3-DevKitC-1_V1.1_20221130.dxf)

### 9.3 Development Resources

- [ESP-IDF Programming Guide](https://docs.espressif.com/projects/esp-idf/en/latest/esp32s3/)
- [ESP32-S3 Technical Reference Manual](https://www.espressif.com/sites/default/files/documentation/esp32-s3_technical_reference_manual_en.pdf)
- [ESP DevKits Overview](https://www.espressif.com/en/products/devkits)
- [Arduino-ESP32 Documentation](https://docs.espressif.com/projects/arduino-esp32/en/latest/)

### 9.4 Support and Community

- **Sales Contact:** sales@espressif.com
- **Sample Orders:** https://www.espressif.com/en/contact-us/get-samples
- **Bulk Orders:** https://www.espressif.com/en/contact-us/sales-questions
- **Technical Forum:** https://esp32.com/
- **GitHub:** https://github.com/espressif

---

## Quick Reference Card

```
Board:          ESP32-S3-DevKitC-1 v1.1
MCU:            ESP32-S3 (Xtensa dual-core @ 240MHz)
Flash:          8MB or 32MB (module dependent)
PSRAM:          8MB or 16MB (module dependent)
Wi-Fi:          802.11 b/g/n (2.4GHz)
Bluetooth:      BLE 5.0
GPIO:           45 (many with multiple functions)
ADC:            2× 12-bit (20 channels total)
Touch:          14 capacitive touch inputs
USB:            1× USB OTG (full-speed)
Power:          5V via USB or pin, 3.3V LDO
RGB LED:        GPIO38 (v1.1), GPIO48 (v1.0)
Boot Button:    GPIO0
Programming:    USB-to-UART (Micro-USB) or USB (Type-C)

Reserved Pins (Octal modules):
  GPIO35, GPIO36, GPIO37 - Internal SPI flash/PSRAM

Strapping Pins (use with care):
  GPIO0, GPIO3, GPIO45, GPIO46
```

---

## Implementation Checklist

### Basic Setup
- [ ] Identify board version (check RGB LED GPIO: v1.0=GPIO48, v1.1=GPIO38)
- [ ] Identify module variant (check module marking for flash/PSRAM size)
- [ ] Install ESP-IDF or Arduino-ESP32 development environment
- [ ] Connect USB cable (Micro-USB for UART or USB-C for native USB)
- [ ] Verify board enumeration on computer
- [ ] Flash test firmware (blink example)

### Pin Planning
- [ ] Review pinout tables and identify required GPIO
- [ ] Avoid reserved pins (GPIO35-37 on Octal modules)
- [ ] Consider strapping pin constraints (GPIO0, 3, 45, 46)
- [ ] Use ADC1 channels if Wi-Fi will be active
- [ ] Plan for USB D+/D- if using native USB functionality

### Power Design
- [ ] Verify power supply can provide 500mA minimum
- [ ] Add decoupling capacitors on power rails
- [ ] Consider bulk capacitance for Wi-Fi stability
- [ ] Protect USB ports with ESD diodes if in harsh environment

### Software Configuration
- [ ] Set correct board target (esp32s3)
- [ ] Configure flash size (8MB or 32MB)
- [ ] Enable PSRAM in build settings (OPI PSRAM)
- [ ] Configure USB CDC if using native USB
- [ ] Set partition table for application size

---

*Document generated from ESP32-S3-DevKitC-1 User Guide v1.1*