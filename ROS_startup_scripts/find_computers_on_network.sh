#!/bin/bash
# 
# sudo apt-get install sshpass
# cd /home/paddy/Desktop/RoboController/ && bash find_computers_on_network.sh
# cd /home/pi/Desktop/ROS_startup_scripts/ && bash find_computers_on_network.sh

# ping dog01.local -c 1
# ping nest01.local -c 1
# ping master01.local -c 1

# ping slave01.local -c 1
# 192.168.1.200

RED='\033[0;31m'
BLUE='\033[0;34m'
GREEN='\033[0;32m'
NC='\033[0m' # No Color

# slave01:
lxterminal --geometry=70x35 -e "sshpass -p "whales" ssh -Y pi@192.168.1.200 -o StrictHostKeyChecking=no ./start_slave_talker_listener_test.sh"
lxterminal --command='sshpass -p "whales" ssh -Y pi@192.168.1.200 | ./start_slave_talker_listener_test.sh'



echo "dog01 ip address:"
dog=$(ping -c 1 dog01.local | grep "64 bytes from " | awk '{print $4}' | cut -d":" -f1)
echo $dog
echo ""

echo "nest01 ip address:"
nest=$(ping -c 1 nest01.local | grep "64 bytes from " | awk '{print $4}' | cut -d":" -f1)
echo $nest

# printf "${GREEN}Now generate some keys .... ${NC}\n"
echo ""

# ssh-keygen -f "/home/paddy/.ssh/known_hosts" -R $dog
# ssh-keygen -f "/home/paddy/.ssh/known_hosts" -R $nest

sleep 2

printf "${GREEN}Now open some more terminals ....${NC}\n"
echo ""

lxterminal --geometry=70x35 -e "sshpass -p "piratesrus" ssh -Y pi@$nest -o StrictHostKeyChecking=no ./str2str.sh"

sleep 2

printf "${GREEN}Next terminal ....${NC}\n"
echo ""

sleep 2

lxterminal --geometry=70x35 -e "sshpass -p "piratesrus" ssh -Y pi@$dog -o StrictHostKeyChecking=no ./str2str.sh"

printf "${GREEN}Both dog and nest terminals should now be open and running str2str.${NC}\n"
echo ""



















# gnome-terminal --geometry=70x35 -- bash -e "sshpass -p "piratesrus" ssh -Y pi@$dog -o StrictHostKeyChecking=no \
# ./str2str.sh \
# ; exec bash"


# Usage:
#   lxterminal [Options...] - LXTerminal is a terminal emulator

# Options:
#   -e, --command=STRING             Execute the argument to this option inside the terminal
#   --geometry=COLUMNSxROWS          Set the terminal's size
#   -l, --loginshell                 Execute login shell
#   -t, -T, --title=,
#     --tabs=NAME[,NAME[,NAME[...]]] Set the terminal's title
#   --working-directory=DIRECTORY    Set the terminal's working directory
#   --no-remote                      Do not accept or send remote commands
#   -v, --version                    Version information







# --tab -e "bash -c 'date; read -n1' " \
# --tab -e "bash -c 'sleep 5; date; read -n1' " \
# --tab -e "bash -c 'sleep 5; echo $dog; read -n1' " \
# --tab


# sshpass -p "piratesrus" ssh -Y pi@$nest -o StrictHostKeyChecking=no


# $ ssh -o UserKnownHostsFile=/dev/null -o StrictHostKeyChecking=no <user>@<host>


# echo "Finished"
# for ip in $(seq 1 14); do ping -c 1 172.20.10.$ip>/dev/null; 
    # [ $? -eq 0 ] && echo "172.20.10.$ip UP" || : ;
# done

# 172.20.10.1
# nmap -sP 172.20.10.0/24

# nmap -sn 192.168.1.0/24

###
# Starting Nmap 7.60 ( https://nmap.org ) at 2021-02-18 09:26 GMT
# Nmap scan report for _gateway (172.20.10.1)
# Host is up (0.010s latency).
# Nmap scan report for nobody (172.20.10.12)
# Host is up (0.00049s latency).
###

# ssh -Y pi@172.20.10.2
# ssh -Y pi@172.20.10.4

# ping 172.20.10.2 -n 1

# ping dog01.local -n 1




# and
# ping nest01.local

# you must have mdns running on your computer..windows probably won't be able to see the by name and
# ping dog01.local will fail. When we get better network router, i can see it to always get the same ip address
# the user is pi@dog01.local and pi@nest01.local

# avahi-browse -at

# paddy@nobody:~$ ssh -Y pi@172.20.10.2
# paddy@nobody:~$ ssh -Y pi@172.20.10.4


