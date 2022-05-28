#!/bin/bash

source /home/pi/ros_catkin_ws/devel/setup.bash && rosrun rosserial_python serial_node.py __name:="toggle_LED" _port:=/dev/ttyACM0

#  _baud:=115200



