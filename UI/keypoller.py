# This uses the Adafruit library- let me know if you're using something else
# https://learn.adafruit.com/setting-up-io-python-library-on-beaglebone-black/installation-on-ubuntu

# I'm also using python-uinput. 
# http://tjjr.fi/sw/python-uinput/
# pip install python-uinput

# If these aren't working out let me know, I've found a few alternatives I can try instead.
# These just seemed easiest to work with


import Adafruit_BBIO.GPIO as GPIO
import uinput
import time

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
GPIO.add_event_detect(Button1, GPIO.RISING)
GPIO.add_event_detect(Button2, GPIO.RISING)
GPIO.add_event_detect(Button3, GPIO.RISING)
GPIO.add_event_detect(Button4, GPIO.RISING)
#Loop FOREVER
while True:
	if GPIO.event_detected(Button1):
        	device.emit_click(uinput.KEY_A)
		print "Button 1"
    	if GPIO.event_detected(Button2):
        	device.emit_click(uinput.KEY_D)
		print "Button 2"
    	if GPIO.event_detected(Button3):
        	device.emit_click(uinput.KEY_S)
		print "Button 3"
    	if GPIO.event_detected(Button4):
        	device.emit_click(uinput.KEY_W)
		print "Button 4"
	time.sleep(1.0)	
    #endifs
#end

