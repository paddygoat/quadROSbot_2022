#!/usr/bin/env python

import sys
import select
import roslib; roslib.load_manifest('rospy_tutorials')

import rospy
from std_msgs.msg import String

def talker():

    # data = None
    pub = rospy.Publisher('chatter', String, queue_size=10)
    rospy.init_node('talker', anonymous=True)
    r = rospy.Rate(0.2) # 10hz
    # for line in sys.stdin:
        # sys.stdout.write(line)
    while not rospy.is_shutdown():
        print(" Hello from talker.py !! ")
        # data = None
        # select(files to read from, files to write to, magic, timeout)
        # timeout=0.0 is essential b/c we want to know the asnwer right away
        i = 0
        data = []
        if select.select([sys.stdin], [], [], 0.0)[0]:
            # data = sys.stdin.read()
            # print ("What is the type of data?")
            # type(data)
            # lines = sys.stdin.readlines()
            for line in sys.stdin:
                i = i+1
                print ("This is a new line: ")
                print (i)
                sys.stdout.write(line)
            data = sys.stdin.read()
            # data = sys.stdin.readlines()
            datajoined = ''.join(data)
            type(datajoined)
            mybytes = bytes.encode(datajoined)
            # data2 = str(data)
            print ("This is the list type data:")
            print (data)
            print ("This is the data datajoined:")
            print (datajoined)
            print ("This is the data mybytes:")
            print (mybytes)

        else:
            print("No data passed to stdin")
            # sys.exit(2)


        # try:
            # line = sys.stdin.readline()
        # except KeyboardInterrupt:
            # break
        # if not line:
            # break
        # print line

        # for line in sys.stdin:
            # sys.stdout.write(line)
        # str = "hello Arsehole !! %s"%rospy.get_time()
        str = datajoined
        # str = "hello Arsehole !! %s"%data
        rospy.loginfo(str)
        pub.publish(str)
        r.sleep()

        

        
if __name__ == '__main__':
    try:
        talker()
    except rospy.ROSInterruptException: pass
