#include <SPI.h>
#include <LoRa.h>
#include <ros.h>
#include <std_msgs/Empty.h>
#include <std_msgs/Char.h>
#include <std_msgs/String.h>

std_msgs::String chatter;
std_msgs::String correction_data_msg_B2;
std_msgs::String cycle_time_msg;
ros::Publisher chatter1("nest_cycle_time", &cycle_time_msg);

ros::NodeHandle  nh;

const long frequency = 433.5E6;  // LoRa Frequency
int spreading = 7;             // spreading factor ranges from 6-12,default 7 see API docs
const int csPin = 39;          // LoRa radio chip select
const int resetPin = 18;        // LoRa radio reset
const int irqPin = 20;          // change for your board; must be a hardware interrupt pin

unsigned long prevMillis_MCU_ID;
const long interval_MCU_ID = 10000;

int ledState_pink = LOW;
int pink_pin = A1;
unsigned long prevMillis_pink = 0;
const long interval_pink = 300;

int ledState_blue = LOW;
int blue_pin = A0;
unsigned long prevMillis_blue = 0;
const long interval_blue = 400;

int ledState_green = LOW;
int green_pin = 4;
unsigned long prevMillis_green = 0;
const long interval_green = 500;

int ledState_yellow = LOW;
int yellow_pin = 13;
unsigned long prevMillis_yellow = 0;
const long interval_yellow = 600;

int ledState_orange = LOW;
int orange_pin = 2;
unsigned long prevMillis_orange = 0;
const long interval_orange = 700;

int ledState_red = LOW;
int red_pin = A3;
unsigned long prevMillis_red = 0;
const long interval_red = 800;

String correction_data = "";

String outgoing;              // outgoing message
byte msgCount = 0;            // count of outgoing messages
byte localAddress = 0xBB;     // address of this device
byte destination = 0xFF;      // destination to send to
long lastSendTime = 0;        // last send time
int interval = 2000;          // interval between sends

char cycle_time[10];


void messageCb1( const std_msgs::Empty& toggle_msg)
{
  digitalWrite(orange_pin, HIGH-digitalRead(orange_pin));   // toggle the led
}
void messageCb2( const std_msgs::String chatter)
{
  digitalWrite(orange_pin, HIGH-digitalRead(orange_pin));   // toggle the led
  correction_data = chatter.data;
}
void messageCb3( const std_msgs::String correction_data_msg_B2)
{
  unsigned long currentMicros1 = micros();
  // digitalWrite(orange_pin, HIGH-digitalRead(orange_pin));   // toggle the led
  correction_data = correction_data_msg_B2.data; // String
  if ((correction_data == "start") || (correction_data == "finish"))
  {
    // digitalWrite(pink_pin, HIGH-digitalRead(pink_pin));   // toggle the led
  }

  // wait until the radio is ready to send a packet
  while (LoRa.beginPacket() == 0) 
  {
    Serial.print("waiting for radio ... ");
  }

  Serial.print("Sending packet: ");

  // Outgoing data seems to be 46 characters max at a time:
  // String outgoing = "46_characters_++++++++++++++++++++++++++++++++";

  digitalWrite(blue_pin, HIGH);
  LoRa.beginPacket();
  LoRa.write(destination);              // add destination address
  LoRa.write(localAddress);             // add sender address
  LoRa.write(msgCount);                 // add message ID
  LoRa.write(correction_data.length());        // add payload length
  LoRa.print(correction_data);
  // LoRa.endPacket(true); // true = async / non-blocking mode
  LoRa.endPacket(); // true = async / non-blocking mode
  
  digitalWrite(blue_pin, LOW);
  msgCount++;
  // if (correction_data == "finish")
  // {
  //   msgCount = 0;
  // }
  unsigned long currentMicros2 = micros();
  String(currentMicros2 - currentMicros1).toCharArray(cycle_time,10);
  // myString.toCharArray(buf, len)
  cycle_time_msg.data = cycle_time;
  chatter1.publish( &cycle_time_msg );
}

// ros::Subscriber<std_msgs::Empty> sub1("toggle_led", &messageCb1 );
// ros::Subscriber<std_msgs::String> sub2("chatter", &messageCb2 );
ros::Subscriber<std_msgs::String> sub3("correction_data_msg_B2", &messageCb3 );

void setup()
{ 
  // Serial.begin(57600);
  // while (!Serial);
  correction_data.reserve(512);

  pinMode(pink_pin, OUTPUT);
  pinMode(blue_pin, OUTPUT);
  pinMode(green_pin, OUTPUT);
  pinMode(yellow_pin, OUTPUT);
  pinMode(orange_pin, OUTPUT);
  pinMode(red_pin, OUTPUT);

  digitalWrite(pink_pin,LOW);
  digitalWrite(blue_pin,LOW);
  digitalWrite(green_pin,LOW);
  digitalWrite(yellow_pin,LOW);
  digitalWrite(orange_pin,LOW);
  digitalWrite(red_pin,LOW);
  delay(5000);

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
    blinkRedLED();
    while (1);
  }
  // LoRa.setSpreadingFactor(12);           // ranges from 6-12,default 7 see API docs
  LoRa.setSpreadingFactor(spreading);           // ranges from 6-12,default 7 see API docs
  LoRa.setSyncWord(0x34);
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
  MCU_ID();
  blinkGreenLED();
  nh.spinOnce();
  delay(5);
}

void blinkOrangeLED() 
{
  unsigned long currentMillis = millis();
  if (currentMillis - prevMillis_orange >= interval_orange) 
  {
    prevMillis_orange = currentMillis;
    if (ledState_orange == LOW) 
    {
      ledState_orange = HIGH;
    } else {
      ledState_orange = LOW;
    }
    digitalWrite(orange_pin, ledState_orange);
  }
}

void blinkRedLED() 
{
  unsigned long currentMillis = millis();
  if (currentMillis - prevMillis_red >= interval_red) 
  {
    prevMillis_red = currentMillis;
    if (ledState_red == LOW) 
    {
      ledState_red = HIGH;
    } else {
      ledState_red = LOW;
    }
    digitalWrite(red_pin, ledState_red);
  }
}

void blinkPinkLED() 
{
  unsigned long currentMillis = millis();
  if (currentMillis - prevMillis_pink >= interval_pink) 
  {
    prevMillis_pink = currentMillis;
    if (ledState_pink == LOW) 
    {
      ledState_pink = HIGH;
    } else {
      ledState_pink = LOW;
    }
    digitalWrite(pink_pin, ledState_pink);
  }
}
void blinkBlueLED() 
{
  unsigned long currentMillis = millis();
  if (currentMillis - prevMillis_blue >= interval_blue) 
  {
    prevMillis_blue = currentMillis;
    if (ledState_blue == LOW) 
    {
      ledState_blue = HIGH;
    } else {
      ledState_blue = LOW;
    }
    digitalWrite(blue_pin, ledState_blue);
  }
}
void blinkYellowLED() 
{
  unsigned long currentMillis = millis();
  if (currentMillis - prevMillis_yellow >= interval_yellow) 
  {
    prevMillis_yellow = currentMillis;
    if (ledState_yellow == LOW) 
    {
      ledState_yellow = HIGH;
    } else {
      ledState_yellow = LOW;
    }
    digitalWrite(yellow_pin, ledState_yellow);
  }
}

void blinkGreenLED() 
{
  unsigned long currentMillis = millis();
  if (currentMillis - prevMillis_green >= interval_green) 
  {
    prevMillis_green = currentMillis;
    if (ledState_green == LOW) 
    {
      ledState_green = HIGH;
    } else {
      ledState_green = LOW;
    }
    digitalWrite(green_pin, ledState_green);
  }
}

void MCU_ID() 
{
  unsigned long currentMillis = millis();
  if (currentMillis - prevMillis_MCU_ID >= interval_MCU_ID) 
  {
    prevMillis_MCU_ID = currentMillis;
    Serial.println("I am MCU_B2");
  }
}
