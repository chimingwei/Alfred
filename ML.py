import Adafruit_BBIO.GPIO as GPIO

GPIO.setup("P8_10", GPIO.IN)
GPIO.setup("P8_11", GPIO.IN)

while !GPIO.input("P8_11"):
	GPIO.wait_for_edge("P8_10", GPIO.RISING)
	while numUser != 1:
		user,numUser = recognizer.findUser()

	try:
		goog.login(user)
	except Exception, e:
		raise e

	display.add("weather")
	display.add("alarms")
	display.add("calender")
	display.add("traffic")

	# GPIO.wait_for_edge("P8_10", GPIO.FALLING)
	while GPIO.input("P8_10"):
		display.idle()


	display.remove("weather")
	display.remove("alarms")
	display.remove("calender")
	display.remove("traffic")

	goog.logout(user)

GPIO.cleanup()