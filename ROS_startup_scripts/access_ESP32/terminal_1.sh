#!/bin/bash

RED='\033[0;31m'
BLUE='\033[0;34m'
GREEN='\033[0;32m'
NC='\033[0m' # No Color

printf "${GREEN}Roscore.${NC}\n" 
echo ""

printf "${GREEN}"

source /opt/ros/melodic/setup.bash && roscore





