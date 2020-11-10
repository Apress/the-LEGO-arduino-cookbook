/*--------------------------------------------------------------------------------------------------
LEGO Spectrum Analyzer
Takes audio spectrum analysis from SparkFun Spectrum shield to display spectral content on LED Matrix
and trigger three motorized mechanism.  
Data is passed from the Arduino to EV3 Intelligent Brick by I2C connection.

Connections:
EV3 Breadboard Connector VBUS to Arduino VIN
EV3 Breadboard Connector GRND (next to VBUS) to Arduino GND
EV3 Breadboard Connector SCL to Arduino SCL
EV3 Breadboard Connector SDA to Arduino SDA
EV3 cable between Breadboard Connector and Port 4 of EV3 Intelligent Brick
Mindsensors LED Matrix to Port 1 of EV3 Intelligent Brick
EV3 cable between EV3 Medium Motor and Port A of EV3 Intelligent Brick
EV3 cable between EV3 Large Motor and Port B of EV3 Intelligent Brick
EV3 cable between EV3 Medium Motor and Port C of EV3 Intelligent Brick
1/8 inch audio plug between audio source and Spectrum Shield Input
1/8 inch audio plug between external speark and Spectrum Shield Output

This script is used in conjunction with EV3 code "analyzer_with_motors".

Sections of code below were orginally developed by Toni Klopfenstein of SparkFun Electronics
and Ben Moyes of Bliptronnics.
Original code and other examples can be found at https://github.com/sparkfun/Spectrum_Shield

Arduino to EV3 connection modified from Dexter Industries post
www.dexterindustries.com/howto/connecting-ev3-arduino. 

--------------------------------------------------------------------------------------------------*/

//Declare Spectrum Shield pin connections
#define STROBE 4
#define RESET 6
#define DC_One A0
#define DC_Two A1 

#include <Wire.h>  //Call library for I2C communication

#define SLAVE_ADDRESS 0x04  //I2C address for communicating with EV3 Intelligent Brick.  
//Same address should be in EV3 program.

byte c[]={10,11,12,13,14,15,16,17};  //Declare array that will be sent to EV3 
//Intelligent Brick.  Load with dummy values that can help de-bugging


//Define spectrum variables
int freq_amp;
int Frequencies_One[7];
int Frequencies_Two[7]; 
int i;


void setup() {

  Serial.begin(9600);  //Start serial communication.  Serial monitor must match this baud rate.
  
  
  //Set Spectrum Shield pin configurations
  pinMode(STROBE, OUTPUT);
  pinMode(RESET, OUTPUT);
  pinMode(DC_One, INPUT);
  pinMode(DC_Two, INPUT);  
  digitalWrite(STROBE, HIGH);
  digitalWrite(RESET, HIGH);
  
  //Initialize Spectrum Analyzers
  digitalWrite(STROBE, LOW);
  delay(1);
  digitalWrite(RESET, HIGH);
  delay(1);
  digitalWrite(STROBE, HIGH);
  delay(1);
  digitalWrite(STROBE, LOW);
  delay(1);
  digitalWrite(RESET, LOW);
  
  Wire.begin(SLAVE_ADDRESS);
  
}


void loop() {
  
  Read_Frequencies();
  Serial.println(Frequencies_One[0]); //Serial output is used as a diagnostic.

  //Fill 8 bytes that will be sent to EV3 Intelligent Brick.  Values are divided
  //by 10 to fit within 8-bit word.  Only seven spectral bands are reported by
  //Spectrum Shield, so c[7] is loaded with a dummy value.
  c[0] = Frequencies_One[0]/10;
  c[1] = Frequencies_One[1]/10;
  c[2] = Frequencies_One[2]/10; 
  c[3] = Frequencies_One[3]/10;
  c[4] = Frequencies_One[4]/10;
  c[5] = Frequencies_One[5]/10;
  c[6] = Frequencies_One[6]/10;
  c[7] = 0;

  Wire.onRequest(sendData); //Send data to EV3
  
  delay(50);
 
}

//Function for sending data
void sendData()
{
  Wire.write(c,8); // c is the array of 8 bytes length.
}


//Function for reading frequencies from Spectrum Shield
void Read_Frequencies(){
  //Read frequencies for each band
  for (freq_amp = 0; freq_amp<7; freq_amp++)
  {
    Frequencies_One[freq_amp] = analogRead(DC_One);
    Frequencies_Two[freq_amp] = analogRead(DC_Two); 
    digitalWrite(STROBE, HIGH);
    digitalWrite(STROBE, LOW);
  }
}
