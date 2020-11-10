/*----------------------------------------------------------------------------------------
Reading Bytes into the EV3 Intelligent Brick

This sketch passes an array of data from the Arduino to the EV3 Intelligent Brick.  The
array is called c[], with 8 values assigned in the script below.

Connections:
EV3 Breadboard VBUS to Arduino VIN
EV3 Breadboard GRND (next to VBUS) to Arduino GND
EV3 Breadboard SCL to Arduino SCL
EV3 Breadboard SDA to Arduino SDA
EV3 cable between breadboard connector and Port 1 of EV3 Intelligent Brick

Use with EV3 program "EV3_read"


Arduino to EV3 connection modified from Dexter Industries post
www.dexterindustries.com/howto/connecting-ev3-arduino
  
-----------------------------------------------------------------------------------*/

#include <Wire.h>  //Call library for I2C communications

#define SLAVE_ADDRESS 0x04  //I2C address for communicating with EV3 Intelligent
//Brick.  Same address should be in EV3 program

byte c[]={10,11,12,13,14,15,16,17}; //Declare array that will be sent to EV3
//Intelligent Brick.  

void setup()
{
  Serial.begin(9600);  //Start serial communications.  Serial monitor must match this baud rate.
  Wire.begin(SLAVE_ADDRESS); //Start I2C link
  Serial.println("Writing values to the EV3 Intelligent Brick . . .");

}

void loop()
{

  Wire.onRequest(sendData); //Send data to EV3
  delay(100);
}

//Function for sending data.
void sendData()
{
  Wire.write(c,8); //c is the array of 8 bytes length
}
