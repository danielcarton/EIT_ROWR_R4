import serial
import struct

port = serial.Serial('COM5', baudrate = 230400)
port.write(struct.pack('4B', *[0, 10, 250, 10]))
port.close()  