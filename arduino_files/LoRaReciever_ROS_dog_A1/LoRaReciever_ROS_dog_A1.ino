#include <SPI.h>
#include <LoRa.h>
#include <ros.h>
#include <std_msgs/String.h>

ros::NodeHandle  nh;
std_msgs::String str_msg;
ros::Publisher pub_A1("correction_data_from_nest_A1", &str_msg);

const long frequency = 433.5E6;  // LoRa Frequency
int spreading = 7;             // spreading factor ranges from 6-12,default 7 see API docs
const int csPin = 39;          // LoRa radio chip select
const int resetPin = 18;        // LoRa radio reset
const int irqPin = 20;          // change for your board; must be a hardware interrupt pin


int ledState_pink = LOW;
int pink_pin = A1;
unsigned long prevMillis_pink = 0;
const long interval_pink = 300;

int ledState_blue = LOW;
int blue_pin = A0;
unsigned long prevMillis_blue = 0;
const long interval_blue = 400;

int ledState_green = LOW;
int green_pin = A3;
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
int red_pin = 4;
unsigned long prevMillis_red = 0;
const long interval_red = 800;

String correction_data = "";

String outgoing;              // outgoing message
byte msgCount = 0x00;            // count of outgoing messages
byte localAddress = 0xBB;     // address of this device
byte destination = 0xFF;      // destination to send to
long lastSendTime = 0;        // last send time
byte previous_incomingMsgId = 0x00;

char inChar[256];

void setup() 
{
  // Serial.begin(57600);
  // while (!Serial);

  nh.initNode();
  nh.advertise(pub_A1);

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

  Serial.println("LoRa Receiver Callback");

  LoRa.setPins(csPin, resetPin, irqPin);// set CS, reset, IRQ pin

  if (!LoRa.begin(frequency)) 
  {
    Serial.println("Starting LoRa failed!");
    while (1);
  }

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
  
  // Uncomment the next line to disable the default AGC and set LNA gain, values between 1 - 6 are supported
  // LoRa.setGain(6);
  
  // register the receive callback
  LoRa.onReceive(onReceive);

  // put the radio into receive mode
  LoRa.receive();
}

void loop() 
{
  blinkGreenLED();
  // do nothing
}

void onReceive(int packetSize) 
{
  memset (inChar, 0, sizeof(inChar));
  digitalWrite(blue_pin, HIGH-digitalRead(blue_pin));   // toggle the led
  // received a packet
  Serial.print("Received packet: '");

  // read packet header bytes:
  int recipient = LoRa.read();          // recipient address
  byte sender = LoRa.read();            // sender address
  byte incomingMsgId = LoRa.read();     // incoming msg ID
  byte incomingLength = LoRa.read();    // incoming msg length
  // byte crc = LoRa.read();    // incoming crc value

  // read packet
  for (int i = 0; i < (packetSize-4); i++) 
  {
    inChar[i] = (char)LoRa.read();
    Serial.print(inChar[i]);
  }
  Serial.print("'");
  // print RSSI of packet
  Serial.print(" with RSSI ");
  Serial.print(LoRa.packetRssi());
  // Serial.println("Message recipient: " + String(recipient));
  // Serial.println("Message sender: " + String(sender));
  Serial.println(" Message ID: " + String(incomingMsgId));
  // Serial.println("Message incomingLength: " + String(incomingLength));
 
  if (previous_incomingMsgId != (incomingMsgId - 0x01) && (incomingMsgId != 0x00))
  {
    Serial.println("An incoming message was missed - slow down the data transmit rate !!");
    // tone(9, 1000, 50);
    digitalWrite(red_pin,HIGH);
    delay(50);
    digitalWrite(red_pin,LOW);
  }
  previous_incomingMsgId = int(incomingMsgId);


  str_msg.data = inChar;
  // char hello[13] = "hello world!";
  // str_msg.data = hello;
  pub_A1.publish( &str_msg );
  nh.spinOnce();
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
