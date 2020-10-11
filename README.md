# Password keeper 
The password keeper is a toy device for storing the personal password, and type them quickly.
The device can store up to 8 different passwords, no more than 16 chars each with 8 tags no more than 8 chars each.
One of the two buttons on the device allows the user to select the intended password and while the other allows to type it.
One two lines Hitachi HD44780 compatible display allows the user to see the tag associated with the password before typing it.
Relevant features of this project are as follows:
* The main MCU is an AVR ATTINY 85 @16MHz
* Just one MCU GPIO is used to drive the display
* The device presents itself as a keyboard, and it allows using just the USB keyboard interface to update the password DB
![design](/res/board.jpg)

