\# Color Sorting System — Hardware Components



\## Overview



This project uses an Arduino Uno R3 to coordinate color detection, stepper motor positioning, and servo-controlled sorting. The system was developed through the Robotics and Automation Society at Texas State University.



\## Components



\### Arduino Uno R3

The main microcontroller responsible for reading sensor inputs and controlling the sorting mechanism.



\### TCS3200 Color Sensor

Measures red, green, blue, and clear-channel light intensity. The firmware normalizes the sensor readings to reduce the effect of changing brightness.



\### NEMA 17 Stepper Motor

Rotates the indexing mechanism to align objects with their assigned sorting locations.



\### A4988 Stepper Motor Driver

Controls the direction and stepping of the NEMA 17 motor. Its current limit must be adjusted to match the motor specifications.



\### PCA9685 PWM Driver

Controls multiple servo motors using I²C communication with the Arduino Uno R3.



\### Servo Motors

Operate the intake, sorting gate, and routing mechanisms. The current firmware defines three servo channels, but the original configuration still needs to be confirmed.



\### Homing Limit Switch

Provides a reference position for the stepper-controlled mechanism to improve alignment and repeatability.



\### 12V DC Power Supply

An enclosed AC/DC switching power supply provides the proposed 12V DC power bus for the reconstructed design.



\### DC-DC Buck Converter

Steps the 12V supply down to regulated 5V for the control electronics and a

