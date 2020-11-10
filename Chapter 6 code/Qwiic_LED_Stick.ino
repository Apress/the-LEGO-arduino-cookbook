
    
/*-----------------------------------------------------------------------------------------------------
  LEGO LED Array
  Takes input from the front panel of the EV3 Intelligent Brick buttons to select LED patterns.
  LED patterns are displayed on a Qwiic LED Stick (sparkfun.com).  Three patterns are programmed:
     Binary Counter at pressing EV3 left button.
     Walking Rainbow at pressing EV3 right button.
     Cycle Rainbow at pressing EV3 up button.
  Communication from EV3 Intelligent Brick to Arduino is by analog voltages.
 
  Wire connections:
     Qwicc red wire to Arduino 3.3 V
     Qwicc black wire to Arduino GND
     Qwicc blue wire to Arduino SDL
     Qwicc yellow wire to Arduino SCL
     EV3 breakout board VBUS to Arduino Vin
     EV3 breakout board Ain to RC circuit
     EV3 breakout board GRND (next to Ain) to Arduino GND
     EV3 breakout board SCL, SDA, VBUS, GRND (next to VBUS) to resistor circuit
     EV3 cable between Breadboard Connector and Port A on EV3 Intelligent Brick

  Run program on EV3 Intelligent Brick called "LED selector".

  Qwiic LED Stick libraries and scripts copied from Sparkfun link.   
*/

#include <Wire.h>  //Call library for I2C communication between Arduino and Qwiic LED stick
#include "Qwiic_LED_Stick.h" //Call library for Qwicc LED stick

LED LEDStick; //Create an object of the LED class

int input;  //Declare variable to test for input level

void setup() {
  Wire.begin(); 
  Serial.begin(9600);  //Start serial communication, used for diagnostic purposes.
  
  LEDStick.begin();  //Start up communication with the LED Stick

 
}

void loop() {

 LEDStick.LEDOff(); //Turn off all LEDs
 input = analogRead(A0); //Read voltage level coming from EV3 Intelligent Brick
 
// Tests are run for three cases of voltage input, each in a while loop.
 
 while( (input > 175) && (input < 275) ) {  
     for (int i = 0; i < 1024; i++) {
        if ( (input > 275)  || (input < 175) )
        break;
        binaryLEDDisplay(i, 10);
      input = analogRead(A0);
      Serial.println(input); // Show input level on serial monitor.
      delay(1000);
  }
  }
 while( (input > 400) && (input < 600) )  {
  if ( (input > 600) || (input < 400) )
  break;
  WalkingRainbow(20, 10, 50);
   input = analogRead(A0);
   Serial.println(input); // Show input level on serial monitor.
 
 }
 

 while(input > 600)  {
  if (input < 600)
  break;
  CycleRainbow(10);
  input = analogRead(A0);
  Serial.println(input); // Show input level on serial monitor.
 
 }
}


//---------------------------------------------------------------------------------------------
//Functions follow for each of the three LED display algorithms.

//Walks a rainbow of length rainbowLength across LED strip of length LED Length with a delay of delayTime
//LEDLength<=rainbowLength<=255)
void WalkingRainbow(byte rainbowLength, byte LEDLength, int delayTime) {
  //Create three LEDs the same length as the LEDStick to store color values
  byte redArray[LEDLength];
  byte greenArray[LEDLength];
  byte blueArray[LEDLength];
  //This will repeat rainbowLength times, generating 3 arrays (r,g,b) of length LEDLength
  //This is like creating rainbowLength differnent rainbow arrays where the positions
  //of each color have changed by 1
  for (byte j = 0; j < rainbowLength; j++) {
    //This will repeat LEDLength times, generating 3 colors (r,g,b) per pixel
    //This creates the array that is sent to the LED Stick
    for (byte i = 0 ; i < LEDLength ; i++) {
      //there are n colors generated for the rainbow
      //the rainbow starts at the location where i and j are equal: n=1
      //the +1 accounts for the LEDs starting their index at 0
      //the value of n determines which color is generated at each pixel
      int n = i + 1 - j;
      //this will loop n so that n is always between 1 and rainbowLength
      if (n <= 0) {
        n = n + rainbowLength; 
      }
      //the nth color is between red and yellow
      if (n <= floor(rainbowLength / 6)) {
        redArray[i] = 255;
        greenArray[i] = floor(6 * 255 / (float) rainbowLength * n);
        blueArray[i] = 0;
      }
      //the nth color is between yellow and green
      else if (n <= floor(rainbowLength / 3)) {
        redArray[i] = floor(510 - 6 * 255 / (float) rainbowLength * n);
        greenArray[i] = 255;
        blueArray[i] = 0;
      }
      //the nth color is between green and cyan
      else if (n <= floor(rainbowLength / 2)) {
        redArray[i] = 0;
        greenArray[i] = 255;
        blueArray[i] = floor( 6 * 255 / (float) rainbowLength * n - 510);
      }
      //the nth color is between cyan and blue
      else if ( n <= floor(2 * rainbowLength / 3)) {
        redArray[i] = 0;
        greenArray[i] = floor(1020 - 6 * 255 / (float) rainbowLength * n);
        blueArray[i] = 255;
      }
      //the nth color is between blue and magenta
      else if (n <= floor(5 * rainbowLength / 6)) {
        redArray[i] = floor(6 * 255 / (float) rainbowLength * n - 1020);
        greenArray[i] = 0;
        blueArray[i] = 255;
      }
      //the nth color is between magenta and red
      else {
        redArray[i] = 255;
        greenArray[i] = 0;
        blueArray[i] = floor(1530 - (6 * 255 / (float)rainbowLength * n));;
      }
    }
    //sets all LEDs to the color values according to the arrays
    //the first LED corresponds to the first entries in the arrays
    LEDStick.setLEDColor(redArray, greenArray, blueArray, LEDLength);
    delay(delayTime);
  }
}

//Display binary on LEDS (LSB==LED10) of length LEDLength
void binaryLEDDisplay(int count, byte LEDLength) {
  //This for loop will repeat for each pixel of the LED Stick
  for (byte i = 0; i < LEDLength; i++) {
    //Below we use bit operators, which operate on the binary
    //representation of numbers.
    //For ithBit, we use the bitshift operator. count >> i takes the binary
    //representation of count and shifts it to the right i times. For example,
    //if count was 10, 0b1010, and i was 2, we get 0b10. if i was 3, we get 0b1.
    //This aligns the ith bit of count to the 0th bit of ithBit
    byte ithBit = count >> i;
    //Here we use the bitwise and. This returns a 1 only in the places where both
    //operands have a 1. For example, 0b1011 & 0b1010 == 0b1010. Here we use 0b1 as
    //an operand, which means our output will be whatever the 0th bit of ithBit is
    byte ithBitTrue = ithBit & 0b1;
    //Here we write to a single LED. We write only the color red,
    //but you can write to any combination of colors. We write to the
    //(10-i)th LED so that the last LED of your strip maps to bit 0
    //and is the least significant bit, or the one's place. The value
    //for the color will be 255*ithBitTrue. Since ithBitTrue can only
    //be 1 or 0, we only send color values of either 255 or zero. This
    //means that the (10-i)th LED will be red if the ith bit of the
    //count is 1, and will be off otherwise
    LEDStick.setLEDColor(10 - i, 255 * ithBitTrue, 0, 0);
  }
}

//Cycle through the rainbow with all LEDs the same color
void CycleRainbow(int delayTime) {
  //will repeat for each color from red to yellow
  for (byte g = 0; g < 255; g++) {
    //Set all LEDs to max red with green increasing each repetition
    LEDStick.setLEDColor(255, g, 0);
    delay(delayTime);
  }

  //will repeat for each color from yellow to green
  for (byte r = 255; r > 0; r--) {
    //Set all LEDs to max green with red decreasing each repetition
    LEDStick.setLEDColor(r, 255, 0);
    delay(delayTime);

  }

  //will repeat for each color from green to cyan
  for (byte b = 0; b < 255; b++) {
    //Set all LEDs to max green with blue increasing each repetition
    LEDStick.setLEDColor(0, 255, b);
    delay(delayTime);
  }

  //will repeat for each color from cyan to blue
  for (byte g = 255; g > 0; g--) {
    //Set all LEDs to max blue with green decreasing each repetition
    LEDStick.setLEDColor(0, g, 255);
    delay(delayTime);

  }

  //will repeat for each color from blue to magenta
  for (byte r = 0; r < 255; r++) {
    //Set all LEDs to max blue with red increasing each repetition
    LEDStick.setLEDColor(r, 0, 255);
    delay(delayTime);

  }

  //will repeat for each color from magenta to red

  for (byte b = 255; b > 0; b--) {
    //Set all LEDs to max red with blue decreasing each repetition
    LEDStick.setLEDColor(255, 0, b);
    delay(delayTime);

  }

}
