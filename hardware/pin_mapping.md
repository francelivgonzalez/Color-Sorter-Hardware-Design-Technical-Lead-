\# Color Sorting System — Pin Mapping



\## Overview



This document defines the proposed Arduino Uno R3 connections for the reconstructed Color Sorting System.



The system uses a TCS3200 sensor for color detection, an A4988 driver for stepper indexing, a PCA9685 for multiple servos, and a limit switch for homing.



\## 1. TCS3200 Color Sensor



\- VCC → Regulated 5V

\- GND → Common GND

\- S0 → Arduino D4

\- S1 → Arduino D5

\- S2 → Arduino D6

\- S3 → Arduino D7

\- OUT → Arduino D8

\- OE → GND (sensor output enabled)



\## 2. A4988 Stepper Motor Driver



\- STEP → Arduino D2

\- DIR → Arduino D3

\- ENABLE → Arduino D9

\- VDD → Regulated 5V

\- Logic GND → Common GND

\- VMOT → 12V DC supply

\- Motor GND → 12V supply negative

\- 1A / 1B → One NEMA 17 motor coil

\- 2A / 2B → Other NEMA 17 motor coil

\- RESET and SLEEP → Connected together and pulled HIGH to VDD

\- MS1, MS2, MS3 → GND for full-step mode



Place an appropriately rated bulk capacitor (typically at least 47 µF, commonly 100 µF) directly across VMOT and motor GND near the A4988 driver. Verify polarity and voltage rating.



Set the A4988 current limit to match the motor and driver cooling conditions before operation.



\## 3. Homing Limit Switch



\- Signal → Arduino D10

\- Other terminal → GND

\- Arduino configuration → INPUT\_PULLUP



The switch is active LOW when pressed.



\## 4. PCA9685 Servo Driver



\- VCC → Regulated 5V logic

\- GND → Common GND

\- SDA → Arduino A4

\- SCL → Arduino A5

\- V+ → Regulated servo supply, nominally 5V



Proposed servo channels:



\- Channel 0 → Intake servo

\- Channel 1 → Sorting gate servo

\- Channel 2 → Output routing servo



These servo roles are provisional until the original mechanical design is confirmed.



The servo supply must be sized for peak servo current. Do not power the servos from the Arduino's onboard regulator.



\## 5. Power Distribution



\- 120V AC input → Enclosed AC/DC supply (mains side)

\- AC/DC supply output → 12V DC bus

\- 12V bus → A4988 VMOT

\- 12V bus → Buck converter input

\- Buck converter output → Regulated 5V bus

\- 5V bus → Arduino, TCS3200, PCA9685 logic

\- Suitable 5V servo supply → PCA9685 V+

\- All low-voltage grounds → Common DC ground



The 12V AC/DC supply and buck converter must have adequate current capacity. The 5V servo rail may require its own dedicated regulator.



\## 6. Unused Arduino Pins



Available for future expansion:



\- D11, D12, D13

\- A0, A1, A2, A3



D0 and D1 are reserved for USB serial communication.



