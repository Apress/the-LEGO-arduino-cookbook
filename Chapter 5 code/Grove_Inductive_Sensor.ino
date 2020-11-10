/*-------------------------------------------------------------------------------------------
Grove Inductive Sensor
Takes measurements from the Grove LDC1612 Inductive Sensor to detect the presence of metal.
The test case of metal was a US quarter coin.
If a metal is detected, this sketch sends a signal on Arduino Pin 10 with a pulse-width modulation
related to how far away the coin is located.

Connections:
Grove 5-V (red) to Arduino 5V
Grove Ground (black) to Arduino GND
Grove SCL (yellow) to Arduino SCL
Grove SDA (white) to Arduino SDA
Arduino pin 10 to RC filter (4.7kohm & 1uF) to Breadboard Connector AN IN
EV3 Breadboard Connector VBUS to Arduino VIN
EV3 Breadboard Connector GND (both of them) to Arduino GND
EV3 cable between Breadboard Connector and Port 4 on EV3 Intelligent Brick

Run program on EV3 Intelligent Brick called "metal detector".

This sketch was modified from github.com/Seeed-Studio/Seeed_LDC1612/blob/master/examples/coin_test_demo

-----------------------------------------------------------------------------------------------------*/

#include "Seeed_LDC1612.h"  //Call library for LDC Inductive Sensor

LDC1612 sensor;

//Define constants for various detection ranges.
const u32 DISTANCE_00_01=60000000;  // distance:<1mm
const u32 DISTANCE_01_05=45000000;  // distance:1mm~5mm
const u32 DISTANCE_05_10=44250000; // distance:5mm~10mm
const u32 DISTANCE_10_15=44080000; // distance:10mm~15mm
const u32 DISTANCE_15_20=44020000; // distance:15mm~20mm


void setup()

{

    Serial.begin(9600); //Start serial communications.  Serial monitor must match this baud rate.
    delay(100);
    Serial.println("start!");

    sensor.init();

    if(sensor.single_channel_config(CHANNEL_0))  //Check for error with Grove device connection.

    {
        Serial.println("can't detect sensor!");
        while(1);
    }

}


void loop()

{

    u32 result_channel1=0;
    setPwmFrequency(10,1);  //Set frequency of PWM higher than default

 
    /*Get channel 0 result and parse it.*/

    sensor.get_channel_result(CHANNEL_0,&result_channel1);


        if(result_channel1>=DISTANCE_00_01)

        {
            Serial.println("The distance to metal is 0~1mm");
            analogWrite(10, 0); //Set pin 10 for 0/255 PWM 
        }


        if(result_channel1<DISTANCE_00_01&&result_channel1>=DISTANCE_01_05)

        {
            Serial.println("The distance to metal is 1~5mm");
            analogWrite(10, 75);  //Set pin 10 for 75/255 PWM 
        }



        if(result_channel1<DISTANCE_01_05&&result_channel1>=DISTANCE_05_10)

        {
            Serial.println("The distance to metal is 5~10mm");
            analogWrite(10, 150);  //Set pin 10 for 150/255 PWM 
        }



        if(result_channel1<DISTANCE_05_10&&result_channel1>=DISTANCE_10_15)

        {
            Serial.println("No metal detected.");
            analogWrite(10, 200);  //Set pin 10 for 200/255 PWM 
        }


        delay(1000);
}


//Function for raising pulsewidth modulation frequency

void setPwmFrequency(int pin, int divisor) {
  byte mode;
  if(pin == 5 || pin == 6 || pin == 9 || pin == 10) {
    switch(divisor) {
      case 1: mode = 0x01; break;
      case 8: mode = 0x02; break;
      case 64: mode = 0x03; break;
      case 256: mode = 0x04; break;
      case 1024: mode = 0x05; break;
      default: return;
    }
    if(pin == 5 || pin == 6) {
      TCCR0B = TCCR0B & 0b11111000 | mode;
    } else {
      TCCR1B = TCCR1B & 0b11111000 | mode;
    }
  } else if(pin == 3 || pin == 11) {
    switch(divisor) {
      case 1: mode = 0x01; break;
      case 8: mode = 0x02; break;
      case 32: mode = 0x03; break;
      case 64: mode = 0x04; break;
      case 128: mode = 0x05; break;
      case 256: mode = 0x06; break;
      case 1024: mode = 0x07; break;
      default: return;
    }
    TCCR2B = TCCR2B & 0b11111000 | mode;
  }
}
