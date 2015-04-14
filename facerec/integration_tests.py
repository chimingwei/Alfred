import Adafruit_BBIO.GPIO as GPIO
from ctypes import cdll

GPIO.setup("P8_10", GPIO.IN)

recognizer = cdll.LoadLibrary('./librecog.so')
recognizer.init()
#recognizer.add_user('taylor')
print "Waiting for user."
GPIO.wait_for_edge("P8_10", GPIO.RISING)
print "User Detected."
detectedUser = recognizer.predict()
print(detectedUser)
