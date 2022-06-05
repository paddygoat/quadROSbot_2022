#!/bin/bash

source /home/pi/ros_catkin_ws/devel/setup.bash && rosrun rosserial_python serial_node.py __name:="camera_gimbal" _port:=/dev/ttyACM0



