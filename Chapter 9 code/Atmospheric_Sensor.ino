/*----------------------------------------------------------------------------------------
  LEGO Weather Station

  This script reads temperature, pressure, and humidity from the SparkFun 
  Atmospheric Sensor (based on a BME280)

  Connections:
  Atmospheric Sensor GND to Arduino GND
  Atmospheric Sensor 3V3 to Arduino 3.3V
  Atmospheric Sensor CS to Arduino Pin 10
  Atmospheric Sensor SDI/SDA to Arduino Pin 11
  Atmospheric Sensor SDO/ADR to Arduino Pin 12
  Atmospheric Sensor SCK/SCL to Arduino Pin 13
  EV3 Breadboard VBUS to Arduino VIN
  EV3 Breadboard GRND (next to VBUS) to Arduino GND
  EV3 Breadboard SCL to Arduino SCL
  EV3 Breadboard SDA to Arduino SDA
  EV3 cable between Breadboard Connector and Port 4 of EV3 Intelligent Brick
  EV3 cable between EV3 Color Sensor and Port 1 of EV3 Intelligent Brick

  Use with EV3 program "weather_station"

  Sections of code taken from SparkFun github site, written by 
  Nathan Seidle

  Arduino to EV3 connection modified from Dexter Industries post
  www.dexterindustries.com/howto/connecting-ev3-arduino
  
-----------------------------------------------------------------------------------*/

#include <SPI.h>  //Call library for SPI communication
#include "SparkFunBME280.h"  //Call library for BME280 sensor
#include <Wire.h>  //Call library for I2C communication

#define SLAVE_ADDRESS 0x04  //I2C address for communicating with EV3 Intelligent
//Brick.  Same address should be in EV3 program

BME280 mySensor;

byte c[]={10,11,12,13,14,15,16,17}; //Declare array theat will be sent to EV3
//Intelligent Brick.  Load with dummy variables that can help de-bugging

void setup()
{
  Serial.begin(9600);  //Start serial communications.  Serial monitor must match this baud rate.
  Wire.begin(SLAVE_ADDRESS); //Start I2C link
  Serial.println("Reading basic values from BME280");

  if (mySensor.beginSPI(10) == false) //Begin communication over SPI. Use pin 10 as CS.
  {
    Serial.println("The sensor did not respond. Please check wiring.");
    while(1); //Freeze
  }
}

void loop()
{

  Serial.print(" Temp= ");  //Print label on serial monitor for diagnostic purposes
  Serial.print(mySensor.readTempF(), 2);  //Print for diagnostic purposes
  c[0] = round(mySensor.readTempF());  //Load value into array to be sent to EV3

  Serial.print(" Pressure= ");  //Print label on serial monitor for diagnostic purposes
  Serial.print(mySensor.readFloatPressure(), 0); //Print for diagnostic purposes
  c[1] = round(mySensor.readFloatPressure()/1000); //Load value into array to be sent to EV3

  Serial.print(" Humidity= "); //Print label on serial monitor for diagnostic purposes
  Serial.print(mySensor.readFloatHumidity(), 0); //Print for diagnostic purposes
  c[2] = round(mySensor.readFloatHumidity()); //Load value into array to be sent to EV3

  Serial.println();

  Wire.onRequest(sendData); //Send data to EV3

  delay(100);
}

//Function for sending data.
void sendData()
{
  Wire.write(c,8); //c is the array of 8 bytes length
}
