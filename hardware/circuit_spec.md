# Color Sorting System - Circuit Diagram Specification

## Controller
Arduino Uno R3

## Power Distribution
- Enclosed AC/DC power supply: 120V AC input, proposed 12V DC output
- 12V DC powers the A4988 motor supply and the buck converter
- Buck converter produces regulated 5V DC
- Regulated 5V powers the Arduino, TCS3200, and PCA9685 logic
- PCA9685 V+ requires a suitably rated servo power supply
- All low-voltage grounds share a common reference

The power supply rating and component current requirements must be verified. The mains supply is represented as a sealed module.

## TCS3200 Connections
- `VCC` -> 5V
- `GND` -> GND
- `S0` -> `D4`
- `S1` -> `D5`
- `S2` -> `D6`
- `S3` -> `D7`
- `OUT` -> `D8`
- `OE` -> `GND`

## A4988 Connections
- `STEP` -> `D2`
- `DIR` -> `D3`
- `ENABLE` -> `D9`
- `VDD` -> 5V
- `Logic GND` -> GND
- `VMOT` -> 12V
- `Motor GND` -> Common DC ground
- `RESET` and `SLEEP` -> HIGH
- `MS1`, `MS2`, `MS3` -> `GND` for full-step mode

Include a suitably rated bulk capacitor near `VMOT` and `Motor GND`. Motor coil pairs must be identified before connection.

## Homing Switch
- Switch signal -> `D10`
- Other terminal -> `GND`
- Active LOW using `INPUT_PULLUP`

## PCA9685 Connections
- `VCC` -> 5V logic
- `GND` -> Common GND
- `SDA` -> Arduino `A4`
- `SCL` -> Arduino `A5`
- `V+` -> Regulated servo supply

## Proposed Servo Channels
- Channel 0 -> Intake servo
- Channel 1 -> Sorting gate servo
- Channel 2 -> Routing servo

## Diagram Requirements
Create two diagrams:

1. A circuit wiring diagram showing all components, connections, and power rails.
2. An electrical schematic with clearly labeled signal and power nets.

Show the 12V and 5V rails separately. Do not connect 12V directly to the Arduino 5V pin or servos.
