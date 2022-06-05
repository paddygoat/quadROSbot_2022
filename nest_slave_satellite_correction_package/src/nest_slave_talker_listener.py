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

def talker():
    str1 = ""
    # data = None
    pub = rospy.Publisher('correction_data_msg', String, queue_size=10)
    rospy.init_node('talker', anonymous=True)
    # r = rospy.Rate(0.1) # 0.1hz
    # for line in sys.stdin:
        # sys.stdout.write(line)
    while not rospy.is_shutdown():
        print(" Hello from talker.py !! ")
        
        # with serial.serial_for_url('spy:///dev/ttyUSB0?', timeout=2) as s:
        with serial.Serial('/dev/ttyUSB0',38400, timeout=3) as s:

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
            print("start of table ... ")
            character_data = s.read(40000)
            print(" ..... end of table")

            hex_data = binascii.hexlify(character_data)
            # hex_data = hex(character_data)
            binary_data = character_data, b''

            # sys.stderr.write("\x1b[94m" + "character_data: " + '\x1b[0m' + end)
            # print(character_data)
            
            sys.stderr.write("\x1b[94m" + "hex_data: " + '\x1b[0m' + end)
            print(hex_data)
            print("length of hex_data = ",len(hex_data))

            # sys.stderr.write("\x1b[94m" + "binary data: " + '\x1b[0m' + end)
            # print(binary_data)
            
            i=0
            hex_data_array = []
            for char in character_data:
                char = binascii.hexlify(char)
                hex_data_array.append(char)
                i = i+1
            print("length of hex_data_array = ",i)
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
            print("The type of str_full: ",type(str_full))
            print("The length of this str_full is: ",len(str_full))
            print("")
            # truncate the string:
            # max size seems to be 113 for some reason.
            str0 = "start"
            str1 = str_full[:45]
            str2 = str_full[45:90]
            str3 = str_full[90:135]
            str4 = str_full[135:180]
            str4b = str_full[180:225]           
            str5 = str_full[225:270]
            str6 = str_full[270:315]
            str7 = str_full[315:360]
            str8 = str_full[360:405]
            str9 = str_full[405:450]
            str9b = str_full[450:495]
            str10 = str_full[495:540]
            str11 = str_full[540:585]
            str12 = str_full[585:630]
            str12b = str_full[630:675]
            str13 = str_full[675:720]
            str14 = str_full[720:765]
            str15 = str_full[765:810]
            str16 = str_full[810:855]
            str17 = str_full[855:900]
            str17b = str_full[900:945]
            str18 = str_full[945:990]
            str19 = str_full[990:1035]

            str20 = str_full[1035:1080]
            str21 = str_full[1080:1125]
            str22 = str_full[1125:1170]
            
            str23 = str_full[1170:1215]
            str24 = str_full[1215:1260]
            str25 = str_full[1260:1305]
            str26 = str_full[1305:1350]
            str27 = str_full[1350:1395]
            str28 = str_full[1395:1440]
            str29 = str_full[1440:1485]
            
            str30 = str_full[1485:1530]
            str31 = str_full[1530:1575]
            str32 = str_full[1575:1620]
            str33 = str_full[1620:1665]
            str34 = str_full[1665:1710]
            str35 = str_full[1710:1755]
            str36 = str_full[1755:1800]
            str37 = str_full[1800:1845]
            str38 = str_full[1845:1890]
            str39 = str_full[1890:1935]

            str40 = str_full[1935:1980]
            str41 = str_full[1980:2025]
            str42 = str_full[2025:2070]
            str43 = str_full[2070:2115]
            str44 = str_full[2115:2160]
            str45 = str_full[2160:2205]
            str46 = str_full[2205:2250]
            str47 = str_full[2250:2295]
            str48 = str_full[2295:2340]
            str49 = str_full[2340:2385]
            
            str50 = str_full[2385:2430]
            str51 = str_full[2430:2475]
            str52 = str_full[2475:2520]
            str53 = str_full[2520:2565]
            str54 = str_full[2565:2610]
            str55 = str_full[2610:2655]
            str56 = str_full[2655:2700]
            str57 = str_full[2700:2745]
            str58 = str_full[2745:2790]
            str59 = str_full[2790:2835]

            str60 = str_full[2835:2880]
            str61 = str_full[2880:2925]
            str62 = str_full[2925:2970]
            str63 = str_full[2970:3015]
            str64 = str_full[3015:3060]
            str65 = str_full[3060:3105]
            str66 = str_full[3105:3150]
            str67 = str_full[3150:3195]
            str68 = str_full[3195:3240]
            str69 = str_full[3240:3285]
    
            str70 = str_full[3285:3330]
            str71 = str_full[3330:3375]
            str72 = str_full[3375:3420]
            str73 = str_full[3420:3465]
            str74 = str_full[3465:3510]
            str75 = str_full[3510:3555]
            str76 = str_full[3555:3600]
            str77 = str_full[3600:3645]
            str78 = str_full[3645:3690]
            str79 = str_full[3690:3735]
            str80 = str_full[3735:3780]
            str81 = str_full[3780:3825]
            str82 = str_full[3825:3870]
            str83 = str_full[3870:3915]
            str84 = str_full[3915:3960]
            str85 = str_full[3960:4005]
            
            
            
            
            
            
            str_full_check = str1 + str2 + str3 + str4 + str4b + str5 + str6 + str7 + str8 + str9 + str9b + str10 + str11 + str12 + str12b + str13 + str14 + str15 + str16 + str17 + str17b + str18 + str19 + str20 + str21 + str22 + str23 + str24 + str25 + str26 + str27 + str28 + str29 + str30 + str31 + str32 + str33 + str34 + str35 + str36 + str37 + str38 + str39 + str40 + str41 + str42 + str43 + str44 + str45 + str46 + str47 + str48 + str49 + str50 + str51 + str52 + str53 + str54 + str55 + str56 + str57 + str58 + str59 + str60 + str61 + str62 + str63 + str64 + str65 + str66 + str67 + str68 + str69 + str70 + str71 + str72 + str73 + str74 + str75 + str76 + str77 + str78 + str79 + str80 + str81 + str82 + str83 + str84 + str85
            print("This is the data checked: ")
            print (str_full_check)
            print("The type of str_full_check: ",type(str_full_check))
            print("The length of this str_full_check is: ",len(str_full_check))
            print("")
            str86 = "finish"
            
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
        
        sleep_value = 0.05  # Tried 1.5 but with errors. 2.0 gave about 2% error. 2.5 gave about 1% error.

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

        if str4b != "":
            pub.publish(str4b)
            rospy.loginfo(str4b)
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
        
        if str9b != "":
            pub.publish(str9b)
            rospy.loginfo(str9b)
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
        
        if str12b != "":
            pub.publish(str12b)
            rospy.loginfo(str12b)
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
            
        if str17b != "":
            pub.publish(str17b)
            rospy.loginfo(str17b)
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
        
        if str23 != "":
            pub.publish(str23)
            rospy.loginfo(str23)
            time.sleep(sleep_value)
        
        if str24 != "":
            pub.publish(str24)
            rospy.loginfo(str24)
            time.sleep(sleep_value)
        
        if str25 != "":
            pub.publish(str25)
            rospy.loginfo(str25)
            time.sleep(sleep_value)
        
        if str26 != "":
            pub.publish(str26)
            rospy.loginfo(str26)
            time.sleep(sleep_value)
        
        if str27 != "":
            pub.publish(str27)
            rospy.loginfo(str27)
            time.sleep(sleep_value)
        
        if str28 != "":
            pub.publish(str28)
            rospy.loginfo(str28)
            time.sleep(sleep_value)
        
        if str29 != "":
            pub.publish(str29)
            rospy.loginfo(str29)
            time.sleep(sleep_value)
        
        if str30 != "":
            pub.publish(str30)
            rospy.loginfo(str30)
            time.sleep(sleep_value)
        
        if str31 != "":
            pub.publish(str31)
            rospy.loginfo(str31)
            time.sleep(sleep_value)
        
        if str32 != "":
            pub.publish(str32)
            rospy.loginfo(str32)
            time.sleep(sleep_value)
        
        if str33 != "":
            pub.publish(str33)
            rospy.loginfo(str33)
            time.sleep(sleep_value)
        
        if str34 != "":
            pub.publish(str34)
            rospy.loginfo(str34)
            time.sleep(sleep_value)
        
        if str35 != "":
            pub.publish(str35)
            rospy.loginfo(str35)
            time.sleep(sleep_value)
        
        if str36 != "":
            pub.publish(str36)
            rospy.loginfo(str36)
            time.sleep(sleep_value)
        
        if str37 != "":
            pub.publish(str37)
            rospy.loginfo(str37)
            time.sleep(sleep_value)
        
        if str38 != "":
            pub.publish(str38)
            rospy.loginfo(str38)
            time.sleep(sleep_value)
        
        if str39 != "":
            pub.publish(str39)
            rospy.loginfo(str39)
            time.sleep(sleep_value)
            
        if str40 != "":
            pub.publish(str40)
            rospy.loginfo(str40)
            time.sleep(sleep_value)
            
        if str41 != "":
            pub.publish(str41)
            rospy.loginfo(str41)
            time.sleep(sleep_value)
            
        if str42 != "":
            pub.publish(str42)
            rospy.loginfo(str42)
            time.sleep(sleep_value)
            
        if str43 != "":
            pub.publish(str43)
            rospy.loginfo(str43)
            time.sleep(sleep_value)
            
        if str44 != "":
            pub.publish(str44)
            rospy.loginfo(str44)
            time.sleep(sleep_value)
            
        if str45 != "":
            pub.publish(str45)
            rospy.loginfo(str45)
            time.sleep(sleep_value)
            
        if str46 != "":
            pub.publish(str46)
            rospy.loginfo(str46)
            time.sleep(sleep_value)
            
        if str47 != "":
            pub.publish(str47)
            rospy.loginfo(str47)
            time.sleep(sleep_value)
            
        if str48 != "":
            pub.publish(str48)
            rospy.loginfo(str48)
            time.sleep(sleep_value)
            
        if str49 != "":
            pub.publish(str49)
            rospy.loginfo(str49)
            time.sleep(sleep_value)
            
        if str50 != "":
            pub.publish(str50)
            rospy.loginfo(str50)
            time.sleep(sleep_value)
            
        if str51 != "":
            pub.publish(str51)
            rospy.loginfo(str51)
            time.sleep(sleep_value)
                      
        if str52 != "":
            pub.publish(str52)
            rospy.loginfo(str52)
            time.sleep(sleep_value)
                      
        if str53 != "":
            pub.publish(str53)
            rospy.loginfo(str53)
            time.sleep(sleep_value)

        if str54 != "":
            pub.publish(str54)
            rospy.loginfo(str54)
            time.sleep(sleep_value)
        
        if str55 != "":
            pub.publish(str55)
            rospy.loginfo(str55)
            time.sleep(sleep_value)
        
        if str56 != "":
            pub.publish(str56)
            rospy.loginfo(str56)
            time.sleep(sleep_value)
        
        if str57 != "":
            pub.publish(str57)
            rospy.loginfo(str57)
            time.sleep(sleep_value)
        
        if str58 != "":
            pub.publish(str58)
            rospy.loginfo(str58)
            time.sleep(sleep_value)
        
        if str59 != "":
            pub.publish(str59)
            rospy.loginfo(str59)
            time.sleep(sleep_value)

        if str60 != "":
            pub.publish(str60)
            rospy.loginfo(str60)
            time.sleep(sleep_value)

        if str61 != "":
            pub.publish(str61)
            rospy.loginfo(str61)
            time.sleep(sleep_value)
        
        if str62 != "":
            pub.publish(str62)
            rospy.loginfo(str62)
            time.sleep(sleep_value)
        
        if str63 != "":
            pub.publish(str63)
            rospy.loginfo(str63)
            time.sleep(sleep_value)
        
        if str64 != "":
            pub.publish(str64)
            rospy.loginfo(str64)
            time.sleep(sleep_value)
        
        if str65 != "":
            pub.publish(str65)
            rospy.loginfo(str65)
            time.sleep(sleep_value)
        
        if str66 != "":
            pub.publish(str66)
            rospy.loginfo(str66)
            time.sleep(sleep_value)
        
        if str67 != "":
            pub.publish(str67)
            rospy.loginfo(str67)
            time.sleep(sleep_value)
        
        if str68 != "":
            pub.publish(str68)
            rospy.loginfo(str68)
            time.sleep(sleep_value)
        
        if str69 != "":
            pub.publish(str69)
            rospy.loginfo(str69)
            time.sleep(sleep_value)
        
        if str70 != "":
            pub.publish(str70)
            rospy.loginfo(str70)
            time.sleep(sleep_value)
        
        if str71 != "":
            pub.publish(str71)
            rospy.loginfo(str71)
            time.sleep(sleep_value)
        
        if str72 != "":
            pub.publish(str72)
            rospy.loginfo(str72)
            time.sleep(sleep_value)
             
        if str73 != "":
            pub.publish(str73)
            rospy.loginfo(str73)
            time.sleep(sleep_value)
             
        if str74 != "":
            pub.publish(str74)
            rospy.loginfo(str74)
            time.sleep(sleep_value)
             
        if str75 != "":
            pub.publish(str75)
            rospy.loginfo(str75)
            time.sleep(sleep_value)
             
        if str76 != "":
            pub.publish(str76)
            rospy.loginfo(str76)
            time.sleep(sleep_value)
             
        if str77 != "":
            pub.publish(str77)
            rospy.loginfo(str77)
            time.sleep(sleep_value)
             
        if str78 != "":
            pub.publish(str78)
            rospy.loginfo(str78)
            time.sleep(sleep_value)
             
        if str79 != "":
            pub.publish(str79)
            rospy.loginfo(str79)
            time.sleep(sleep_value)
             
        if str80 != "":
            pub.publish(str80)
            rospy.loginfo(str80)
            time.sleep(sleep_value)
             
        if str81 != "":
            pub.publish(str81)
            rospy.loginfo(str81)
            time.sleep(sleep_value)
             
        if str82 != "":
            pub.publish(str82)
            rospy.loginfo(str82)
            time.sleep(sleep_value)
             
        if str83 != "":
            pub.publish(str83)
            rospy.loginfo(str83)
            time.sleep(sleep_value)
             
        if str84 != "":
            pub.publish(str84)
            rospy.loginfo(str84)
            time.sleep(sleep_value)
             
        if str85 != "":
            pub.publish(str85)
            rospy.loginfo(str85)
            time.sleep(sleep_value)

        pub.publish(str86)
        rospy.loginfo(str86)
        time.sleep(sleep_value)

        # r.sleep()

        
if __name__ == '__main__':
    try:
        talker()
    except rospy.ROSInterruptException: pass
