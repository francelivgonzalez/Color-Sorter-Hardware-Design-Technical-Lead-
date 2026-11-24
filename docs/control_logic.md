# Color Sorting System — Control Logic

## Overview

The Arduino Uno R3 controls the sorting process using input from the TCS3200 color sensor, a homing limit switch, and commands sent through the Serial Monitor.

The current firmware is a reconstructed development version with manual testing commands.

## Color Detection

The TCS3200 measures red, green, blue, and clear-channel light intensity.

The firmware converts pulse durations into frequency-proportional readings and normalizes the RGB values to reduce sensitivity to changes in overall brightness.

A provisional separation threshold is used to reject uncertain color readings.

## Stepper Motor Control

The Arduino communicates with the A4988 driver using `STEP`, `DIR`, and `ENABLE` signals.

Three indexing positions are currently defined:

- **Red:** 0 steps
- **Green:** 400 steps
- **Blue:** 800 steps

These positions are placeholders and must be adjusted to the actual mechanical system.

## Homing

The homing switch establishes the reference position.

The controller attempts to locate the switch within a maximum number of steps. If the switch cannot be found or released, the operation stops and an error is reported.
