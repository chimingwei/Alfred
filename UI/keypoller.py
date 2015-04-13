
# This uses the Adafruit library- let me know if you're using something else
# https://learn.adafruit.com/setting-up-io-python-library-on-beaglebone-black/installation-on-ubuntu

# I'm also using python-uinput. 
# http://tjjr.fi/sw/python-uinput/
# pip install python-uinput

# If these aren't working out let me know, I've found a few alternatives I can try instead.
# These just seemed easiest to work with


import Adafruit_BBIO.GPIO as GPIO
import uinput

#Fake key setup
#Using WASD because, looking at the source, this doesn't seem
#to support the arrow keys ;_;
device = uinput.Device([
        uinput.KEY_A,
        uinput.KEY_D,
        uinput.KEY_S,
        uinput.KEY_W,
        ])
        
#GPIO Setup
#I don't know what pins you're using, so these are
#just some bullshit ones I made up

Button1 = "P8_14"
Button2 = "P8_15"
Button3 = "P8_16"
Button4 = "P8_17"

GPIO.setup(Button1, GPIO.IN)
GPIO.setup(Button2, GPIO.IN)
GPIO.setup(Button3, GPIO.IN)
GPIO.setup(Button4, GPIO.IN)

#Loop FOREVER
while True:
    if GPIO.input(Button1):
        device.emit_click(uinput.KEY_A)
    if GPIO.input(Button2):
        device.emit_click(uinput.KEY_D)
    if GPIO.input(Button3):
        device.emit_click(uinput.KEY_S)
    if GPIO.input(Button4):
        device.emit_click(uinput.KEY_W)
    #endifs
#end

