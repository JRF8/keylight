# keylight
A utility to control the keyboard backlight on a MacBook Pro in Linux

## Summary
This program is used to modify /sys/class/leds/smc::kbd_backlight/brightness. To do so, the binary is compiled with SUID privileges.
It increments or decrements by 15, with a range of 0 to the max value defined in /sys/class/leds/smc::kbd_backlight/max_brightness

## Usage
keylight [action]

Actions:

up: increase the keyboard backlight brightness

down: decrease the keyboard backlight brightness

## Installation

Clone this repository, cd into keylight, and run:
sudo make install

You can then run 'make clean' to clean up object files, or run sudo make uninstall to uninstall.

