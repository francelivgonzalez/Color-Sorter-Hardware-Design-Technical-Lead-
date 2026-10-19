\# Color Sorting System - Control Logic



\## Overview



The Arduino Uno R3 controls the sorting process using input from the TCS3200 color sensor, a homing limit switch, and commands sent through the Serial Monitor.



The current firmware is a reconstructed development version with manual testing commands.



\## Color Detection



The TCS3200 measures red, green, blue, and clear-channel light intensity.



The firmware converts pulse durations into frequency-proportional readings and normalizes the RGB values to reduce sensitivity to changes in overall brightness.



A provisional separation threshold is used to reject uncertain color readings.



\## Stepper Motor Control



The Arduino communicates with the A4988 driver using STEP, DIR, and ENABLE signals.



Three indexing positions are currently defined:



\- Red: 0 steps

\- Green: 400 steps

\- Blue: 800 steps



These positions are placeholders and must be adjusted to the actual mechanical system.



\## Homing



The homing switch establishes the reference position.



The controller attempts to locate the switch within a maximum number of steps. If the switch cannot be found or released, the operation stops and an error is reported.



\## Servo Control



The PCA9685 communicates with the Arduino over I²C and provides PWM signals for three proposed servo channels:



\- Channel 0: Intake servo

\- Channel 1: Sorting gate servo

\- Channel 2: Routing servo



Currently, the sorting cycle actuates the sorting gate after indexing. Intake and routing channels have separate manual test commands.



\## Sorting Sequence



1\. Home the indexing mechanism.

2\. Read and classify the object's color.

3\. Reject uncertain readings.

4\. Move the stepper to the selected position.

5\. Open the sorting gate.

6\. Close the gate.

7\. Report cycle completion.



\## Serial Commands



\- `r`: Read raw color sensor values

\- `c`: Classify the current color

\- `h`: Home the stepper

\- `s`: Execute one sorting cycle

\- `0`: Test intake servo

\- `1`: Test sorting gate

\- `2`: Test routing servo

\- `?`: Display available commands



\## Current Limitations



\-

