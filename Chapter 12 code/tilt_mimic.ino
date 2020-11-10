/*---------------------------------------------------------------------------------------

Orientation Shield Example

This example tilts a LEGO motor to the same angle read in Y-axis orientation of  a smartphone.

Communication between EV3 Intelligent Brick and Arduino is by I2C
Connections:
ISheeld to smart phone by bluetooth
EV3 Breadboard VBUS to Arduino VIN
EV3 Breadboard GRND (next to VBUS) to Arduino GND
EV3 Breadboard SCL to Arduino SCL
EV3 Breadboard SDA to Arduino SDA
EV3 cable between Breadboard Connector and Port 4 of EV3 Intelligent Brick

Use with EV3 program "orientation.ev3"

1Sheeld+ app on smart phone should be running shield for Orientation

Remember to have 1Sheeld serial switch to SW to upload sketch, then go to HW. 

Arduino to EV3 connection modified from Dexter Industries post
www.dexterindustries.com/howto/connecting-ev3-arduino

----------------------------------------------------------------------------------------------*/

#define CUSTOM_SETTINGS  //
#define INCLUDE_ORIENTATION_SENSOR_SHIELD  //

#include <OneSheeld.h>  //Call library for 1Sheeld

#include <Wire.h>  //Call library for I2C communications

#define SLAVE_ADDRESS 0x04  //I2C address for communicating with EV3 Intelligent Brick.  Same address should be in EV3 program.

byte c[]={10,11,12,13,14,15,16,17};  //Declare array that will be sent to EV3 Intelligent Brick.  Loaded with dummy values that can help de-bugging.

void setup() 
{
  OneSheeld.begin(); //Start OneSheeld communications
  Wire.begin(SLAVE_ADDRESS);  //Start I2C communications
}

void loop()
{
  Serial.println(OrientationSensor.getY());  //Print orientation as diagnostic
  c[0] = OrientationSensor.getY();  //Store orientation in variable

  Wire.onRequest(sendData); //Send data to EV3
  delay(100);
}


//Function for sending data
void sendData()
{
  Wire.write(c,8); //c is the array of 8 bytes length.
}
