import Adafruit_BBIO.UART as UART
import serial
UART.setup("UART1")

ser = serial.Serial(port="/dev/ttyO1", baudrate=9600)
ser.close()
ser.open()
while True:
    if ser.isOpen():
        weatherInfo = ser.read(12)
        weatherInfo.split(':')
        weatherJsonResponse = "{\"humidity\":"+weatherInfo[0]
+",\"temp1\":"+weatherInfo[1]
+",\"temp2\":"+weatherInfo[2]
+",\"pressure\":"+weatherInfo[3]+"}"
ser.close()
