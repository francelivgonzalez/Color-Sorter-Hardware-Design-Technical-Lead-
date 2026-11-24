# Color Sorting System — System Architecture

## Overview

The Color Sorting System combines optical sensing with motor-driven positioning and servo actuation.

The Arduino Uno R3 coordinates the process by reading the TCS3200 sensor, determining an object's color, and controlling the motors used to route it.

## System Workflow

1. An object is placed in the sensing area.
2. The TCS3200 measures red, green, blue, and clear-channel values.
3. The firmware normalizes the color readings and attempts to identify the object.
4. If the reading is uncertain, the sorting operation is cancelled.
5. The stepper motor indexes the mechanism toward the selected bin.
6. The servo gate opens to release the object.
7. The gate closes, completing the sorting cycle.

## Control Architecture

**Inputs**
- TCS3200 color sensor
- Homing limit switch
- Serial Monitor commands for development testing

**Controller**
- Arduino Uno R3

**Outputs**
- A4988 driver and NEMA 17 stepper motor
- PCA9685 PWM driver and servo motors
- Serial Monitor diagnostic messages

## Power Architecture

The proposed design uses a 12V DC bus for the stepper motor driver and a buck converter to supply regulated 5V for the control electronics.

The power architecture is documented separately in `hardware/power_distribution.md`.

## Development Status

The repository contains reconstructed development firmware and a proposed electrical design. Physical validation, sensor calibration, and final motion parameters are still pending.
