
/*----------------------------------------------------------------------------------------
Favorite Color Machine

  This script sets the color of an Adafruit NeoPixel Array based on red/green/blue input
  from the EV3 Intelligent Brick.  Each red/green/blue component setting is generated
  by the EV3 Intelligent Brick and passed over I2C to the Arduino

  Connections:
  EV3 Breadboard VBUS to Arduino VIN
  EV3 Breadboard GRND (next to VBUS) to Arduino GND
  EV3 Breadboard SCL to Arduino SCL
  EV3 Breadboard SDA to Arduino SDA
  EV3 cable between breadboard connector and Port 1 of EV3 Intelligent Brick

  Use with EV3 program "favorite color.ev3"


  Arduino to EV3 connection modified from Dexter Industries post
  www.dexterindustries.com/howto/connecting-ev3-arduino
  
-----------------------------------------------------------------------------------*/

#include <Adafruit_NeoPixel.h>
#include <Wire.h>  //Call library for I2C communications

#define SLAVE_ADDRESS 0x04  //I2C address for communicating with EV3 Intelligent
//Brick.  Same address should be in EV3 program

const int ROWS = 5;
const int COLS = 8;
const int NUM_LEDS = ROWS * COLS;
const int LED_PIN = 6;
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, LED_PIN, NEO_GRB + NEO_KHZ800);

void setup() 
{
    strip.begin();
    strip.show(); //Initialize all pixels to 'off'
    Serial.begin(9600);         //Start serial communications.  Serial monitor must match this baud rate
    Wire.begin(SLAVE_ADDRESS);  //Start I2C link
    Wire.onReceive(receiveData); //Read data from EV3
    Serial.println("Ready!");
}
int val,flag=0,index=0;
byte d[]={10,11,12,13,14,15,16,17};  //Declare array to be sent to the Arduino
int i; //Declare loop increment
int red;  //Declare red color value
int green;  //Declare green color value
int blue;  //Declare blue color value

void loop()
{
 red = d[0]*2;  //Value from EV3 is 127 max, so double to set to 254 max
 green = d[1]*2;  //Value from EV3 is 127 max, so double to set to 254 max
 blue = d[2]*2;  //Value from EV3 is 127 max, so double to set to 254 max
 strip.begin();
 for (int counter = 0; counter < 40; counter++){
 strip.setPixelColor(counter,red,green,blue);
}
 strip.show();
 delay(100);
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
