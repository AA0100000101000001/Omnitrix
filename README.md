# Omnitrix

# Status
| Currently working on adding support for ESP32-S3 ROUND LCD 1.28.|
|----|  

# Work in Progress

![IMG_20230619_164351](media/Images/IMG_20230619_164351.jpg) 


This project is meant to be a replica of the Omnitrix from the Ben 10 Classic series and be as accurate as possible. I started it to learn how to develop a mechatronic project using the ESP32. It uses an ESP32 Development Board - NodeMCU-32S2 module, a Round LCD Display GC9A01, a Fermion DFPlayer Pro for sound and switches for user input.
RGB LEDs and battery are planned to be added.  

I am also planning to develop an ESP-IDF framework version. See the  [ESP-IDF-Omnitrix-Tests](https://github.com/AA0100000101000001/ESP-IDF-Omnitrix-Tests) repository for testing the features (In progress).  

Video showcasing a first test of the project with most of the features included:  

[![IMAGE ALT TEXT HERE](https://img.youtube.com/vi/lkjPJR9iCuw/0.jpg)](https://www.youtube.com/watch?v=lkjPJR9iCuw) 

# Instructions
This is a work in progress and the instructions to recreate this project will change. Support for more boards will be added  
  
For now you will need:  
* ESP32 Development Board - NodeMCU-32S2 module  
* Round LCD Display GC9A01, I am now using the [EC Buying](https://www.aliexpress.com/item/1005004786844308.html) one  
* Fermion DFPlayer Pro  
* 2X Mini Metal Speaker w/ Wires - 8 ohm 0.5W  
* 2X MicroSwitch SPDT ON-(ON) - Long Lever 18mm (A,B on the Schematic)  
* MicroSwitch SPDT ON-(ON) - Roller Lever (SW on the Schematic)  
* Tact Switch 6x6mm 5mm (ButtonPin on the Schematic)  
* Breadboard, jumper wires, 4X 10 kohm resistor
  
Follow the schematic on how to connect the wires. Some soldering will be needed to connect the pin headers and the speakers to the Fermion DFPlayer Pro.  
You can check the [Omnitrix-Test-Files](https://github.com/AA0100000101000001/Omnitrix-Test-Files/) repository to test the features separately before uploading the code (omnitrix folder) to the MCU. These projects are also helpfull if someone wants to use a different board.  
## *Remember to enable PSRAM to avoid Guru Meditation Error*

## Support
* This project is developed in Arduino IDE version 2.1.1  
* It uses the arduino-esp32 core by Espressif Systems version 2.0.14  
* TFT_eSPI library version 2.5.34  
* PNGdec library version 1.0.1  
* DFRobot_DF1201S library version 1.0.2 

# Schematic:  
![EC Buying Display](media/Images/EC_Buying_Display.png)
I have also made one with the Waveshare Display in the /media/Images/ folder.

# Current Features:  
* Four states of control (Start mode, Alien Selection mode, Transformation mode, Recharging Mode)
* Support of the first twelve aliens  
* Animation  
* Sound  
* Ability to go into Deep Sleep Mode after a short time of inactivity  

# To Do List:  
✅ Use Micro switches instead of Encoder  
✅ Power reduction code  
✅ Make Schematic using EasyEDA  
✅ Rewrite code to use GPIO interrupts  
☐ Add support for touch lcd  
☐ Make rotary encoder mechanism with micro switches  
☐ Find cheaper components  
☐ Create Omnitrix graphics library for GC9A01 driver that uses transparent images  
☐ Power reduction code and pin rearangement for LCD display   
☐ GPIO pins as Vcc for inputs to reduce energy when in Deep Sleep  
☐ RGB LEDs  
☐ Increase resistance of voltage dividers  
☐ Only enable GPIO outputs (LEDs) at the last moment  
☐ Test current for LED PCB  
☐ Make RGB LED PCB  
☐ Reduce size and memory usage of program sketch  
☐ Remove all Serial.println  
☐ Conect battery with switch in 5V pin  
☐ Make PCB  
	
# Future Plans:  
☐ Create the rest of the mechanisms using a CAD program  
☐ Add energy system  
☐ Secret combination input for Master Control Mode  
☐ Smoother animation  
☐ Xtra animation  
☐ Download aliens from a server  
☐ Update code with FOTA  
☐ Rechargable battery  
☐ Download additional aliens from a server  
☐ Add motor to elevate display (for fun!)  
☐ Make Omnitrix Microcontroller based on ESP32 chip  
☐ Add Menu that includes:  
* ☐ Time  
* ☐ Battery state  
* ☐ Sound options  
* ☐ Option to turn off LEDs  
* ☐ Options for Changing tranformation Time variables  
* ☐ Low power mode disable/enable (ULP coprossesor use in ESP-IDF)  
* ☐ Demo Mode disable/enable  
* ☐ Search for Updates  
