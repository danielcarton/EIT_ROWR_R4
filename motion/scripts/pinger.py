#!/usr/bin/env python
# license removed for brevity
import rospy
from std_msgs.msg import Float32

def pinger():
    pub = rospy.Publisher('pinger', Float32, queue_size=10)
    rospy.init_node('pinger', anonymous=True)
    rate = rospy.Rate(250) # 0.004ms
    hue = 0

    while not rospy.is_shutdown():
        hue += 0.004
        if hue > 1.0:
            hue -= 1.0
        # ping_ = "ping %s" % rospy.get_time()
        # rospy.loginfo(ping_)
        pub.publish(hue)
        rate.sleep()

if __name__ == '__main__':
    try:
        pinger()
    except rospy.ROSInterruptException:
        pass