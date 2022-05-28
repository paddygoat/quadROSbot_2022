#!/bin/bash
# cd /home/pi/Desktop/ROS_startup_scripts/Test_Arduino_ROSSERIAL/toggle_arduino_LED/ && ./toggle_arduino_LED.sh

RED='\033[0;31m'
BLUE='\033[0;34m'
GREEN='\033[0;32m'
NC='\033[0m' # No Color

printf "${GREEN}nest_arduino_tx.sh ....${NC}\n" 
echo ""

xdotool getactivewindow windowmove 0 500 windowsize 600 370 && lxterminal --command='./terminal_1.sh'
sleep 5

# xdotool getactivewindow windowmove 600 500 windowsize 600 370 && lxterminal --command='./terminal_2.sh'
# sleep 10

xdotool getactivewindow windowmove 600 500 windowsize 600 370 &&
sleep 5

printf "${GREEN}All done.${NC}\n"
echo ""
