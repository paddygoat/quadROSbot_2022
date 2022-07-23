#!/bin/bash
# cd /home/paddy/Desktop/RoboController/ && ./reboot_computers_on_network.sh


RED='\033[0;31m'
BLUE='\033[0;34m'
GREEN='\033[0;32m'
NC='\033[0m' # No Color

killall bash

printf "${GREEN}Reboot the whole system ....${NC}\n"
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

sleep 5

# killall bash

