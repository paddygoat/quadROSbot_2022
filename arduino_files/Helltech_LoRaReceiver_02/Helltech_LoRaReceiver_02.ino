/* 
*/

#include "heltec.h"

#define BAND    433.5E6  //you can set band here directly,e.g. 868E6,915E6
const byte led_gpio = 25;
String correction_data_string;
String full_correction_data;
char correction_data_char[256];
char full_correction_data_char[2048];
String finish_check;
char inChar[256];


void setup() 
{
    //WIFI Kit series V1 not support Vext control
  Heltec.begin(true /*DisplayEnable Enable*/, true /*Heltec.LoRa Disable*/, true /*Serial Enable*/, true /*PABOOST Enable*/, BAND /*long BAND*/);
  Serial.begin(115200);
  Serial1.begin(38400, SERIAL_8N1, 2, 17);
  // Serial1.begin(9600, SERIAL_8N1, 2, 17);
  // while(!Serial);
  pinMode(led_gpio, OUTPUT);
  //WIFI Kit series V1 not support Vext control

  LoRa.setSignalBandwidth(500000);
  LoRa.setSpreadingFactor(7);

  Serial.print("LoRa.getSignalBandwidth: ");Serial.println(LoRa.getSignalBandwidth());
  Serial.print("LoRa.getSpreadingFactor: ");Serial.println(LoRa.getSpreadingFactor());
}

void loop() 
{
  // try to parse packet
  int packetSize = LoRa.parsePacket();
  if (packetSize) 
  {
    // received a packet
    Serial.print("Received packet: ");
    // read packet
    int i =0;
    correction_data_string = "";
    while (LoRa.available()) 
    {
      digitalWrite(led_gpio, HIGH-digitalRead(led_gpio));   // toggle the led
      inChar[i] = (char)LoRa.read();
      i++;
    }
    for(int i =4; i < 128; i++ )
    {
       correction_data_char[i-4] = inChar[i];
    }
    correction_data_string = correction_data_char;
    correction_data_string;
    // Serial.print("correction_data_string");Serial.println(correction_data_string);

    if (correction_data_string != "finish")
    {
      // full_correction_data = full_correction_data + correction_data_string;
      strcat(full_correction_data_char, correction_data_char);  // keeps appending until 'finish' detected.
      Serial.print("inChar: ");Serial.println(inChar);
      Serial.print("correction_data_char: ");Serial.print("'");Serial.print(correction_data_char);Serial.println("'");
      memset (inChar, 0, sizeof(inChar));
      memset (correction_data_char, 0, sizeof(correction_data_char));

    }
    else
    {
      Serial.println("");Serial.println("");
      Serial.println("Word finish was detected !!");
      Serial.print("full_correction_data_char array: ");Serial.println(full_correction_data_char);

      int arrayLength = 0;
      for (int i = 0; i < 2049; i++)
      {
        if(full_correction_data_char[i] != '\0')
        {
          ++arrayLength;
        }
        else
          break;
      }
      
      Serial.print("size of full_correction_data_char array: ");Serial.println(arrayLength);
      Serial1.write(full_correction_data_char);
      
      memset (correction_data_char, 0, sizeof(correction_data_char));
      memset (inChar, 0, sizeof(inChar));
      memset (full_correction_data_char, 0, sizeof(full_correction_data_char));

      

      // for(int i =0; i < 800; i++ )
      // {
      //   char c = full_correction_data[i];
      //   Serial1.write(c);
      //   Serial.print(c);
      // }
      // for(int i =0; i < 800; i++ )
      // {
      //  char c = full_correction_data[i];
      // byte c = message[i];
      //  Serial1.write(c);
      //  Serial.print(c);
      // }
      // Serial.print("full_correction_data: ");Serial.println(full_correction_data);
      
      Serial.println("");Serial.println("");
    }
  }
}
