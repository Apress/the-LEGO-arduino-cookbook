 /*------------------------------------------------------------------------------
  LEGO Lidar
  Takes measurements from Garmin Lidar-Lite V3 and tranfers data to EV3 Intelligent Brick.
  Measurements are valid to 10-m of distance with 1-cm resolution.
  Lidar-Lite V3 mode of operation is with pulse width modulation.
  Communication between EV3 Intelligent Brick and Arduino is by I2C.
 
  Connections:
  LIDAR-Lite 5 Vdc (red) to Arduino 5v
  LIDAR-Lite Ground (black) to Arduino GND
  LIDAR-Lite Mode control (yellow) to Arduino digital input (pin 11)
  LIDAR-Lite Mode control (yellow) to 1 kOhm resistor lead 1
  1 kOhm resistor lead 2 to Arduino digital output (pin 12)
  EV3 Breadboard Connector VBUS to Arduino Vin
  EV3 Breadboard Connector GRND (next to VBUS) to Arduino GND
  EV3 Breadboard Connector SCL to Arduino SCL
  EV3 Breadboard Connector SDA to Arduino SDA
  EV3 cable between Breadboard Connector and Port 4 of EV3 Intelligent Brick

  Run program on EV3 Intelligent Brick called "lidar_40_m".
  
  See the Operation Manual for wiring diagrams and more information:
  http://static.garmin.com/pumac/LIDAR_Lite_v3_Operation_Manual_and_Technical_Specifications.pdf

  Arduino to EV3 connection modified from Dexter Industries post 
  www.dexterindustries.com/howto/connecting-ev3-arduino
------------------------------------------------------------------------------*/
#include <Wire.h>  //Call Library for I2C communications.

#define SLAVE_ADDRESS 0x04  //I2C address for communicating with EV3 Intelligent Brick.  Same address should be in EV3 program.

unsigned long pulseWidth;  //Declarevariable of pulse width measured from lidar.
unsigned long distance; //Declare variable of distance, related to pulse width.
byte c[]={10,11,12,13,14,15,16,17};  //Declaring array that will be sent to EV3 Intelligent Brick.  Loaded with dummy values that can help de-bugging.

void setup()
{
  Serial.begin(9600); //Start serial communications.  Serial monitor must match this baud rate.

  pinMode(12, OUTPUT); //Set pin 12 as trigger pin.
  digitalWrite(12, LOW); //Set trigger LOW for continuous read.

  pinMode(11, INPUT); //Set pin 11 as monitor pin.
 
  Wire.begin(SLAVE_ADDRESS);
  
}


void loop()
{
  pulseWidth = pulseIn(11, HIGH); //Count how long the pulse is high in microseconds.
  distance = pulseWidth / 40; //10usec = 1 cm of distance, with scaling by 4.

  if (distance <= 127) { // Test for range of values. Repeated in if statements below.
    c[0] = 0;
    c[1] = 0;
    c[2] = 0;
    c[3] = 0;
    c[4] = 0;
    c[5] = 0;
    c[6] = 0;
    c[7] = distance;
  } 

  if (distance > 127 && distance <= 254) {
    c[0] = 0;
    c[1] = 0;
    c[2] = 0;
    c[3] = 0;
    c[4] = 0;
    c[5] = 0;
    c[6] = distance - 127;
    c[7] = 127;
  }

   if (distance > 254 && distance <= 381) {
    c[0] = 0;
    c[1] = 0;
    c[2] = 0;
    c[3] = 0;
    c[4] = 0;
    c[5] = distance - 254;
    c[6] = 127;
    c[7] = 127;
  }

  if (distance > 381 && distance <= 508) {
    c[0] = 0;
    c[1] = 0;
    c[2] = 0;
    c[3] = 0;
    c[4] = distance - 381;
    c[5] = 127;
    c[6] = 127;
    c[7] = 127;
  }

  if (distance > 508 && distance <= 635) {
    c[0] = 0;
    c[1] = 0;
    c[2] = 0;
    c[3] = distance - 508;
    c[4] = 127;
    c[5] = 127;
    c[6] = 127;
    c[7] = 127;
  }

  if (distance > 635 && distance <= 762) {
    c[0] = 0;
    c[1] = 0;
    c[2] = distance - 635;
    c[3] = 127;
    c[4] = 127;
    c[5] = 127;
    c[6] = 127;
    c[7] = 127;
  }

    if (distance > 762 && distance <= 889) {
    c[0] = 0;
    c[1] = distance - 762;
    c[2] = 127;
    c[3] = 127;
    c[4] = 127;
    c[5] = 127;
    c[6] = 127;
    c[7] = 127;
  }

    if (distance > 889 && distance <= 1016) {
    c[0] = distance - 889;
    c[1] = 127;
    c[2] = 127;
    c[3] = 127;
    c[4] = 127;
    c[5] = 127;
    c[6] = 127;
    c[7] = 127;
  }
  
    Serial.println(distance); //Print the distance to Arduino serial monitor.
    Wire.onRequest(sendData); //Send data to EV3
 
}


//Function for sending data.
void sendData()
{
  Wire.write(c,8); //c is the array of 8 bytes length.
}
