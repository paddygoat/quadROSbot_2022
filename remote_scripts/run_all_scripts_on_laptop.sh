#!/bin/bash
# cd /home/paddy/Desktop/RoboController/ && ./run_all_scripts_on_laptop.sh


# masternest = ssh -Y pi@192.168.1.134
# slave01 = ssh -Y pi@192.168.1.200 -o StrictHostKeyChecking=no

RED='\033[0;31m'
BLUE='\033[0;34m'
GREEN='\033[0;32m'
NC='\033[0m' # No Color

killall bash

printf "${GREEN}Start the system ....${NC}\n"
echo ""

gnome-terminal --geometry=59x3-1200+0 -- bash -c "sshpass -p "whales" ssh -t pi@192.168.1.134 -o StrictHostKeyChecking=no \
sudo reboot \
; exec bash"

gnome-terminal --geometry=59x3-1200+0 -- bash -c "sshpass -p "whales" ssh -t pi@192.168.1.200 -o StrictHostKeyChecking=no \
sudo reboot \
; exec bash"

gnome-terminal --geometry=59x3-1200+0 -- bash -c "sshpass -p "whales" ssh -t pi@192.168.1.161 -o StrictHostKeyChecking=no \
sudo reboot \
; exec bash"

gnome-terminal --geometry=59x3-1200+0 -- bash -c "sshpass -p "whales" ssh -t pi@192.168.1.236 -o StrictHostKeyChecking=no \
sudo reboot \
; exec bash"

sleep 40

# First row of terminals:

# masternest: 192.168.1.134 .... starts up Roscore:
gnome-terminal --geometry=59x12-1100+0 -- bash -c "sshpass -p "whales" ssh -t pi@192.168.1.134 -o StrictHostKeyChecking=no \
/home/pi/Desktop/ROS_startup_scripts/nest_master_satellite_correction/./terminal_1.sh \
; exec bash"

sleep 1

# masternest: 192.168.1.134
gnome-terminal --geometry=59x12-1100+0 -- bash -c "sshpass -p "whales" ssh -t pi@192.168.1.134 -o StrictHostKeyChecking=no \
/home/pi/Desktop/ROS_startup_scripts/nest_master_satellite_correction/./terminal_2.sh \
; exec bash"

sleep 5

# masternest: 192.168.1.134
gnome-terminal --geometry=59x12-550+0 -- bash -c "sshpass -p "whales" ssh -t pi@192.168.1.134 -o StrictHostKeyChecking=no \
/home/pi/Desktop/ROS_startup_scripts/nest_arduino_rosserial/nest_arduino_tx/./terminal_1.sh \
; exec bash"

sleep 1

# slavenest: 192.168.1.200
gnome-terminal --geometry=59x12-0+0 -- bash -c "sshpass -p "whales" ssh -t pi@192.168.1.200 -o StrictHostKeyChecking=no \
./nest_slave_satellite_correction.sh \
; exec bash"

sleep 1

# Second row of terminals:

# masterdog: 192.168.1.161  .... starts up Roscore:
gnome-terminal --geometry=59x12-1100+300 -- bash -c "sshpass -p "whales" ssh -t pi@192.168.1.161 -o StrictHostKeyChecking=no \
/home/pi/Desktop/ROS_startup_scripts/dog_master_satellite_correction/./terminal_1.sh \
; exec bash"

sleep 1

# masterdog: 192.168.1.161
gnome-terminal --geometry=59x12-1100+300 -- bash -c "sshpass -p "whales" ssh -t pi@192.168.1.161 -o StrictHostKeyChecking=no \
/home/pi/Desktop/ROS_startup_scripts/nest_master_satellite_correction/./terminal_2.sh \
; exec bash"

sleep 5
# masterdog: 192.168.1.161
gnome-terminal --geometry=59x12-550+300 -- bash -c "sshpass -p "whales" ssh -t pi@192.168.1.161 -o StrictHostKeyChecking=no \
/home/pi/Desktop/ROS_startup_scripts/dog_arduino_rosserial/dog_arduino_rx/./terminal_1.sh \
; exec bash"

sleep 1
# slavedog: 192.168.1.236
gnome-terminal --geometry=59x12-0+300 -- bash -c "sshpass -p "whales" ssh -t pi@192.168.1.236 -o StrictHostKeyChecking=no \
./dog_slave_satellite_correction.sh \
; exec bash"

# Third row of terminals:

printf "${GREEN}.... all finished.${NC}\n"
exit











gnome-terminal --geometry=70x35-800+0 -- bash -c "sshpass -p "whales" ssh -t pi@192.168.1.134 -o StrictHostKeyChecking=no ./test_1.sh     ; exec bash"

# sshpass -p "whales" ssh -t pi@192.168.1.134 -o StrictHostKeyChecking=no ./test_1.sh

# source /opt/ros/melodic/setup.bash



gnome-terminal --geometry=70x35-800+0 -- bash -c "sshpass -p "whales" ssh -Y pi@masternest.local -o StrictHostKeyChecking=no \
&& source /opt/ros/melodic/setup.bash \
&& roscore \
; exec bash"


sshpass -p "whales" ssh -Y pi@masternest.local -o StrictHostKeyChecking=no ./test_1.sh
sshpass -p "whales" ssh -Y pi@masternest.local -o StrictHostKeyChecking=no ./nest_run_all_scripts.sh



gnome-terminal --geometry=70x35-800+0 -- bash -c "sshpass -p "whales" ssh -Y pi@masternest.local -o StrictHostKeyChecking=no \
/home/pi/Desktop/ROS_startup_scripts/./nest_run_all_scripts.sh \
; exec bash"

ssh -Y pi@masternest.local
gnome-terminal --geometry=70x35-0+0 -- bash -c "sshpass -p "whales" ssh -Y pi@masternest.local && sleep 5 && cd /home/pi/Desktop/ROS_startup_scripts ; exec bash"

# masternest:
gnome-terminal --geometry=70x35-0+0 -- bash -c "sshpass -p "whales" ssh -Y pi@192.168.1.134 && cd /home/pi/Desktop/ROS_startup_scripts/talker_listener_test/ && ./termianl_1.sh ; exec bash"
gnome-terminal --geometry=70x35-600+0 -- bash -c "sshpass -p "whales" ssh -Y pi@192.168.1.134 && cd /home/pi/Desktop/ROS_startup_scripts/talker_listener_test/ && ./termianl_2.sh ; exec bash"
gnome-terminal --geometry=70x35-600+0 -- bash -c "sshpass -p "whales" ssh -Y pi@192.168.1.134 && cd /home/pi/Desktop/ROS_startup_scripts/talker_listener_test/ ; exec bash"
sleep 2

# masterdog: 192.168.1.161
# slavedog: 192.168.1.236


# slavenest: 192.168.1.200
gnome-terminal --geometry=70x35-800+0 -- bash -c "sshpass -p "whales" ssh -Y pi@192.168.1.200 -o StrictHostKeyChecking=no \
/home/pi/Desktop/ROS_startup_scripts/talker_listener_test/./start_master_talker_listener_test.sh \
; exec bash"

gnome-terminal --geometry=70x35-1600+0 -- bash -c "sshpass -p "whales" ssh -Y pi@$slave -o StrictHostKeyChecking=no \
/home/pi/Desktop/ROS_startup_scripts/Test_Arduino_ROSSERIAL/./toggle_arduino_LED.sh \
; exec bash"


