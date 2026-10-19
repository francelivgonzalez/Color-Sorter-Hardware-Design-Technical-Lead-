\# Color Sorting System - Testing Plan



\## Overview



This document outlines the tests needed to validate the reconstructed Color Sorting System. These tests have not yet been completed.



\## Firmware Verification



\- \[ ] Compile firmware for Arduino Uno R3.

\- \[ ] Confirm the required Adafruit libraries are installed.

\- \[ ] Verify serial communication at 9600 baud.



\## Color Sensor Testing



\- \[ ] Confirm the TCS3200 provides valid RGB and clear-channel readings.

\- \[ ] Record measurements for red, green, and blue objects.

\- \[ ] Collect readings under different lighting conditions.

\- \[ ] Calibrate color thresholds using known samples.

\- \[ ] Verify that uncertain readings return UNKNOWN.



\## Stepper Motor Testing



\- \[ ] Verify A4988 current-limit configuration.

\- \[ ] Confirm stepper rotation direction.

\- \[ ] Test individual indexing positions.

\- \[ ] Verify movement limits.

\- \[ ] Check alignment and repeatability.



\## Homing Verification



\- \[ ] Confirm switch wiring and active-LOW behavior.

\- \[ ] Verify homing direction.

\- \[ ] Test switch detection and release.

\- \[ ] Verify that failed homing prevents sorting.



\## Servo Testing



\- \[ ] Verify servo power and current requirements.

\- \[ ] Confirm PCA9685 communication.

\- \[ ] Test intake, sorting gate, and routing servo channels individually.

\- \[ ] Calibrate servo angles.

\- \[ ] Check for mechanical interference.



\## Power Distribution



\- \[ ] Verify AC/DC power supply output is 12V DC.

\- \[ ] Verify regulated 5V output from the buck converter.

\- \[ ] Confirm appropriate supply current ratings.

\- \[ ] Check common DC grounding.

\- \[ ] Verify required protective components.



\## Full System Validation



\- \[ ] Complete a successful red-object sorting cycle.

\- \[ ] Complete a successful green-object sorting cycle.

\- \[ ] Complete a successful blue-object sorting cycle.

\- \[ ] Confirm uncertain colors are rejected.

\- \[ ] Measure sorting accuracy across repeated trials.

\- \[ ] Measure sorting time and positioning repeatability.



\## Current Status



The project has reconstructed firmware and design documentation. Compilation, calibration, and physical hardware testing have not yet been verified.

