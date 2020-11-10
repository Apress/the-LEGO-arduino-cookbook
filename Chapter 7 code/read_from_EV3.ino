
/*----------------------------------------------------------------------------------------
Writing Bytes from the EV3 Intelligent Brick

This sketch passes an array of data from the EV3 Intelligent Brick to the Arduino.  The
array is called d[], with 8 values assigned in the script below.  The values are displayed 
on the serial monitor.

Connections:
EV3 Breadboard VBUS to Arduino VIN
EV3 Breadboard GRND (next to VBUS) to Arduino GND
EV3 Breadboard SCL to Arduino SCL
EV3 Breadboard SDA to Arduino SDA
EV3 cable between breadboard connector and Port 1 of EV3 Intelligent Brick

Use with EV3 program "EV3_write"

Arduino to EV3 connection modified from Dexter Industries post
www.dexterindustries.com/howto/connecting-ev3-arduino
 
-----------------------------------------------------------------------------------*/

#include <Wire.h>  //Call library for I2C communications

#define SLAVE_ADDRESS 0x04  //I2C address for communicating with EV3 Intelligent
//Brick.  Same address should be in EV3 program


void setup() 
{
    Serial.begin(9600); //Start serial communications.  Serial monitor must match this baud rate.
    Wire.begin(SLAVE_ADDRESS);  //Start I2C link
    Wire.onReceive(receiveData); //Read data from EV3
    Serial.println("Ready!");
}
int val,flag=0,index=0;
byte d[]={10,11,12,13,14,15,16,17};  //dCeclare array to be sent to the Arduino
int i; //declare loop increment

void loop()
{
 Serial.println(d[0]);  //Send values to serial monitor.
 Serial.println(d[1]);
 Serial.println(d[2]);
 Serial.println(d[3]);
 Serial.println(d[4]);
 Serial.println(d[5]);
 Serial.println(d[6]);
 Serial.println(d[7]);
 delay(500);
}

//Function for reading data.
void receiveData(int byteCount)
{
    i=0; 
    while(Wire.available()>0)
        {
      val=Wire.read();
      d[i]=val;
      i = i + 1;
      flag=1;
      
    }

}
