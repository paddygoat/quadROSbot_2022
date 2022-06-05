#!/bin/bash
# cd /home/tegwyn/Desktop/ROS_startup_scripts/ && bash reboot_computers_on_network.sh
# cd /home/pi/Desktop/ROS_startup_scripts/ && bash reboot_computers_on_network.sh

# ping dog01.local -c 1
# ping nest01.local -c 1

RED='\033[0;31m'
BLUE='\033[0;34m'
GREEN='\033[0;32m'
NC='\033[0m' # No Color

printf "${GREEN}slavedog ip address:"
echo ""

# sshpass -p "whales" ssh -Y pi@192.168.1.236

lxterminal -e "sshpass -p "whales" ssh -Y pi@192.168.1.236 -o StrictHostKeyChecking=no sudo reboot"
