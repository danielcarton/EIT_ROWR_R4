import board
import time
import colorsys

board = board.Board()
board.init('/dev/ttyACM0') # 'COM3'

hue = 0
while True:
  data = colorsys.hsv_to_rgb(hue,1,1)
  test = [int(data[0] * 255), int(data[1] * 255), int(data[2] * 255)]
  board.send(test)

  hue += 0.004
  if hue > 1.0:
    hue -= 1.0

  time.sleep(0.005)

  print("Testing: ", test)
  
board.deinit()
