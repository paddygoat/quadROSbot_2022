#!/bin/bash

source /home/pi/ros_catkin_ws/devel/setup.bash && rosrun rosserial_python serial_node.py __name:="MCU_A1" _port:=/dev/ttyUSB1

#  _baud:=115200
