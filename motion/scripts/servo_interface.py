#!/usr/bin/env python


import rospy
from std_msgs.msg import Float32
import colorsys
# import board as brd

# board = brd.Board()

# set_servo_angles function writes to the servos. Note that the orientation of the servos means a positive angle
# means positive on one servo and negative on the other. The intention is: positive angle means boat goes up
# the float message has something like 
def set_servo_angles(angle): 
    rospy.loginfo(rospy.get_caller_id() + 'I heard %s', angle.data)
    # angle has type FLoat32
    # angle.serialize_numpy
    # angle.serialize
    # angle.deserialize
    # color = colorsys.hsv_to_rgb(0.1,1,1)
    # test = [int(color[0]), int(color[1]), int(color[2])]
    # board.send(test)

def servo_interface():

    # In ROS, nodes are uniquely named. If two nodes with the same
    # name are launched, the previous one is kicked off. The
    # anonymous=True flag means that rospy will choose a unique
    # name for our 'listener' node so that multiple listeners can
    # run simultaneously.
    rospy.init_node('servo_interface', anonymous=False)

    rospy.Subscriber('/motion/cmd_angle', Float32, set_servo_angles)

    # spin() simply keeps python from exiting until this node is stopped
    rospy.spin()

if __name__ == '__main__':
    # board.init('/dev/ttyACM0')
    servo_interface()
