#!/bin/bash

source /home/pi/ros_catkin_ws/devel/setup.bash && rostopic pub toggle_led std_msgs/Empty --once
rostopic pub toggle_led std_msgs/Empty --once
rostopic pub toggle_led std_msgs/Empty --once
rostopic pub toggle_led std_msgs/Empty --once
rostopic pub toggle_led std_msgs/Empty --once
rostopic pub toggle_led std_msgs/Empty --once
rostopic pub toggle_led std_msgs/Empty --once
rostopic pub toggle_led std_msgs/Empty --once
rostopic pub toggle_led std_msgs/Empty --once
rostopic pub toggle_led std_msgs/Empty --once

# source /home/pi/ros_catkin_ws/devel/setup.bash && rostopic pub chatter std_msgs/String --once
