#include <SPI.h>
#include <LoRa.h>
#include <ros.h>
#include <std_msgs/Empty.h>
#include <std_msgs/Char.h>
#include <std_msgs/String.h>

std_msgs::String chatter;
std_msgs::String correction_data_msg2;
std_msgs::String cycle_time_msg;
ros::Publisher chatter1("nest_cycle_time", &cycle_time_msg);

ros::NodeHandle  nh;

const long frequency = 433.5E6;  // LoRa Frequency
int spreading = 7;             // spreading factor ranges from 6-12,default 7 see API docs
const int csPin = 4;          // LoRa radio chip select
const int resetPin = 2;        // LoRa radio reset
const int irqPin = 3;          // change for your board; must be a hardware interrupt pin

int ledState_03 = LOW;
unsigned long prevMillis_03 = 0;
const long interval_03 = 1400;
String correction_data = "";

String outgoing;              // outgoing message
byte msgCount = 0;            // count of outgoing messages
byte localAddress = 0xBB;     // address of this device
byte destination = 0xFF;      // destination to send to
long lastSendTime = 0;        // last send time
int interval = 2000;          // interval between sends

char cycle_time[10];
String outgoing_from_nest = "";
int digit = 0;
int result = 0;
char char_result;
char first;
char second;
char c;

void messageCb1( const std_msgs::Empty& toggle_msg)
{
  digitalWrite(7, HIGH-digitalRead(7));   // toggle the led
}
void messageCb2( const std_msgs::String chatter)
{
  digitalWrite(6, HIGH-digitalRead(6));   // toggle the led
  correction_data = chatter.data;
}
void messageCb3( const std_msgs::String correction_data_msg2)
{
  unsigned long currentMicros1 = micros();
  digitalWrite(6, HIGH-digitalRead(6));   // toggle the led
  correction_data = correction_data_msg2.data; // String

  if ((correction_data == "start") || (correction_data == "finish"))
  {
    digitalWrite(7, HIGH-digitalRead(7));   // toggle the led
  }

/////////////////////////////////////////////////////////
  first = correction_data[0];
  int result1 = my_funct(first);
  second = correction_data[1];
  int result2 = my_funct(second);
  int result3 = result1*16 + result2;
  // Serial.print("result3: ");  Serial.print(result3);
  char_result = char(result3);
  // Serial.print(" char result3: ");  Serial.print(char_result);
  // byte int_result = (byte)char_result;
  // Serial.print(" char result3 printed as int: ");Serial.println(int_result);
  outgoing_from_nest = char(result3);
  
  for(int i =0; i < 57; i++ ) 
  {
    if (correction_data[i] == ' ')
    {
      first = correction_data[i+1];
      second = correction_data[i+2];
      result1 = my_funct(first);
      result2 = my_funct(second);
      result3 = result1*16 + result2;
      char_result = char(result3);
      outgoing_from_nest = outgoing_from_nest + char_result;
      // Serial.print("result3: ");  Serial.print(result3);
      // Serial.print(" char result3: ");  Serial.print(char(result3));
      // byte int_result = (byte)char_result;
      // Serial.print(" char result3 printed as int: ");  Serial.println(int_result);
    }
  }
  Serial.print("outgoing_from_nest: ");Serial.println(outgoing_from_nest);
  correction_data = outgoing_from_nest;
/////////////////////////////////////////////////////////

  


  // wait until the radio is ready to send a packet
  while (LoRa.beginPacket() == 0) 
  {
    Serial.print("waiting for radio ... ");
  }

  Serial.print("Sending packet: ");

  // Outgoing data seems to be 46 characters max at a time:
  // String outgoing = "46_characters_++++++++++++++++++++++++++++++++";

  digitalWrite(8, HIGH);
  LoRa.beginPacket();
  LoRa.write(destination);              // add destination address
  LoRa.write(localAddress);             // add sender address
  LoRa.write(msgCount);                 // add message ID
  LoRa.write(correction_data.length());        // add payload length
  LoRa.print(correction_data);
  // LoRa.endPacket(true); // true = async / non-blocking mode
  LoRa.endPacket(); // true = async / non-blocking mode
  
  digitalWrite(8, LOW);
  msgCount++;
  if (correction_data == "finish")
  {
    msgCount = 0;
  }
  unsigned long currentMicros2 = micros();
  String(currentMicros2 - currentMicros1).toCharArray(cycle_time,10);
  // myString.toCharArray(buf, len)
  cycle_time_msg.data = cycle_time;
  chatter1.publish( &cycle_time_msg );
}

// ros::Subscriber<std_msgs::Empty> sub1("toggle_led", &messageCb1 );
// ros::Subscriber<std_msgs::String> sub2("chatter", &messageCb2 );
ros::Subscriber<std_msgs::String> sub3("correction_data_msg2", &messageCb3 );

void setup()
{ 
  correction_data.reserve(512);
  
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  digitalWrite(5,HIGH);
  digitalWrite(6,HIGH);
  digitalWrite(7,HIGH);
  digitalWrite(8,HIGH);
  delay(500);
  digitalWrite(5,LOW);
  digitalWrite(6,LOW);
  digitalWrite(7,LOW);
  digitalWrite(8,LOW);
  nh.initNode();
  nh.advertise(chatter1);
  // nh.subscribe(sub1);
  // nh.subscribe(sub2);
  nh.subscribe(sub3);

  Serial.println("LoRa Sender non-blocking");
    // override the default CS, reset, and IRQ pins (optional)
  LoRa.setPins(csPin, resetPin, irqPin);// set CS, reset, IRQ pin

  if (!LoRa.begin(frequency)) 
  {
    Serial.println("Starting LoRa failed!");
    while (1);
  }
  // LoRa.setSpreadingFactor(12);           // ranges from 6-12,default 7 see API docs
  LoRa.setSpreadingFactor(spreading);           // ranges from 6-12,default 7 see API docs
  Serial.println("LoRa init succeeded.");
  // LoRa.setGain(6);   // Ranges from 0 to 6 where 6 is max.
  // LoRa.writeRegister(0x0C,0x23);  // This should be max LNA gain.
  
  Serial.println("LoRa init succeeded.");
  Serial.println("LoRa.setSignalBandwidth: ");
  LoRa.setSignalBandwidth(500000);
  Serial.print("LoRa.getSignalBandwidth: ");Serial.println(LoRa.getSignalBandwidth());
  Serial.print("LoRa.getSpreadingFactor: ");Serial.println(LoRa.getSpreadingFactor());
  Serial.print("LoRa.readRegister RegModemConfig1(0x1d): ");Serial.print("B");Serial.println(LoRa.readRegister(0x1d),BIN);
  Serial.print("LoRa.readRegister RegPaDac(high power)(0x4d): "); Serial.print("0x");Serial.println(LoRa.readRegister(0x4d),HEX);
  Serial.print("LoRa.readRegister RegLna(0x0C): ");Serial.print("B");Serial.println(LoRa.readRegister(0x0C),BIN);
  byte b = B00100011; // = "00100011";
  Serial.print("Convert b to hex value: ");Serial.print("0x");Serial.println (b, HEX); // comes to 0x23.
  
}

void loop()
{  
  blinkLED_5();
  nh.spinOnce();
  delay(5);
}

void blinkLED_5() 
{
  unsigned long currentMillis = millis();
  if (currentMillis - prevMillis_03 >= interval_03) 
  {
    prevMillis_03 = currentMillis;
    if (ledState_03 == LOW) 
    {
      ledState_03 = HIGH;
    } else {
      ledState_03 = LOW;
    }
    digitalWrite(5, ledState_03);
  }
}

int my_funct(char c)
{
  if (c == '0'){digit = 0;}
  if (c == '1'){digit = 1;}
  if (c == '2'){digit = 2;}
  if (c == '3'){digit = 3;}
  if (c == '4'){digit = 4;}
  if (c == '5'){digit = 5;}
  if (c == '6'){digit = 6;}
  if (c == '7'){digit = 7;}
  if (c == '8'){digit = 8;}
  if (c == '9'){digit = 9;}
  if (c == 'a'){digit = 10;}
  if (c == 'b'){digit = 11;}
  if (c == 'c'){digit = 12;}
  if (c == 'd'){digit = 13;}
  if (c == 'e'){digit = 14;}
  if (c == 'f'){digit = 15;}
  return digit;
}
