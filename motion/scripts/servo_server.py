#!/usr/bin/env python


import serial
import struct
import rospy
from std_msgs.msg import Float32

def angle_to_pwm(angle):
  angle.data -= 50
  assert(0 <= angle and angle <= 180)
  return int(254 * angle / 181 + 1)

def callback(message, port):
  pwm = angle_to_pwm(message.data)
  port.write(struct.pack('4B', *[0, pwm, 256 - pwm, 0]))

def servo_server():
  port = serial.Serial('/dev/ttyUSB0', baudrate = 230400)
  rospy.init_node('ServoServer', anonymous = False)
  rospy.Subscriber("/motion/cmd_angle", Float32, callback = callback,  callback_args = port)
  rospy.spin()

if __name__ == '__main__':
    # board.init('/dev/ttyACM0')
    servo_server()
