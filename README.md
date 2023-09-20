# Omnitrix

# Work in Progress  

![IMG_20230619_164351](media/Images/IMG_20230619_164351.jpg) 


This project is meant to be a replica of the Omnitrix from the Ben 10 Classic series in as accurate as posible form. It uses a ESP32 Development Board - NodeMCU-32S2 module, a Round LCD Display GC9A01, a Fermion DFPlayer Pro for sound, a Rotary Encoder with Switch and a tack switch.
(The Rotary Encoder is planned to be changed by Mini Switches for space saving. Also RGB LEDs and battery will to be added)  

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
☐ Use Mini switches instead of Encoder  
☐ Fix transformation time in Deep Sleep mode  
✅ Update ShowSelectSymbols and ShowSymbols with PNGdec  
✅ Power reduction code  
☐ Increase resistance of voltage dividers  
☐ Only enable GPIO outputs at the last moment  
☐ Remove all Serial.println  
☐ Power reduction code for LCD display  
☐ GPIO pins as Vcc for inputs to reduce energy when in Deep Sleep  
☐ RGB LEDs  
☐ Conect 6V battery with switch in 5V pin  
	
# Future Plans:  
☐ Secret combination for Master Control Mode  
☐ Add more interrupts for Deep Sleep  
☐ Smoother animation  
☐ Xtra animation  
☐ Update code with FOTA  
☐ Download additional aliens from a server  
☐ Add Menu that includes:  
- ☐ Time  
- ☐ Battery state  
- ☐ Sound options  
- ☐ Change tranformation Time variables  
- ☐ A Demo Mode  
