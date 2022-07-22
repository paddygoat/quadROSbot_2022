#!/bin/bash
# cd /home/paddy/Desktop/RoboController/ && ./run_all_scripts_on_laptop.sh


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

for i in $(seq 1 40); do
  echo -ne "$i\033[0K\r"
  sleep 1
done

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
# rosserial python node on USB0:
gnome-terminal --geometry=59x12-550+0 -- bash -c "sshpass -p "whales" ssh -t pi@192.168.1.134 -o StrictHostKeyChecking=no \
/home/pi/Desktop/ROS_startup_scripts/nest_arduino_rosserial/nest_arduino_tx/./terminal_1.sh \
; exec bash"

sleep 1

# masternest: 192.168.1.134
# rosserial python node on USB1:
gnome-terminal --geometry=59x12-550+0 -- bash -c "sshpass -p "whales" ssh -t pi@192.168.1.134 -o StrictHostKeyChecking=no \
/home/pi/Desktop/ROS_startup_scripts/nest_arduino_rosserial/nest_arduino_tx/./terminal_2.sh \
; exec bash"

sleep 1

# masternest: 192.168.1.134
# rosserial python node on USB2:
gnome-terminal --geometry=59x12-550+0 -- bash -c "sshpass -p "whales" ssh -t pi@192.168.1.134 -o StrictHostKeyChecking=no \
/home/pi/Desktop/ROS_startup_scripts/nest_arduino_rosserial/nest_arduino_tx/./terminal_3.sh \
; exec bash"

sleep 1

# masternest: 192.168.1.134
# rosserial python node on USB3:
gnome-terminal --geometry=59x12-550+0 -- bash -c "sshpass -p "whales" ssh -t pi@192.168.1.134 -o StrictHostKeyChecking=no \
/home/pi/Desktop/ROS_startup_scripts/nest_arduino_rosserial/nest_arduino_tx/./terminal_4.sh \
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

# masternest: 192.168.1.134
gnome-terminal --geometry=59x12-1100+596 -- bash -c "sshpass -p "whales" ssh -t pi@192.168.1.134 -o StrictHostKeyChecking=no \
/home/pi/Desktop/ROS_startup_scripts/./ros_echo_arduino_tx_timings.sh \
; exec bash"

printf "${GREEN}.... all finished.${NC}\n"

exit

# masternest: 192.168.1.134
# This will copy from masternest to user=nobody and is done on nobody's machine.
# scp pi@192.168.1.134:/var/log/* /home/nobody/copy/.



while true; do foo; sleep 2; done

i=0; while [ $i -lt 5 ]; do echo "."; sleep 1; i = $i + 1; done
while((i++ < 20)); do echo "hi \033[0K\r"; sleep 1; done


for i in $(seq 1 40); do
  echo -ne "$i%\033[0K\r"
  sleep 1
done
echo "ended"






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


