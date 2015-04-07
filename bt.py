#24.0:22.5:22:830
import Adafruit_BBIO.UART as UART
import serial
UART.setup("UART1")
weatherJsonResponse = "nothing"
ser = serial.Serial(port="/dev/ttyO1", baudrate=115200)
ser.close()
ser.open()
while True:
    if ser.isOpen():
        weatherInfo = ser.read(16)
        weatherArray = weatherInfo.split(':')
        weatherJsonResponse = "{\"humidity\":\""+weatherArray[0]+"\",\"temp1\":\""+weatherArray[1]+"\",\"temp2\":\""+weatherArray[2]+"\",\"pressure\":\""+weatherArray[3]+"\"}"
        json_file = open("weather.json", "w")
        json_file.write(weatherJsonResponse)
        json_file.close()
ser.close()

