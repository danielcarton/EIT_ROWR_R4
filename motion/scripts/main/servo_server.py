import serial
import struct
import rospy
from std_msgs.msg import Int32MultiArray

def angle_to_pwm(angle):
  assert(0 <= angle and angle <= 180)
  return int(254 * angle / 181 + 1) 

def callback(message, port):
  pwm0 = angle_to_pwm(message.data[0])
  pwm1 = angle_to_pwm(message.data[1])
  pwm2 = angle_to_pwm(message.data[2])
  print("Sending: [%d, %d, %d]" % (pwm0, pwm1, pwm2))
  port.write(struct.pack('4B', *[0, pwm0, pwm1, pwm2]))

port = serial.Serial('COM5', baudrate = 230400)
rospy.init_node('ServoServer', anonymous = False)
rospy.Subscriber("ServoTopic", Int32MultiArray, queue_size = 3, callback = callback,  callback_args = port)
rospy.spin()
