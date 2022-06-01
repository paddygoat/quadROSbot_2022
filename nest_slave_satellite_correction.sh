#!/bin/bash
# cd /home/pi/ && ./nest_slave_satellite_correction.sh
# A copy of this file must be in the home directory!

RED='\033[0;31m'
BLUE='\033[0;34m'
GREEN='\033[0;32m'
NC='\033[0m' # No Color

source /home/pi/ros_catkin_ws/devel/setup.bash
export ROS_MASTER_URI=http://masternest:11311
rosrun nest_slave_satellite_correction_package nest_slave_talker_listener.py
