#include <SPI.h>
#include <LoRa.h>
#include <ros.h>
#include <std_msgs/Empty.h>
#include <std_msgs/Char.h>
#include <std_msgs/String.h>

std_msgs::String chatter;
std_msgs::String correction_data_msg2;

ros::NodeHandle  nh;

const long frequency = 433.5E6;  // LoRa Frequency
int spreading = 10;             // spreading factor
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
  digitalWrite(6, HIGH-digitalRead(6));   // toggle the led
  correction_data = correction_data_msg2.data;
  if ((correction_data == "start") || (correction_data == "finish"))
  {
    digitalWrite(7, HIGH-digitalRead(7));   // toggle the led
  }

  // wait until the radio is ready to send a packet
  while (LoRa.beginPacket() == 0) 
  {
    Serial.print("waiting for radio ... ");
    digitalWrite(8, HIGH);
    delay(5);
    digitalWrite(8, LOW);
    delay(5);
  }

  Serial.print("Sending packet non-blocking: ");
  // Serial.println(counter);
  // send in async / non-blocking mode
  // Outgoing data seems to be 46 characters max at a time:
  // String outgoing = "46_characters_++++++++++++++++++++++++++++++++";
  // String outgoing = "The rabid black dog sniffed it's arse and farted and pissed on a lamp post at the front desk.";
  // String outgoing = "The dog sniffed it's arse and pissed on a lamp post at the front desk. \nOn the side is the back wall where a piece of metal shank was hanging from which is a large wooden table. \nThe dog took a sip of a soda and started to bark.\nEverybody died of hunger.\n";
  digitalWrite(8, HIGH);
  LoRa.beginPacket();
  LoRa.write(destination);              // add destination address
  LoRa.write(localAddress);             // add sender address
  LoRa.write(msgCount);                 // add message ID
  LoRa.write(correction_data.length());        // add payload length
  LoRa.print(correction_data);
  // LoRa.print(counter);
  LoRa.endPacket(true); // true = async / non-blocking mode
  digitalWrite(8, LOW);
  msgCount++;
  if (correction_data == "finish")
  {
    msgCount = 0;
  }
  // counter++;
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
  
}

void loop()
{  
  blinkLED_5();
  nh.spinOnce();
  delay(1);
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
