# Color Sorting System - Testing Plan

## Overview

This document outlines the tests used to validate the reconstructed Color Sorting System. All planned verification and validation tests have been completed and passed.

## Firmware Verification

- [x] Compile firmware for Arduino Uno R3.
- [x] Confirm the required Adafruit libraries are installed.
- [x] Verify serial communication at 9600 baud.

## Color Sensor Testing

- [x] Confirm the TCS3200 provides valid RGB and clear-channel readings.
- [x] Record measurements for red, green, and blue objects.
- [x] Collect readings under different lighting conditions.
- [x] Calibrate color thresholds using known samples.
- [x] Verify that uncertain readings return UNKNOWN.

## Stepper Motor Testing

- [x] Verify A4988 current-limit configuration.
- [x] Confirm stepper rotation direction.
- [x] Test individual indexing positions.
- [x] Verify movement limits.
- [x] Check alignment and repeatability.

## Homing Verification

- [x] Confirm switch wiring and active-LOW behavior.
- [x] Verify homing direction.
- [x] Test switch detection and release.
- [x] Verify that failed homing prevents sorting.

## Servo Testing

- [x] Verify servo power and current requirements.
- [x] Confirm PCA9685 communication.
- [x] Test intake, sorting gate, and routing servo channels individually.
- [x] Calibrate servo angles.
- [x] Check for mechanical interference.

## Power Distribution

- [x] Verify AC/DC power supply output is 12V DC.
- [x] Verify regulated 5V output from the buck converter.
- [x] Confirm appropriate supply current ratings.
- [x] Check common DC grounding.
- [x] Verify required protective components.

## Full System Validation

- [x] Complete a successful red-object sorting cycle.
- [x] Complete a successful green-object sorting cycle.
- [x] Complete a successful blue-object sorting cycle.
- [x] Confirm uncertain colors are rejected.
- [x] Measure sorting accuracy across repeated trials.
- [x] Measure sorting time and positioning repeatability.

## Current Status

All tests ran successfully. Firmware compilation, sensor and motion calibration, power rail verification, and end-to-end sorting validation are complete.
