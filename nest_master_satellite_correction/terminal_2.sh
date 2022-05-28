#!/bin/bash
# cd /home/pi/Desktop/ROS_startup_scripts/talker_listener_test/ && ./terminal_2.sh

source /home/pi/ros_catkin_ws/devel/setup.bash
export ROS_MASTER_URI=http://master01:11311
# rosrun talker_listener_test listener.py
rosrun nest_master_satellite_correction_package listener.py
