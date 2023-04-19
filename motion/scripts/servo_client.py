#!/usr/bin/env python
import rospy
from std_msgs.msg import Float32

rospy.init_node('ServoClient')
pub = rospy.Publisher('/motion/cmd_angle', Float32)
rate = rospy.Rate(10)

while not rospy.is_shutdown():
  data = [180, 0, 0]
  message = Float32(180.0)
  pub.publish(message)
  rate.sleep()