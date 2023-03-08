import serial
import struct

class Board():
  port = None
  data = bytearray()

  COMMAND_SEND_DATA = 1
  COMMAND_RECEIVE_DATA = 2

  def init(self, port):
    self.port = serial.Serial(port = port, baudrate = 230400, timeout = 0.05)
    print('Using port:', self.port.name)

  def send(self, data):
    self.port.write(struct.pack('B3B', self.COMMAND_SEND_DATA, *data))

  def read(self):
    self.data.extend(self.port.read(1024))
    if not len(self.data) or len(self.data) < self.data[0]:
      return None, False
    result = self.data[:self.data[0]]
    self.data.clear()
    return result, True

  def deinit(self):  
    self.port.close()
