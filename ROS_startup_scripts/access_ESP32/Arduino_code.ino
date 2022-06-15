
//////////////////////
// WiFi Definitions //
//////////////////////
const char* ssid = "GOATNET_2.4G";
const char* password = "f5HLx42R";

// const char* ssid = "RUT_FA26_5G";
// const char* password = "Nk20WeTn";



#include "WiFi.h"
#include <ros.h>
#include <std_msgs/String.h>
#include <std_msgs/Int16.h>
#include <std_msgs/Float64.h>
#include <rosserial_arduino/Adc.h>


// IPAddress server(172, 20, 10, 3); // ip of your ROS server
IPAddress server(192,168,1,134); // ip of your ROS server(masternest)
// IPAddress server(10,244,128,65); // ip of your ROS server(masternest)

IPAddress ip_address;
int status = WL_IDLE_STATUS;
WiFiClient client;
class WiFiHardware {
public:
WiFiHardware() {};
void init() {
// do your initialization here. this probably includes TCP server/client setup
client.connect(server, 11411);
}
// read a byte from the serial port. -1 = failure
int read() {
// implement this method so that it reads a byte from the TCP connection and returns it
// you may return -1 is there is an error; for example if the TCP connection is not open
return client.read(); //will return -1 when it will works
}
// write data to the connection to ROS
void write(uint8_t* data, int length) {
// implement this so that it takes the arguments and writes or prints them to the TCP connection
for(int i=0; i<length; i++)
client.write(data[i]);
}
// returns milliseconds since start of program
unsigned long time() {
return millis(); // easy; did this one for you
}
};
int i;
void chatterCallback(const std_msgs::String& msg) {
i = atoi(msg.data);
}
std_msgs::String str_msg;
rosserial_arduino::Adc adc_msg;
ros::Publisher chatter("chatter", &str_msg);
ros::Publisher p("adc", &adc_msg);
ros::Subscriber<std_msgs::String> sub("message", &chatterCallback);
ros::NodeHandle_<WiFiHardware> nh;
char hello[20] = "ESP32 wifi alive!";
void setupWiFi()
{
WiFi.begin(ssid, password);
Serial.print("\nConnecting to "); Serial.println(ssid);
uint8_t i = 0;
while (WiFi.status() != WL_CONNECTED && i++ < 20) delay(500);
if(i == 21){
Serial.print("Could not connect to"); Serial.println(ssid);
while(1) delay(500);
}
Serial.print("Ready! Use ");
Serial.print(WiFi.localIP());
Serial.println(" to access client");
}
int averageAnalog(int pin){
int v=0;
for(int i=0; i<4; i++) v+= analogRead(pin);
return v/4;
}
void setup() {
Serial.begin(115200);
setupWiFi();
delay(2000);
nh.initNode();
nh.advertise(chatter);
nh.subscribe(sub);
nh.advertise(p);
}
void loop() {
str_msg.data = hello;
chatter.publish( &str_msg );
adc_msg.adc0 = averageAnalog(0);
p.publish(&adc_msg);
nh.spinOnce();
delay(500);
}
