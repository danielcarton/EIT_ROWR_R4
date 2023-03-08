#!/usr/bin/env python
# license removed for brevity
import rospy
from std_msgs.msg import String

def pinger():
    pub = rospy.Publisher('pinger', String, queue_size=10)
    rospy.init_node('pinger', anonymous=True)
    rate = rospy.Rate(10) # 10hz
    while not rospy.is_shutdown():
        ping_ = "ping %s" % rospy.get_time()
        rospy.loginfo(ping_)
        pub.publish(ping_)
        rate.sleep()

if __name__ == '__main__':
    try:
        pinger()
    except rospy.ROSInterruptException:
        pass