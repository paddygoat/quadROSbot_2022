#!/bin/bash
# cd /home/paddy/Desktop/RoboController/ && ./edit_all_talker_listener_py_files.sh


RED='\033[0;31m'
BLUE='\033[0;34m'
GREEN='\033[0;32m'
NC='\033[0m' # No Color


printf "${GREEN}edit master_talker_listener_py files ....${NC}\n"
printf "${GREEN}and copy those files to /home/paddy/copy/ ....${NC}\n"
echo ""

sleep 1

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

sleep 1

gnome-terminal --geometry=95x60-1200+0 -- bash -c " \
sshpass -p "whales" ssh -t pi@192.168.1.161 -o StrictHostKeyChecking=no \
'cd ros_catkin_ws/src/dog_master_satellite_correction_package/src/; \
nano dog_master_talker_listener.py' \
; exec bash"

sleep 1

gnome-terminal --geometry=95x60-250+0 -- bash -c " \
sshpass -p "whales" ssh -t pi@192.168.1.236 -o StrictHostKeyChecking=no \
'cd ros_catkin_ws/src/dog_slave_satellite_correction_package/src/; \
nano dog_slave_talker_listener.py' \
; exec bash"

sshpass -p "whales" scp pi@192.168.1.134:/home/pi/ros_catkin_ws/src/nest_master_satellite_correction_package/src/nest_master_talker_listener.py /home/paddy/copy/.
sshpass -p "whales" scp pi@192.168.1.200:/home/pi/ros_catkin_ws/src/nest_slave_satellite_correction_package/src/nest_slave_talker_listener.py /home/paddy/copy/.

sshpass -p "whales" scp pi@192.168.1.161:/home/pi/ros_catkin_ws/src/dog_master_satellite_correction_package/src/dog_master_talker_listener.py /home/paddy/copy/.
sshpass -p "whales" scp pi@192.168.1.236:/home/pi/ros_catkin_ws/src/dog_slave_satellite_correction_package/src/dog_slave_talker_listener.py /home/paddy/copy/.

# sshpass -p "whales" scp -r pi@192.168.1.236:/home/pi/ros_catkin_ws/src/* /home/paddy/copy/.










