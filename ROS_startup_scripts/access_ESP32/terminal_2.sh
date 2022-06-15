#!/bin/bash


RED='\033[0;31m'
BLUE='\033[0;34m'
GREEN='\033[0;32m'
NC='\033[0m' # No Color

printf "${GREEN}rosrun rosserial_python serial_node.py tcp.${NC}\n" 
echo ""


source /home/pi/ros_catkin_ws/devel/setup.bash && rosrun rosserial_python serial_node.py tcp




