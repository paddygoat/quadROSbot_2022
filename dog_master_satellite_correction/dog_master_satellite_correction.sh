#!/bin/bash
# cd /home/pi/Desktop/ROS_startup_scripts/dog_master_satellite_correction/ && ./dog_master_satellite_correction.sh

RED='\033[0;31m'
BLUE='\033[0;34m'
GREEN='\033[0;32m'
NC='\033[0m' # No Color

printf "${GREEN}nest_master_satellite_correction.sh${NC}\n" 
echo ""

xdotool getactivewindow windowmove 0 100 windowsize 600 370 && lxterminal --command='./terminal_1.sh' &
sleep 5

xdotool getactivewindow windowmove 600 100 windowsize 600 370 && lxterminal --command='./terminal_2.sh' &
sleep 5


