# Omnitrix

# Status
| Ordered the PCB shield I made for [ESP32-S3-LCD-1.28](https://www.waveshare.com/wiki/ESP32-S3-LCD-1.28) and if it works then I'll upload the production files |
|----|  

# Work in Progress

![IMG_20230619_164351](media/Images/IMG_20230619_164351.jpg) 


This project is meant to be a replica of the Omnitrix from the Ben 10 Classic series and be as accurate as possible when it comes to operating it like in the series. I started it to learn how to develop a mechatronic project using the ESP32. It started with a ESP32 Development Board - NodeMCU-32S2 module but I found out that there are other boards with an embedded LCD module on the market that are better to use. More about that on Board Comparisons.  
  
In [Omnitrix-Test-Files](https://github.com/AA0100000101000001/Omnitrix-Test-Files) repository I am documenting varius tests for the features.  
I am also planning to develop an ESP-IDF framework version. See the  [ESP-IDF-Omnitrix-Tests](https://github.com/AA0100000101000001/ESP-IDF-Omnitrix-Tests) repository for testing the features (On hold).  

Video showcasing a first test of the project with most of the features included:  

[![IMAGE ALT TEXT HERE](https://img.youtube.com/vi/lkjPJR9iCuw/0.jpg)](https://www.youtube.com/watch?v=lkjPJR9iCuw) 

# Board Comparisons

| Board | Pros | Cons |
|----|----|----|
| [ESP32-S3-Touch-LCD-1.28](https://www.waveshare.com/wiki/ESP32-S3-Touch-LCD-1.28) | LiPo battery charging header | Few free pins to use for peripherals |
| | Touch Display | No Rotary Encoder |
| [M5Dial](https://docs.m5stack.com/en/core/M5Dial)| Rotary Encoder | Bulky size |
| | Buzzer | Can't add support to this code (Hey I should probably use this board in the future) |
| | Under-screen button| Unusual connector for pins |
| | Built-in charging circuit| | 
| | Touch Display | | 
| | Free pins to use for peripherals | |
| | Touch Screen | | 
| [MaTouch ESP32 Rotary](https://www.makerfabs.com/matouch-esp32-s3-rotary-ips-display-with-touch-2-1-st7701.html) | Rotary Encoder | Too big display screen for a watch |  
| | Touch Screen | Few free pins to use for peripherals | 
| [ZX2D10GE01R](https://www.aliexpress.us/item/3256804935405680.html) | Rotary Encoder | Too big display screen for a watch | 
| [ESP32-S3-LCD-1.28](https://www.waveshare.com/wiki/ESP32-S3-LCD-1.28) | A lot of free pins to use for peripherals | No Embedded Rotary Encoder |
| | LiPo battery charging header | Have to make own PCB shield to use pins |
| | Can make 4 pulse rotary encoder to be more accurate | Have to learn more about electronics | 
| | Cheap price | | 
  
I decided to use ESP32-S3-LCD-1.28 for now to learn how to make PCBs and rotary encoders in hopes that the size of the final Omnitrix core can be reduced.

# Instructions
These are instructions on how to use with a Esp32 Development Board to test the code.     
  
You will need:  
* ESP32 Development Board with embedded PSRAM, Currently I have only tested it with [NodeMCU-32S2 module](https://www.waveshare.com/wiki/NodeMCU-32-S2-Kit)  
* [Waveshare Round LCD Display GC9A01](https://www.waveshare.com/1.28inch-lcd-module.htm), I am using the [EC Buying](https://www.aliexpress.com/item/1005004786844308.html) one
* [Fermion DFPlayer Pro](https://www.dfrobot.com/product-2232.html)  
* 2X Mini Metal Speaker w/ Wires - 8 ohm 0.5W  
* 2X MicroSwitch SPDT ON-(ON) - Long Lever 18mm (A,B on the Schematic)  
* MicroSwitch SPDT ON-(ON) - Roller Lever (SW on the Schematic)  
* Tact Switch 6x6mm 5mm (ButtonPin on the Schematic)  
* Breadboard, jumper wires, 4X 10 kohm resistor
  
Follow the schematic on how to connect the wires. Some soldering will be needed to connect the pin headers and the speakers to the Fermion DFPlayer Pro.  

## Schematic:  
![EC Buying Display](media/Images/EC_Buying_Display.png)

## Uploading The Software  
This project uses Arduino IDE to program the Esp32 so you need to [install the ESP32 board to it](https://randomnerdtutorials.com/installing-the-esp32-board-in-arduino-ide-windows-instructions/). It also uses Bodmer's [TFT_eSPI](https://github.com/Bodmer/TFT_eSPI) library for the control of the LCD Display and [PNGdec](https://github.com/bitbank2/PNGdec) for displaying png images. You can configure the LCD Display pins by editing the TFT_eSPI/User_Setup.h file or you can create a configuration file in TFT_eSPI/User_Setups folder and include it in TFT_eSPI/User_Setup_Select.h instead of User_Setup.h. I have added my configurations in the Supported Displays folder.     
```C
/* User_Setup_Select.h */

//#include <User_Setup.h>           // Default setup is root library folder
//#include <User_Setups/Setup302_ESP32S3_GC9A01_TOUCH.h>
#include <User_Setups/Setup303_ESP32S2_GC9A01.h>
//#include <User_Setups/Setup304_ESP32S3_GC9A01.h>
//#include <User_Setups/Setup305_ESP32S3_LCD128.h>
```
   
You can check the [Omnitrix-Test-Files](https://github.com/AA0100000101000001/Omnitrix-Test-Files/tree/main/Test%20files/Used%20For%20Final%20Project) repository to test the features separately before uploading the code (omnitrix folder) to the MCU. These projects are also helpfull if someone wants to use a different board.  

### User Setup
 Inside the User_Setup folder there are some header files for the pin configuration of non LCD Display parts. You can edit the config_CUSTOM.h file for your own pin configuration or use one of other ones.       
Make sure that the pin configuration file is included in `User_Setup.h`. In this file you can configure hardware and software settings.    
For hardware you can choose what kind of rotary encoder is being used, if sound is enabled and how it is implemented and if LEDs are enabled and how they are implemented. Right now the configurations that are supported are: micro switches or rotary encoder for detection of right and left rotation, DFPLAYER_PRO for sound and three pin RGB LEDs. You can also remove features by commenting the `#define X_ENABLED` definitions. `POP_UP_BUTTONS_ENABLED` and one option for rotary encoder are the only essential features.   
For software settings you can configure what kind of animation is being used, if sound will be muted in booting and if demo mode will be enabled (it is not supported right now). The only essential setting is one option for the animation.

## *Remember to enable PSRAM to avoid Guru Meditation Error*

## Tested With
| Board | Micro Switches as Rotary Encoder | Rotary Encoder | Magnetic Rotary Encoder | DFPlayer_Pro Sound | Buzzer Sound | RGB LEDs Tested | Neopixel Ring |
|----|----|----|----|----|----|----|----| 
| [ESP32 Development Board - NodeMCU-32S2 module](https://www.waveshare.com/wiki/NodeMCU-32-S2-Kit) | ✅ | ✅ | | ✅ | | | |


## Dependencies
* This project is developed in Arduino IDE version 2.1.1  
* It uses the arduino-esp32 core by Espressif Systems version 2.0.14  
* TFT_eSPI library version 2.5.34  
* PNGdec library version 1.0.1  
* DFRobot_DF1201S library version 1.0.2 

# Current Features:  
* Settings for testing different hardware
* Four states of control (Start mode, Alien Selection mode, Transformation mode, Recharging Mode)
* Support of the first twelve aliens  
* Animation  
* Sound  
* Ability to go into Deep Sleep Mode after a short time of inactivity  
