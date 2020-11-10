/*-------------------------------------------------------------------------------

LEGO Intrusion Monitor
Takes a digital trigger on pin 12 to have the 1Sheeld+ take a picture and
send a notification email.

Connections:
EV3 Breadboard Connector VBUS to Arduino VIN
EV3 Breadboard Connector GRND (next to VBUS) to Arduino GND
EV3 Breadboard Connector GRND wired together with jumper wire
EV3 Breadboard Connector AN IN to two 1kohm resistors in series.
Other end of series resistors to Arduino GND
Arduino Pin 12 to joint of series resistors
Arduino Pin 13 to 330 ohm resistor in series with LED
Other end of LED to Arduino GND

This sketch is used in conjuction with EV3 code "ultrasonic_trigger.ev3"

1Sheeld+ app on smart phone should be running sheelds for Email and Camera

Sections of code taken from examples provided by 1Sheeld ()

-------------------------------------------------------------------------------*/

#define CUSTOM_SETTINGS //
#define INCLUDE_CAMERA_SHIELD  //
#define INCLUDE_EMAIL_SHIELD  // 

#include <OneSheeld.h> //Call library for 1Sheeld

int buttonPin = 12; //Set input pin, connected to EV3 Intelligent Brick
int ledPin = 13; //Set output pin, connected to LED

void setup()
{

  OneSheeld.begin(); //Start 1Sheeld communications
  pinMode(buttonPin,INPUT); //Set button pin as input
  pinMode(ledPin,OUTPUT); //Sets LED pin as output
}

void loop()
{
  if(digitalRead(buttonPin) == HIGH) //Checks the digital input state
  {
    digitalWrite(ledPin,HIGH); //Turn on LED
    Camera.frontCapture(); //Take a picture with front camera
    Email.send("type_your_address_here@gmail.com","Intruder!", "I took a picture of intruder!"); //Send email
    OneSheeld.delay(10000);  //Wait for 10 seconds

  }
  else
  {
    digitalWrite(ledPin,LOW);//Turn off LED
  }
    
}
