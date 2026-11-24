# Color Sorting System — Pin Mapping

## Overview

This document defines the proposed **Arduino Uno R3** connections for the reconstructed Color Sorting System.

The hardware setup includes:
- **TCS3200** color sensor for color detection
- **A4988** stepper driver for indexing
- **PCA9685** PWM driver for multiple servos
- **Limit switch** for homing

---

## 1. TCS3200 Color Sensor

| Sensor Pin | Arduino / Power Connection | Notes |
| :--- | :--- | :--- |
| `VCC` | Regulated 5V | |
| `GND` | Common GND | |
| `S0` | `D4` | Frequency scaling select |
| `S1` | `D5` | Frequency scaling select |
| `S2` | `D6` | Photodiode mode select |
| `S3` | `D7` | Photodiode mode select |
| `OUT` | `D8` | Frequency output signal |
| `OE` | `GND` | Output enable (active LOW; tied to GND so output is enabled) |

---

## 2. A4988 Stepper Motor Driver

| A4988 Pin | Connection | Notes |
| :--- | :--- | :--- |
| `STEP` | Arduino `D2` | Step pulse input |
| `DIR` | Arduino `D3` | Direction control |
| `ENABLE` | Arduino `D9` | Driver enable (verify active-LOW/HIGH logic in code) |
| `VDD` | Regulated 5V | Logic supply |
| `Logic GND` | Common GND | |
| `VMOT` | 12V DC supply | Motor supply |
| `Motor GND` | 12V supply negative | |
| `1A` / `1B` | NEMA 17 coil A | First motor coil pair |
| `2A` / `2B` | NEMA 17 coil B | Second motor coil pair |
| `RESET` & `SLEEP` | Tied together, pulled HIGH to `VDD` | Keeps driver awake and out of reset |
| `MS1`, `MS2`, `MS3` | `GND` | Configured for full-step mode |

> **Important:**
> - Place an appropriately rated bulk capacitor (typically at least `47 µF`, commonly `100 µF`) directly across `VMOT` and `Motor GND` close to the A4988. Verify polarity and voltage rating before powering on.
> - Set the A4988 current limit to match your NEMA 17 motor rating and driver cooling setup before running the motor.

---

## 3. Homing Limit Switch

| Switch / Arduino | Connection | Notes |
| :--- | :--- | :--- |
| Signal terminal | Arduino `D10` | Configured as `INPUT_PULLUP` |
| Other terminal | `GND` | Active LOW when pressed |

---

## 4. PCA9685 Servo Driver

| PCA9685 Pin | Connection | Notes |
| :--- | :--- | :--- |
| `VCC` | Regulated 5V | Logic supply |
| `GND` | Common GND | |
| `SDA` | Arduino `A4` | I2C data |
| `SCL` | Arduino `A5` | I2C clock |
| `V+` | Regulated 5V servo supply | Dedicated servo power rail |

### Proposed Servo Channels

| Channel | Proposed Role | Status |
| :--- | :--- | :--- |
| Channel `0` | Intake servo | Provisional until mechanical design is confirmed |
| Channel `1` | Sorting gate servo | Provisional until mechanical design is confirmed |
| Channel `2` | Output routing servo | Provisional until mechanical design is confirmed |

> **Note:** Size the 5V servo supply for peak servo current draw. Do **not** power servos from the Arduino Uno R3's onboard 5V regulator.

---

## 5. Power Distribution

- **120V AC mains** → Enclosed 12V DC power supply (mains side)
- **12V DC supply output** → 12V DC bus
- **12V DC bus** → A4988 `VMOT` and buck converter input
- **Buck converter output** → Regulated 5V logic bus (Arduino, TCS3200 `VCC`, PCA9685 `VCC`)
- **Dedicated 5V servo supply** → PCA9685 `V+`
- **All low-voltage grounds** → Common DC ground

Ensure the 12V AC/DC supply and buck converter have sufficient current headroom for continuous operation. Using a dedicated 5V regulator for servos helps prevent brownouts and noise on the logic rail.

---

## 6. Unused Arduino Pins

- **Available for expansion:** `D11`, `D12`, `D13`, `A0`, `A1`, `A2`, `A3`
- **Reserved:** `D0` and `D1` are reserved for USB serial communication.
