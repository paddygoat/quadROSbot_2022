
#include <SPI.h>              // include libraries
#include <LoRa.h>
#include <ros.h>
#include <std_msgs/String.h>

int ledState_03 = LOW;
unsigned long prevMillis_03 = 0;
const long interval_03 = 1400;

const long frequency = 433.5E6;  // LoRa Frequency
const int spreading = 12;       // ranges from 6-12
const int csPin = 4;          // LoRa radio chip select
const int resetPin = 2;        // LoRa radio reset
const int irqPin = 3;          // change for your board; must be a hardware interrupt pin

byte localAddress = 0xBB;     // address of this device
byte destination = 0xFF;      // destination to send to
long lastSendTime = 0;        // last send time

const int LED_pin_8 = 8;
const int LED_pin_7 = 7;
const int LED_pin_6 = 6;
const int LED_pin_5 = 5;

ros::NodeHandle  nh;
std_msgs::String str_msg;
ros::Publisher chatter("correction_data_from_nest", &str_msg);

char inChar[256];
// char previous_inChar[256];
int previous_incomingMsgId = 0;

void setup() 
{
  tone(9, 2000, 100);
  delay(100);
  tone(9, 1000, 100);
  delay(100);
  nh.initNode();
  nh.advertise(chatter);

  pinMode(LED_pin_8, OUTPUT);
  pinMode(LED_pin_7, OUTPUT);
  pinMode(LED_pin_6, OUTPUT);
  pinMode(LED_pin_5, OUTPUT);

  digitalWrite(LED_pin_5, HIGH);
  digitalWrite(LED_pin_6, HIGH);
  digitalWrite(LED_pin_7, HIGH);
  digitalWrite(LED_pin_8, HIGH);
  delay(1000);
  digitalWrite(LED_pin_5, LOW);
  digitalWrite(LED_pin_6, LOW);
  digitalWrite(LED_pin_7, LOW);
  digitalWrite(LED_pin_8, LOW);

  digitalWrite(LED_pin_7, HIGH);
  delay(5000);             // Do not delete this or it may brick the MCU.
  digitalWrite(LED_pin_7, LOW);

  // Serial.begin(115200);                   // initialize serial
  // while (!Serial);

  Serial.println("LoRa Reciever on Dog");

  // override the default CS, reset, and IRQ pins (optional)
  LoRa.setPins(csPin, resetPin, irqPin);// set CS, reset, IRQ pin

  if (!LoRa.begin(frequency)) 
  {             // initialize ratio at 915 MHz
    Serial.println("LoRa init failed. Check your connections.");
    while (true);                       // if failed, do nothing
  }
  // LoRa.setSpreadingFactor(12);           // ranges from 6-12,default 7 see API docs
  LoRa.setSpreadingFactor(spreading);           // ranges from 6-12,default 7 see API docs
  // LoRa.setSignalBandwidth(31.25E3); 
  // LoRa.setCodingRate4(5);
  // LoRa.enableCrc();
  // LoRa.writeRegister(REG_PA_CONFIG, PA_BOOST | (17 - 2));
  // LoRa.writeRegister(REG_PA_DAC, 0x87);  //turn on 3rd amplifier, see 5.4.3
  // LoRa.writeRegister(REG_OCP, 0x20 | 18); //increace power protection to 150mA RegOcp, see 5.4.4
  Serial.println("LoRa init succeeded.");
  Serial.println("waiting for incoming data ......");
}

void loop() 
{
  blinkLED_5();
  // parse for a packet, and call onReceive with the result:
  onReceive(LoRa.parsePacket());
  delay(5);
  // Serial.print("inChar: ");Serial.println(inChar);
  str_msg.data = inChar;
  // char hello[13] = "hello world!";
  // str_msg.data = hello;
  chatter.publish( &str_msg );
  nh.spinOnce();
}

char onReceive(int packetSize) 
{
  if (packetSize == 0) return;          // if there's no packet, return

  memset (inChar, 0, sizeof(inChar));

  // read packet header bytes:
  int recipient = LoRa.read();          // recipient address
  byte sender = LoRa.read();            // sender address
  byte incomingMsgId = LoRa.read();     // incoming msg ID
  byte incomingLength = LoRa.read();    // incoming msg length
  int i = 0;

  
  Serial.println("Message: ");
  while (LoRa.available())
  {
    inChar[i] = (char)LoRa.read();
    Serial.print(inChar[i]);
    i++;
  }
  // inChar[i] = "\0";     // This terminates the array?
  

  /*
  if (incomingLength != incoming.length()) 
  {   // check length for error
    Serial.println("error: message length does not match length");
    // return;                             // skip rest of function
  }
  */

  // if the recipient isn't this device or broadcast,
  if (recipient != localAddress && recipient != 0xFF) 
  {
    Serial.println("This message is not for me.");
    // return;                             // skip rest of function
  }

  // if message is for this device, or broadcast, print details:
  Serial.println("");
  Serial.println("Received from: 0x" + String(sender, HEX));
  Serial.println("Sent to: 0x" + String(recipient, HEX));
  Serial.println("Message ID: " + String(incomingMsgId));
  if ((previous_incomingMsgId != (int(incomingMsgId) - 1)) && (int(incomingMsgId) != 0))
  {
    Serial.println("An incoming message was missed - slow down the data transmit rate !!");
    tone(9, 2000, 100);
    delay(100);
    tone(9, 1000, 100);
    delay(100);
  }
  previous_incomingMsgId = int(incomingMsgId);
  Serial.println("Message length: " + String(incomingLength));
  Serial.println("RSSI: " + String(LoRa.packetRssi()));
  Serial.println("Snr: " + String(LoRa.packetSnr()));
  Serial.println();
  digitalWrite(LED_pin_6, HIGH);
  int pitch  =  4000 + LoRa.packetRssi()*20;
  tone(9, pitch, 100); 
  delay(100);
  digitalWrite(LED_pin_6, LOW);

  return inChar;
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
