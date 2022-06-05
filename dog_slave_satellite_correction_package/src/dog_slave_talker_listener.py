#!/usr/bin/env python
# cd /home/pi/Desktop/ROS_startup_scripts/talker_listener_test/ && ./start_slave_talker_listener_test.sh

import time
import binascii
import serial
import sys
import select
import roslib; roslib.load_manifest('rospy_tutorials')

import rospy
from std_msgs.msg import String

end = "\n"
RED = "\x1b[1;31m"
BLUE="\e[44m"
F_LightGreen = "\x1b[92m"
F_Green = "\x1b[32m"
F_LightBlue = "\x1b[94m"
B_White = "\x1b[107m"
NC = "\x1b[0m" # No Color
Blink = "\x1b[5m"

b = b""
data_concat = ""
started = "false"
blank = "false"


def callback(data):
    global data_concat
    global started
    hex_data_array = []
    char_data_array = []
    blank = ""
    char_1 = ""
    char_2 = ""
    hex_num = 00
    i =0
    rospy.loginfo(rospy.get_caller_id()+" I heard:  %s",data.data)
    if data.data == "start":
        started = "true"
        data_concat = ""
        print("Start was detected")
    if data.data != "finish" and data.data != "start" and started == "true":
        # print(data.data)
        data_concat = data_concat + data.data
    if data.data == "finish":
        started = "false"
        print ("data_concat:  ", data_concat)
        
        for c in data_concat:
            if c == " ":
                blank = "true"
            if c != " ":
                blank = "false"
                i = i+1
            if blank == "false" and i == 1:
                char_1 = c
            if blank == "false" and i == 2:
                char_2 = c
                i =0
                int_num = int((char_1 + char_2),16)
                hex_num = hex(int((char_1 + char_2),16))
                hex_data_array.append(hex_num)
                char_data_array.append(chr(int_num))
                
                # print(" int_num: ", int_num)
                blank = "false"
                
        # print("hex_data_array: ", hex_data_array)
        print("char_data_array: ", char_data_array)
        print("length of char_data_array: ", len(char_data_array))

        char_concat_string = ""
        char_concat_string = "".join(str(e) for e in char_data_array)
        # i=0
        # for d in char_data_array:
            # print(d)
            # char_concat_string = char_concat_string + d
            # i = i+1
            
        # print("length of char_concat_string",i)
            
        print("char_concat_string: ", char_concat_string)

        # with serial.serial_for_url('spy:///dev/ttyUSB0?', timeout=2) as s:
        with serial.Serial('/dev/ttyUSB0', 38400, timeout=2) as s:

            '''Test modem control lines'''
            s.dtr = False
            s.rts = False
            s.write(char_concat_string)
        
        
        
        
                # ascii_char = chr(int_num)
                # char c = (char)65
                # char c = Convert. ToChar(65);
                # ascii_char = (char)int_num
                # bytes_num = bytes(int_num)
                # ascii_char = bytes_num.decode('cp437')
                # print(ascii_char)
                # character_data = binascii.unhexlify(hex_num)
                # print ("ascii_char:  ", ascii_char)
                # print(bytes.fromhex("72 65 61 6c 70 79 74 68 6f 6e"))

                # a = hex_num.decode("utf-8")
                # b = hex_num.decode("latin-1")
                # c = binascii.unhexlify(hex_num)
                # d = binascii.unhexlify("\x" + str(int_num))
                # print (" a:  ", a)
                # print (" b:  ", b)
                # print (" c:  ", c)
                # print (" d:  ", d)
                # e = binascii.hexify(b'\xb9\x0\xef' , '-')
                # print (" e:  ", e)

        # character_data = binascii.unhexlify(data_concat)
        # print ("character_data:  ", character_data)

def listener():

    # in ROS, nodes are unique named. If two nodes with the same
    # node are launched, the previous one is kicked off. The 
    # anonymous=True flag means that rospy will choose a unique
    # name for our 'talker' node so that multiple talkers can
    # run simultaenously.
    rospy.init_node('listener', anonymous=True)

    rospy.Subscriber("correction_data_msg2", String, callback)
    # rospy.Subscriber("correction_data_from_nest", String, callback)

    # spin() simply keeps python from exiting until this node is stopped
    rospy.spin()

def talker():
    str1 = ""
    # data = None
    pub = rospy.Publisher('correction_data_msg', String, queue_size=10)
    rospy.init_node('talker', anonymous=True)
    r = rospy.Rate(0.1) # 0.1hz
    # for line in sys.stdin:
        # sys.stdout.write(line)
    while not rospy.is_shutdown():
        print(" Hello from talker.py !! ")
        
        with serial.serial_for_url('spy:///dev/ttyUSB0?', timeout=2) as s:

            '''Test modem control lines'''
            s.dtr = False
            s.rts = False
            # s.ri = False
    
            # s.write('hello arsehole !!')
            # s.read(4000)
            # s.dtr = True
            # s.write(serial.to_bytes(range(256)))
            # s.write('This is where the data starts .... ')
            # binary_data = s.read(40000), b''
            character_data = s.read(40000)

            hex_data = binascii.hexlify(character_data)
            # hex_data = hex(character_data)
            binary_data = character_data, b''

            # sys.stderr.write("\x1b[94m" + "character_data: " + '\x1b[0m' + end)
            # print(character_data)
            
            # sys.stderr.write("\x1b[94m" + "hex_data: " + '\x1b[0m' + end)
            # print(hex_data)

            # sys.stderr.write("\x1b[94m" + "binary data: " + '\x1b[0m' + end)
            # print(binary_data)
            
            i=0
            hex_data_array = []
            for char in character_data:
                char = binascii.hexlify(char)
                hex_data_array.append(char)
                i = i+1
            # print("i = ",i)
            # sys.stderr.write("\x1b[94m" + "hex_data_array: " + '\x1b[0m' + end)
            # print(hex_data_array)
            
            str_full = ""
            # str1 = ''.join(hex_data_array)
            blacklist = set('\/')
            str_full = " ".join(str(e) for e in hex_data_array if e not in blacklist)
            # " ".join(str(x) for x in L)
            # makeitastring = ''.join(map(str, hex_data_array))
            sys.stderr.write("\x1b[94m" + "string data: " + '\x1b[0m' + end)
            print(str_full)
            print("The type of this data: ",type(str_full))
            print("The length of this data is: ",len(str_full))
            print("")
            # truncate the string:
            # max size seems to be 113 for some reason.
            str0 = "start"
            str1 = str_full[:45]
            str2 = str_full[45:90]
            str3 = str_full[90:135]
            str4 = str_full[135:180]
            str5 = str_full[225:270]
            str6 = str_full[270:315]
            str7 = str_full[315:360]
            str8 = str_full[360:405]
            str9 = str_full[405:450]
            str10 = str_full[495:540]
            str11 = str_full[540:585]
            str12 = str_full[585:630]
            str13 = str_full[675:720]
            str14 = str_full[720:765]
            str15 = str_full[765:810]
            str16 = str_full[810:855]
            str17 = str_full[855:900]
            str18 = str_full[945:990]
            str19 = str_full[990:1035]
            str20 = str_full[1035:1080]
            str21 = str_full[1080:1125]
            str22 = str_full[1125:1170]
            str_full_check = str1 + str2 + str3 + str4 + str5 + str6 + str7 + str8 + str9 + str10 + str11 + str12 + str13 + str14 + str15 + str16 + str17 + str18 + str19 + str20 + str21 + str22
            print("This is the data checked: ")
            print (str_full_check)
            str23 = "finish"
            
        # str1 = "Hello Arsehole!!"
        # testNum = 0xa1b2c3
        # hex(testNum)
        # test = hex(testNum)
        # isinstance(test, str)
        
        # str = hex(hex_data)
        # format(hex_data, 'hex_data')
        # str = hex_data
        # str = str(hex_data,'ascii')
        # outputString = inputString.encode('utf-8').hex()
        # str = character_data.encode('ascii').hex()
        # str = character_data
        # str = str(hex_data)
        # str = "hello Arsehole !! %s"%data
        
        sleep_value = 1

        rospy.loginfo(str0)
        pub.publish(str0)
        time.sleep(sleep_value)
        
        if str1 != "":
            pub.publish(str1)
            rospy.loginfo(str1)
            time.sleep(sleep_value)
        
        if str2 != "":
            pub.publish(str2)
            rospy.loginfo(str2)
            time.sleep(sleep_value)
        
        if str3 != "":
            pub.publish(str3)
            rospy.loginfo(str3)
            time.sleep(sleep_value)
        
        if str4 != "":
            pub.publish(str4)
            rospy.loginfo(str4)
            time.sleep(sleep_value)
        
        if str5 != "":
            pub.publish(str5)
            rospy.loginfo(str5)
            time.sleep(sleep_value)
        
        if str6 != "":
            pub.publish(str6)
            rospy.loginfo(str6)
            time.sleep(sleep_value)
        
        if str7 != "":
            pub.publish(str7)
            rospy.loginfo(str7)
            time.sleep(sleep_value)
        
        if str8 != "":
            pub.publish(str8)
            rospy.loginfo(str8)
            time.sleep(sleep_value)
        
        if str9 != "":
            pub.publish(str9)
            rospy.loginfo(str9)
            time.sleep(sleep_value)
        
        if str10 != "":
            pub.publish(str10)
            rospy.loginfo(str10)
            time.sleep(sleep_value)
        
        if str11 != "":
            pub.publish(str11)
            rospy.loginfo(str11)
            time.sleep(sleep_value)
        
        if str12 != "":
            pub.publish(str12)
            rospy.loginfo(str12)
            time.sleep(sleep_value)
        
        if str13 != "":
            pub.publish(str13)
            rospy.loginfo(str13)
            time.sleep(sleep_value)
        
        if str14 != "":
            pub.publish(str14)
            rospy.loginfo(str14)
            time.sleep(sleep_value)
        
        if str15 != "":
            pub.publish(str15)
            rospy.loginfo(str15)
            time.sleep(sleep_value)
        
        if str16 != "":
            pub.publish(str16)
            rospy.loginfo(str16)
            time.sleep(sleep_value)
        
        if str17 != "":
            pub.publish(str17)
            rospy.loginfo(str17)
            time.sleep(sleep_value)
        
        if str18 != "":
            pub.publish(str18)
            rospy.loginfo(str18)
            time.sleep(sleep_value)
        
        if str19 != "":
            pub.publish(str19)
            rospy.loginfo(str19)
            time.sleep(sleep_value)
        
        if str20 != "":
            pub.publish(str20)
            rospy.loginfo(str20)
            time.sleep(sleep_value)
        
        if str21 != "":
            pub.publish(str21)
            rospy.loginfo(str21)
            time.sleep(sleep_value)
        
        if str22 != "":
            pub.publish(str22)
            rospy.loginfo(str22)
            time.sleep(sleep_value)
        
        pub.publish(str23)
        rospy.loginfo(str23)
        time.sleep(sleep_value)

        # r.sleep()

        
if __name__ == '__main__':
    try:
        listener()
    except rospy.ROSInterruptException: pass
