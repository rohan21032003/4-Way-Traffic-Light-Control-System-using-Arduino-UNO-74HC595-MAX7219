# 4-Way-Traffic-Light-Control-System-using-Arduino-UNO-74HC595-MAX7219
A realistic 4-way traffic light control system built using Arduino UNO with dual 74HC595 shift registers and MAX7219 display driver.  Features: • 4 independent road traffic control • Green → Yellow → Red sequencing • Pedestrian crossing mode • Real-time countdown timers for all roads • Shift register expansion for efficient pin usage
# 4-Way Traffic Light Control System

## Overview

This project simulates a realistic 4-way traffic intersection using Arduino UNO.

The system controls four independent traffic directions using two 74HC595 shift registers while displaying live countdown timers through a MAX7219 display controller.

Pedestrian crossing mode is included and can be triggered manually.

---

## Features

✅ 4 Road Traffic Control  
✅ Green → Yellow → Red Cycle  
✅ Pedestrian Crossing Mode  
✅ Real-Time Countdown Display  
✅ Non-Blocking Timing (millis())  
✅ Efficient Pin Usage using Shift Registers  
✅ MAX7219 Display Control  
✅ Proteus Simulation Ready  

---

## Components

### Controller
- Arduino UNO

### Traffic Expansion
- 74HC595 ×2

### Display
- MAX7219 ×1
- 2 Digit 7 Segment Display ×4 (Common Cathode)

### Other
- LEDs
- Resistors
- Push Button

---

## Pin Mapping

### Arduino → 74HC595

| Arduino | 74HC595 |
|---------|---------|
| D12 | DS |
| D11 | ST_CP |
| D13 | SH_CP |

---

### Arduino → MAX7219

| Arduino | MAX7219 |
|---------|---------|
| D10 | DIN |
| D9 | LOAD |
| D8 | CLK |

---

### Pedestrian Button

| Arduino |
|---------|
| D7 |

---

## Countdown Logic

Road timers update continuously.

Example:

Road A Active

A → 30  
B → 30  
C → 60  
D → 90  

Then counts down dynamically.

---

## Simulation

Built and tested in Proteus.

---

## Future Improvements

- Emergency Vehicle Priority
- Adaptive Traffic Timing
- Vehicle Detection Sensors
- Dedicated Pedestrian Countdown
- IoT Monitoring
- RTC Synchronization

---

## Author

Rohan Bhardwaj
