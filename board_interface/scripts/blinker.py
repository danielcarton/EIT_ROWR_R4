#!/usr/bin/env python
import rospy
from std_msgs.msg import Float32
import board as brd
import colorsys
import board as brd

def callback(data, board):
    # rospy.loginfo(rospy.get_caller_id() + "I heard %s", data.data)
    color = colorsys.hsv_to_rgb(data.data,1,1)
    test = [int(color[0] * 255), int(color[1] * 255), int(color[2] * 255)]
    board.send(test)
    
def blinker(board):

    # In ROS, nodes are uniquely named. If two nodes with the same
    # name are launched, the previous one is kicked off. The
    # anonymous=True flag means that rospy will choose a unique
    # name for our 'blinker' node so that multiple blinkers can
    # run simultaneously.
    rospy.init_node('blinker', anonymous=False)

    rospy.Subscriber("pinger", Float32, callback,board)

    # spin() simply keeps python from exiting until this node is stopped
    rospy.spin()

if __name__ == '__main__':
    board = brd.Board()
    board.init('/dev/ttyACM0')
    blinker(board)