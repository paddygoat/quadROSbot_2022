#!/bin/bash
# cd ~/Desktop/ROS_startup_scripts && bash nest_run_all_scripts.sh

RED='\033[0;31m'
BLUE='\033[0;34m'
GREEN='\033[0;32m'
NC='\033[0m' # No Color

pgrep bash | xargs -n1 pstree -p -c
# killall bash 
# pgrep bash | xargs -n1 pstree -p -c | grep -o '[0-9]\+' | xargs kill
# pgrep bash | xargs -n1 pstree -p -c | grep -v \- | grep -o '[0-9]\+' | xargs kill

# printf "${GREEN}Reboot the Raspberry pis....${NC}\n"
# sh ./reboot_computers_on_network.sh

source /opt/ros/melodic/setup.bash


printf "${GREEN}Run all scripts${NC}\n" 

xdotool getactivewindow windowmove 0 100 windowsize 600 370 && ./reboot_computers_on_network.sh

sleep 40

# cd ~/Desktop/ROS_startup_scripts/ && bash T265_Tracking_Module.sh
printf "${GREEN}start nest_satellite_correction.sh ....${NC}\n"
echo ""

cd /home/pi/Desktop/ROS_startup_scripts/nest_master_satellite_correction/ && ./nest_master_satellite_correction.sh
sleep 5
xdotool getactivewindow windowmove 1200 100 windowsize 600 370 && lxterminal -e "sshpass -p "whales" ssh -Y pi@192.168.1.200 -o StrictHostKeyChecking=no ./nest_slave_satellite_correction.sh"
sleep 5
xdotool getactivewindow windowmove 0 800 windowsize 600 370 && cd /home/pi/Desktop/ROS_startup_scripts/nest_arduino_rosserial/nest_arduino_tx/ && ./nest_arduino_tx.sh
sleep 5




# sh ./find_computers_on_network.sh

# printf "${GREEN}Start dog and snout nodes ....${NC}\n"
# echo ""
# sleep 10

# sh ./dog_and_snout_ROS_nodes.sh

# printf "${GREEN}Run combined dog and snout for GPS and heading data ....${NC}\n"
# echo ""
# sleep 10

# sh ./run_combined_dog_snout.sh

pgrep bash | xargs -n1 pstree -p -c



