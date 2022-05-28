#!/usr/bin/env python

import sys

end = "\n"
RED = "\x1b[1;31m"
# BLUE='\e[44m'
F_LightGreen = "\x1b[92m"
F_Green = "\x1b[32m"
F_LightBlue = "\x1b[94m"
B_White = "\x1b[107m"
NC = "\x1b[0m" # No Color
Blink = "\x1b[5m"


## Simple talker demo that listens to std_msgs/Strings published 
## to the 'chatter' topic

PKG = 'rospy_tutorials' # this package name
import roslib; roslib.load_manifest(PKG)

import rospy
from std_msgs.msg import String

def callback(data):
    sys.stderr.write('\x1b[1;31m' + "Data received:" + '\x1b[0m' + end)
    rospy.loginfo(rospy.get_caller_id()+"I heard %s",data.data)

    
    pub = rospy.Publisher('correction_data_msg2', String, queue_size=10)
    # str1 = "hello world %s"%rospy.get_time()
    str1 = data.data
    sys.stderr.write('\x1b[1;31m' + "Data to publish:" + '\x1b[0m' + end)
    # print("type of data: ",type(str1))
    print(str1)
    # rospy.loginfo(str1)
    pub.publish(str1)

    # r.sleep()
    
def listener():

    # in ROS, nodes are unique named. If two nodes with the same
    # node are launched, the previous one is kicked off. The 
    # anonymous=True flag means that rospy will choose a unique
    # name for our 'talker' node so that multiple talkers can
    # run simultaenously.
    rospy.init_node('listener', anonymous=True)
    rospy.Subscriber("correction_data_msg", String, callback)
    # spin() simply keeps python from exiting until this node is stopped
    rospy.spin()
    
def talker():
    pub = rospy.Publisher('correction_data_msg2', String)
    rospy.init_node('master_talker', anonymous=True)
    r = rospy.Rate(10) # 10hz
    while not rospy.is_shutdown():
        str1 = "hello world %s"%rospy.get_time()
        rospy.loginfo(str1)
        pub.publish(str1)
        r.sleep()
        
def talker_listener():
    rospy.init_node('talker_listener', anonymous=True)
    # pub = rospy.Publisher('correction_data_msg2', String)
    r = rospy.Rate(0.1) # 0.1hz
    # while not rospy.is_shutdown():
    rospy.Subscriber("correction_data_msg", String, callback)
    rospy.spin()
        # str1 = "hello world %s"%rospy.get_time()
        # rospy.loginfo(str1)
        # pub.publish(str1)
        # r.sleep()
        
if __name__ == '__main__':
    talker_listener()

