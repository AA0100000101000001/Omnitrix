# Omnitrix

# Work in Progress  

![IMG_20230619_164351](media/Images/IMG_20230619_164351.jpg) 


This project is meant to be a replica of the Omnitrix from the Ben 10 Classic series and be as accurate as posible. It uses a ESP32 Development Board - NodeMCU-32S2 module, a Round LCD Display GC9A01, a Fermion DFPlayer Pro for sound, a Rotary Encoder with Switch and a tact switch for user input.
The Rotary Encoder is planned to be changed by Micro Switches for reducing space. Also RGB LEDs and battery will be added  

Arduino IDE is used for the software part of the project but could be changed for ESP-IDF in order to use the ULP Coprocessor for better power reduction. For the graphics Bodmer's TFT_eSPI library is used and for the sound the DFRobot_DF1201S library.  


Video showcasing a first test of the project with most of the features included:  

https://uniwagr-my.sharepoint.com/:v:/g/personal/ice19390009_uniwa_gr/EfeOqV_51WFMiZ7XlbTfxEgBar_7Mj2zRy3ds0np9BVFCA?e=VAcc18&nav=eyJyZWZlcnJhbEluZm8iOnsicmVmZXJyYWxBcHAiOiJTdHJlYW1XZWJBcHAiLCJyZWZlcnJhbFZpZXciOiJTaGFyZURpYWxvZyIsInJlZmVycmFsQXBwUGxhdGZvcm0iOiJXZWIiLCJyZWZlcnJhbE1vZGUiOiJ2aWV3In19


# Schematic:  
![omnitrix_schematic_v4](media/Images/omnitrix_schematic_v4.bmp) 

# Current Features:  
- Four states of control (Start mode, Alien Selection mode, Transformation mode, Recharging Mode)
- Array of PNG images decoded into HEX representing the first twelve aliens  
- Animation  
- Sound (commented for now)  
- Ability to go into Deep Sleep Mode after a short time of inactivity (tranformation mode in progress)  
  

# To Do List:  
☐ Use Micro switches instead of Encoder  
☐ Fix transformation time in Deep Sleep mode  
✅ Update ShowSelectSymbols and ShowSymbols with PNGdec  
✅ Power reduction code  
☐ Increase resistance of voltage dividers  
☐ Power reduction code and pin rearangement for LCD display  
☐ GPIO pins as Vcc for inputs to reduce energy when in Deep Sleep  
☐ RGB LEDs  
☐ Only enable GPIO outputs (LEDs) at the last moment  
☐ Remove all Serial.println  
☐ Conect battery with switch in 5V pin  
☐ Make PCB  
	
# Future Plans:  
☐ Make rotary encoder mechanism with micro switches  
☐ Create the rest of the mechanics using a CAD program  
☐ Secret combination for Master Control Mode  
☐ Smoother animation  
☐ Xtra animation  
☐ Update code with FOTA  
☐ Download additional aliens from a server  
☐ Add Menu that includes:  
- ☐ Time  
- ☐ Battery state  
- ☐ Sound options  
- ☐ Options for Changing tranformation Time variables  
- ☐ Option for a Demo Mode  
