# Omnitrix

# Status
It seems that I ran into some issues with UART and SPI. Currently investigating the problem in my board

# Work in Progress

![IMG_20230619_164351](media/Images/IMG_20230619_164351.jpg) 


This project is meant to be a replica of the Omnitrix from the Ben 10 Classic series and be as accurate as possible. It uses an ESP32 Development Board - NodeMCU-32S2 module, a Round LCD Display GC9A01, a Fermion DFPlayer Pro for sound, Micro Switches implementing an encoder and a tact switch for user input.
RGB LEDs and battery are planned to be added.  

Arduino IDE is used for the software part of the project but could be changed for ESP-IDF in order to use the ULP Coprocessor for better power reduction. For the graphics Bodmer's TFT_eSPI library is used and for the sound the DFRobot_DF1201S library.  


Video showcasing a first test of the project with most of the features included:  

[![IMAGE ALT TEXT HERE](https://img.youtube.com/vi/lkjPJR9iCuw/0.jpg)](https://www.youtube.com/watch?v=lkjPJR9iCuw)

# Instructions
This is a work in progress and the instructions to recreate this project will change.  
  
For now you will need:  
ESP32 Development Board - NodeMCU-32S2 module  
Round LCD Display GC9A01  
Fermion DFPlayer Pro  
2X Mini Metal Speaker w/ Wires - 8 ohm 0.5W  
2X MicroSwitch SPDT ON-(ON) - Long Lever 18mm (A,B on the Schematic)  
MicroSwitch SPDT ON-(ON) - Roller Lever (SW on the Schematic)  
Tact Switch 6x6mm 5mm (ButtonPin on the Schematic)  
Breadboard, jumper wires, 4X 10 kohm resistor
  
Follow the schematic on how to connect the wires. Some soldering will be needed to connect the pin headers and the speakers to the Fermion DFPlayer Pro.  
You can check the [Omnitrix-Test-Files](https://github.com/AA0100000101000001/Omnitrix-Test-Files/) repository to test the features separately before uploading the code (omnitrix folder) to the MCU. These projects are also helpfull if someone wants to use a different board.  
## *Remember to enable PSRAM to avoid Guru Meditation Error*

# Schematic:  
![Schematic_omnitrix_2023-11-26](media/Images/Schematic_omnitrix_2023-11-26.png)

# Current Features:  
- Four states of control (Start mode, Alien Selection mode, Transformation mode, Recharging Mode)
- Array of PNG images decoded into HEX representing the first twelve aliens  
- Animation  
- Sound (commented for now)  
- Ability to go into Deep Sleep Mode after a short time of inactivity  

# To Do List:  
✅ Use Micro switches instead of Encoder  
✅ Power reduction code  
✅ Make Schematic using EasyEDA  
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
☐ Make rotary encoder mechanism with micro switches  
☐ Create the rest of the mechanisms using a CAD program  
☐ Rewrite code to use GPIO interrupts  
☐ Create Omnitrix library for GC9A01 driver based on TFT-eSPI  
☐ Find cheaper components  
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
- ☐ Time  
- ☐ Battery state  
- ☐ Sound options  
- ☐ Option to turn off LEDs  
- ☐ Options for Changing tranformation Time variables  
- ☐ Option for a Demo Mode  
- ☐ Search for Updates  
