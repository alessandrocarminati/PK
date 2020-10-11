# Passwork keeper database updater
Straightforward utility. It gets a password file as argument and pushes it into the device using keyboard LEDs.
The three LEDs on the keyboard are used as lines of synchronous serial communication.
**makedb.c**  can be used to create a new database
**update.c** is the utility used for the actual update

*Example*
    [edit makedb.c and put your password data. Remeber data is meant to be usb keyboard scancodes. Refer to usb_hid_keys.h]
    gcc -o makedb makedb.c
    ./makedb >data
    gcc -o updater updater.c
    ./updater data


