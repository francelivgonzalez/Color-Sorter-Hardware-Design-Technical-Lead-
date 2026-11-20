# Color-Sorter-Hardware-Design-Technical-Lead
> Automated color-sorting hardware on an Arduino UNO R3, pairing TCS3200 sensing and regulated power with stepper indexing, homing checks, and multi-servo routing.

An automated color-sorting hardware platform developed through Texas State University's Robotics and Automation Society, built around an Arduino UNO R3, TCS3200 color sensor, stepper motor indexing with homing verification, PWM-driven multi-servo routing, and regulated DC-DC power distribution.

## What This Project Does

Sorting parts reliably by color requires repeatable mechanical alignment, clean power delivery, and coordinated sensing and actuation. This project establishes the hardware architecture and controls roadmap for a color-sorting system:
1. **Color Sensing & Bin Selection:** Reads object color with a TCS3200 sensor to determine the target bin.
2. **Stepper Indexing & Homing:** Drives stepper motion with homing sensor verification to keep alignment and repeatability consistent.
3. **Multi-Servo Routing & Power Regulation:** Uses PWM drivers and servos to route parts into bins while supplying regulated power via a DC-DC converter.

## What I'm Focusing On

- **Hardware Architecture & Integration:** Coordinating the Arduino UNO R3, TCS3200 color sensor, stepper indexing, homing sensor, PWM drivers, and DC-DC power stage.
- **Repeatability & Alignment:** Using homing verification and stepper indexing to reduce positional drift across sort cycles.
- **Subsystem Bring-Up & Troubleshooting:** Validating individual hardware blocks and documenting wiring, power distribution, and open verification items.
- **Technical Leadership & Roadmap Execution:** Driving system design, troubleshooting, and project milestones as Technical Lead for the build.

## How the System Is Set Up

- **Compute & Sensing:** Arduino UNO R3 paired with a TCS3200 color sensor and homing sensor for alignment verification.
- **Actuation & Motion:** Stepper motors and drivers for indexing alongside PWM drivers and multi-servo actuation for part routing.
- **Power & Documentation:** DC-DC converter for regulated power distribution, supported by wiring/power notes, subsystem docs, and proposed reconstruction diagrams (with original wiring and component ratings still undergoing full verification).

## Planned Folder Layout

```text
Color-Sorter-Hardware-Design-Technical-Lead/
├── README.md
├── hardware/       # Hardware design notes, wiring, power distribution, and diagrams
├── control/        # Control logic planning and actuation/indexing notes
├── docs/           # Subsystem documentation, troubleshooting, and roadmap records
└── media/          # Reference photos and visual notes
