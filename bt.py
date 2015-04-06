#import Adafruit_BBIO.UART as UART
#import serial
UART.setup("UART1")

ser = serial.Serial(port = "/dev/ttyO1", baudrate=9600)
ser.close()
ser.open()
while True:
    if ser.isOpen():
       ser.read(12)
ser.close()
