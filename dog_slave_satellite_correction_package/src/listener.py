#!/usr/bin/env python
# cd /home/pi/ros_catkin_ws/src/dog_slave_satellite_correction_package/src/ ./listener.py

## Simple talker demo that listens to std_msgs/Strings published 
## to the 'chatter' topic

PKG = 'rospy_tutorials' # this package name
import roslib; roslib.load_manifest(PKG)

import rospy
from std_msgs.msg import String

def callback(data):
    rospy.loginfo(rospy.get_caller_id()+"I heard %s",data.data)
    
def listener():

    # in ROS, nodes are unique named. If two nodes with the same
    # node are launched, the previous one is kicked off. The 
    # anonymous=True flag means that rospy will choose a unique
    # name for our 'talker' node so that multiple talkers can
    # run simultaenously.
    rospy.init_node('listener', anonymous=True)

    rospy.Subscriber("chatter", String, callback)

    # spin() simply keeps python from exiting until this node is stopped
    rospy.spin()
        
if __name__ == '__main__':
    listener()
