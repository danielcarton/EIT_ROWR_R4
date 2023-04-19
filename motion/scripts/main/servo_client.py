import rospy
from std_msgs.msg import Int32MultiArray

rospy.init_node('ServoClient')
pub = rospy.Publisher('ServoTopic', Int32MultiArray, queue_size=10)
rate = rospy.Rate(10)

while not rospy.is_shutdown():
  data = [0, 180, 0]
  message = Int32MultiArray(data = data)
  pub.publish(message)
  rate.sleep()
