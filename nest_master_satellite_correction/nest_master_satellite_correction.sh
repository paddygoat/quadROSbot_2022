#!/bin/bash
# cd /home/pi/Desktop/ROS_startup_scripts/talker_listener_test/ && ./start_master_talker_listener_test.sh

printf "${GREEN}talker_listener_test.${NC}\n" 
echo ""

xdotool getactivewindow windowmove 0 100 windowsize 600 370 && lxterminal --command='./terminal_1.sh' &
sleep 5

xdotool getactivewindow windowmove 600 100 windowsize 600 370 && lxterminal --command='./terminal_2.sh' &
sleep 5


