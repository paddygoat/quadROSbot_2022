#!/bin/bash

# cd /home/pi/Desktop/ROS_startup_scripts/ && ./access_slave_nest_timing_value.sh
# lxterminal -e "sshpass -p "whales" ssh -Y pi@192.168.1.200 -o StrictHostKeyChecking=no sudo reboot"

sshpass -p "whales" ssh -Y pi@192.168.1.200 -o StrictHostKeyChecking=no
sleep 4 
cd /home/pi/ros_catkin_ws/src/nest_slave_satellite_correction_package/src/ && nano nest_slave_talker_listener.py

