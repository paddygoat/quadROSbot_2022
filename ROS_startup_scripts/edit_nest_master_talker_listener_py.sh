#!/bin/bash
# cd /home/paddy/Desktop/RoboController/ && ./edit_nest_master_talker_listener_py.sh


RED='\033[0;31m'
BLUE='\033[0;34m'
GREEN='\033[0;32m'
NC='\033[0m' # No Color


printf "${GREEN}edit_nest_master_talker_listener_py ....${NC}\n"
echo ""
sleep 1
# sshpass -p "whales" ssh -t pi@192.168.1.134 -o StrictHostKeyChecking=no && \
# sleep 5 && \
# cd ros_catkin_ws/src/nest_master_satellite_correction_package/src/ && \
# nano nest_master_talker_listener.py

#  scp://pi@192.168.1.134//home/pi/ros_catkin_ws/src/nest_master_satellite_correction_package/src/nest_master_talker_listener.py


# Syntax : ssh -i pemfile.pem user_name@ip_address 'command_1 ; command 2; command 3'

# sshpass -p "whales" ssh -t pi@192.168.1.134 -o StrictHostKeyChecking=no 'nano ros_catkin_ws/src/nest_master_satellite_correction_package/src/nest_master_talker_listener.py'

# sshpass -p "whales" ssh -t pi@192.168.1.134 -o StrictHostKeyChecking=no \
# 'cd ros_catkin_ws/src/nest_master_satellite_correction_package/src/; \
# nano nest_master_talker_listener.py'

gnome-terminal --geometry=95x60-1200+0 -- bash -c " \
sshpass -p "whales" ssh -t pi@192.168.1.134 -o StrictHostKeyChecking=no \
'cd ros_catkin_ws/src/nest_master_satellite_correction_package/src/; \
nano nest_master_talker_listener.py' \
; exec bash"

sleep 1

gnome-terminal --geometry=95x60-250+0 -- bash -c " \
sshpass -p "whales" ssh -t pi@192.168.1.200 -o StrictHostKeyChecking=no \
'cd ros_catkin_ws/src/nest_slave_satellite_correction_package/src/; \
nano nest_slave_talker_listener.py' \
; exec bash"
