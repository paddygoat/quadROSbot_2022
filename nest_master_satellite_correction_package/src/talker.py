#!/usr/bin/env python

import roslib; roslib.load_manifest('rospy_tutorials')
import sys

import rospy
from std_msgs.msg import String

def talker():
    pub = rospy.Publisher('chatter', String)
    rospy.init_node('talker', anonymous=True)
    r = rospy.Rate(10) # 10hz
    while not rospy.is_shutdown():
        for line in sys.stdin:
            sys.stdout.write(line)
        str = "hello world %s"%rospy.get_time()
        rospy.loginfo(str)
        pub.publish(str)
        r.sleep()
        
if __name__ == '__main__':
    try:
        talker()
    except rospy.ROSInterruptException: pass
