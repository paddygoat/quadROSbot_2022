#!/bin/bash

source /home/pi/ros_catkin_ws/devel/setup.bash && rosrun rosserial_python serial_node.py __name:="MCU_A0" _port:=/dev/ttyUSB0

#  _baud:=115200



