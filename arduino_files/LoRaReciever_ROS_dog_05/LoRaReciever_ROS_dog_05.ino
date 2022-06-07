#include <SPI.h>
#include <LoRa.h>
#include <ros.h>
#include <std_msgs/String.h>

ros::NodeHandle  nh;
std_msgs::String str_msg;
ros::Publisher chatter("correction_data_from_nest", &str_msg);

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
byte msgCount = 0x00;            // count of outgoing messages
byte localAddress = 0xBB;     // address of this device
byte destination = 0xFF;      // destination to send to
long lastSendTime = 0;        // last send time
byte previous_incomingMsgId = 0x00;

char inChar[256];

void setup() 
{
  // Serial.begin(115200);
  // while (!Serial);

  nh.initNode();
  nh.advertise(chatter);

  tone(9, 2000, 200);
  delay(200);
  tone(9, 1000, 200);
  delay(200);

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

  Serial.println("LoRa Receiver Callback");

  LoRa.setPins(csPin, resetPin, irqPin);// set CS, reset, IRQ pin

  if (!LoRa.begin(frequency)) 
  {
    Serial.println("Starting LoRa failed!");
    while (1);
  }

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
  
  // Uncomment the next line to disable the default AGC and set LNA gain, values between 1 - 6 are supported
  // LoRa.setGain(6);
  
  // register the receive callback
  LoRa.onReceive(onReceive);

  // put the radio into receive mode
  LoRa.receive();
}

void loop() 
{
  blinkLED_5();
  // do nothing
}

void onReceive(int packetSize) 
{
  memset (inChar, 0, sizeof(inChar));
  digitalWrite(6, HIGH-digitalRead(6));   // toggle the led
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
    tone(9, 1000, 50);
    delay(50);
  }
  previous_incomingMsgId = int(incomingMsgId);


  str_msg.data = inChar;
  // char hello[13] = "hello world!";
  // str_msg.data = hello;
  chatter.publish( &str_msg );
  nh.spinOnce();
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
