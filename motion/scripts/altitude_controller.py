#!/usr/bin/env python

import rospy
from geometry_msgs.msg import PoseStamped
from std_msgs.msg import Float32
from geometry_msgs.msg import Twist

class PIDController:

    def __init__(self, kp, ki, kd, r, i_min=-float('inf'), i_max=float('inf')):
        self.kp = kp
        self.ki = ki
        self.kd = kd
        self.r = r
        self.i_min = i_min
        self.i_max = i_max
        self.error = 0
        self.integral = 0
        self.derivative = 0
        self.prev_error = 0

    def update(self, feedback_value, dt):
        self.error = self.r - feedback_value
        self.integral += self.error * dt
        self.integral = self._integral_windup(self.integral)
        self.derivative = (self.error - self.prev_error) / dt
        self.prev_error = self.error

        return (self.kp * self.error) + (self.ki * self.integral) + (self.kd * self.derivative)

    def _integral_windup(self, integral):
        if integral < self.i_min:
            return self.i_min
        elif integral > self.i_max:
            return self.i_max
        else:
            return integral
        
class AltitudeController:

    def __init__(self, kp, ki, kd, r, i_min=-float('inf'), i_max=float('inf')):
        self.pid = PIDController(kp, ki, kd, r, i_min, i_max)
        # self.cmd_vel_pub = rospy.Publisher('/cmd_vel', Twist, queue_size=1)   
        self.cmd_angle_pub = rospy.Publisher('/motion/cmd_angle', Float32, queue_size=1)   ## Originally Twist by ChatGPT
        rospy.Subscriber('/pose_stamped', PoseStamped, self.pose_stamped_callback)
        self.feedback_value = 0
        self.prev_time = rospy.Time.now()

    def pose_stamped_callback(self, msg):
        self.feedback_value = msg.pose.position.z
        # dt = (rospy.Time.now() - self.prev_time).to_sec()
        dt = (msg.header.stamp.secs - self.prev_time).to_sec()
        u = self.pid.update(self.feedback_value, dt)    # named error by ChatGPT
        cmd_angle_msg = Float32()
        cmd_angle_msg.data = u
        # cmd_vel_msg = Twist()
        # cmd_vel_msg.linear.z = error
        self.cmd_angle_pub.publish(cmd_angle_msg)
        # self.prev_time = rospy.Time.now()
        self.prev_time = msg.header.stamp.secs
        

if __name__ == '__main__':
    rospy.init_node('altitude_controller')
    kp = rospy.get_param('/controllers/altitude_controller/kp', 0.1)
    ki = rospy.get_param('/controllers/altitude_controller/ki', 0.0)
    kd = rospy.get_param('/controllers/altitude_controller/kd', 0.0)
    r = rospy.get_param('/controllers/altitude_controller/r', 5.0)
    min_angle = rospy.get_param('/controllers/altitude_controller/min_angle', -40)
    max_angle = rospy.get_param('/controllers/altitude_controller/max_angle', 40)
    controller = AltitudeController(kp, ki, kd, r, -40, 40)
    rospy.spin()