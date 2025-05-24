# Arduino Alarm Clock
This repository contains the code, schematics, and pictures of my custom made Arduino-based alarm clock. Primarily uses the Arduino programming language (.ino) with a hint of C++ for file management through header files.

![Image of alarm clock](https://github.com/jayinterrobang/arduino-alarm/blob/main/images/alarm-clock-image-1.JPG)

## Features

- **Custom time setting**
    - Allows the user to sync the alarm clock with their current timezone.
- **Long-lasting time accuracy**
    - After setting the time, the displayed time will not deviate more than 2 seconds from the actual time for more than 5 hours.
- **Alarms**
    - Lets the user set an alarm for any time within 24 hours.
    - Lets the user snooze any alarm currently going off.

#### Future Features (in order of priority):
- Multiple alarms
- Automatic time syncing


## Circuit

### Components Used

| Component | Product Link | Alternatives |
|----------|-----------|-------|
| Arduino UNO R3 CH340 | [Circuitrocks](https://circuit.rocks/products/arduino-uno-r3-ch340?srsltid=AfmBOorfvkTrYXO3PM-1DmKzO5XjVEcX1r3ql2juuECp4jREYsKT1It7) | A normal Arduino UNO R3 also works. |
| 16x2 LCD with I2C Adaptor | [Makerlab](https://www.makerlab-electronics.com/products/16x2-lcd-display-i2c-white-on-blue?srsltid=AfmBOoo7WMoDt_drLrZEz3xNRIUCMjZNSTRs382Evmy1ZjbHN98qeva8) | Bigger LCDs will work, but will require a different library from the one used in the code |
| PS2 Joystick Sensor Module 5V | [Makerlab](https://www.makerlab-electronics.com/products/ps2-joystick-sensor-module-5v?srsltid=AfmBOoqMCSAS8wYtjJ3GqIKvTer6O2OKeIfYBth8jfc1SdGsg9M107M3) | Any other joystick module will work |
| Full Breadboard | [Makerlab](https://www.makerlab-electronics.com/products/solder-less-pcb-breadboard-syb-mb102-830-800-400-170-tie-points-circuit-solderless-half-full-size?srsltid=AfmBOoqObq_0juRriIgIwXXEIq-aPE1NXWbfMbkLIs-3F_PujRlwKLGX) | Smaller breadboards will possibly work too |

### Circuit Diagram
![Circuit diagram of project (made in TinkerCAD)](https://github.com/jayinterrobang/arduino-alarm/blob/main/images/circuit-diagram.png "Circuit diagram")

#### NOTES

In the circuit diagram, the joystick component is displayed as 3 separate components: two potentiometers and a push button. The left potentiometer is in place of the VRx connection of the joystick, while the right potentiometer is in place of the VRy connection. The push button is in place of the switch connection. In other words, the connections of the joystick are displayed below:

| Connection | Port |
| --- | --- |
| VCC | 5V |
| GND | GND |
| VRx | A1 |
| VRy | A0 |
| SW | 10 |

## How it Works
After connecting the arduino USB adaptor to a power source, the alarm will turn on and initially be in Display Mode. At first, the time will be set to exactly 12:00 AM.

#### Display Mode

The main purpose of display mode is to simply **display the time**. Many options are available from this point:

- *By quickly pressing the button*, the alarm clock will shift into *Alarm Setting Mode*, explained in more detail below.
- *By holding the button for more than half a second*, the alarm clock will shift into *Time Setting Mode*, explained in more detail below.

#### Time Setting Mode

In Time Setting mode, you can freely set the time of the alarm clock. By increasing the voltage of VRx, we can increment the minutes by one. By decreasing the voltage of VRy, we can increment the hours by one. The joystick in the alarm clock is placed such that the connections are on the left side. This way, the controls are simplified to:

- *By moving the joystick right*, we increment the current hour by one.
- *By moving the joystick left*, we decrement the current hour by one.
- *By moving the joystick up*, we increment the current minute by one.
- *By moving the joystick down*, we decrement the current minute by one.
- *By pressing the joystick*, the alarm clock will shift back into Display Mode.
#### Alarm Setting Mode

In alarm setting mode, we can freely set the alarm time of the alarm clock. The alarm will ring the **next time the alarm passes that time**. See description of the Time Setting Mode if you want to know the controls of how to increase or decrease the current time.

#### Alarm Mode

When the current time is the same as the alarm time, the alarm clock will shift into alarm mode. The buzzer will vibrate until you do one of two actions:

- *By quickly pressing the button*, the alarm clock will snooze the alarm. This automatically sets a new alarm 5 minutes later.
- *By holding the button for more than half a second*, the alarm will halt completely. 

## Pictures

#### Outside
![Closeup of alarm clock](https://github.com/jayinterrobang/arduino-alarm/blob/main/images/closeup.JPG)
![Farther perspective of alarm clock](https://github.com/jayinterrobang/arduino-alarm/blob/main/images/alarm-clock-image-2.JPG)
![Front view of alarm clock](https://github.com/jayinterrobang/arduino-alarm/blob/main/images/alarm-clock-image-3.JPG)

#### Interior / Circuitry
![Top-down view of alarm clock](https://github.com/jayinterrobang/arduino-alarm/blob/main/images/interior-image-2.JPG)
![Other perspective of interior, showing how the front components are attached](https://github.com/jayinterrobang/arduino-alarm/blob/main/images/interior-image-4.JPG)

