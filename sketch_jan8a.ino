/*
  Arduino TFT text example

  This example demonstrates how to draw text on the
  TFT with an Arduino. The Arduino reads the value
  of an analog sensor attached to pin A0, and writes
  the value to the LCD screen, updating every
  quarter second.

  This example code is in the public domain

  Created 15 April 2013 by Scott Fitzgerald

  http://www.arduino.cc/en/Tutorial/TFTDisplayText

 */

#include <TFT.h>  // Arduino LCD library
#include <SPI.h>

// pin definition for the Uno
#define cs   10
#define dc   9
#define rst  8
#define BUTTON_PIN 4
#define LED_PIN 6

// pin definition for the Leonardo
// #define cs   7
// #define dc   0
// #define rst  1

// create an instance of the library
TFT TFTscreen = TFT(cs, dc, rst);

// char array to print to the screen
char sensorPrintout[30];

void setup() {
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  Serial.begin(9600);

  // Put this line at the beginning of every sketch that uses the GLCD:
  TFTscreen.begin();

  // clear the screen with a black background
  TFTscreen.background(0, 0, 0);
  // write the static text to the screen
  // set the font color to white
  TFTscreen.stroke(255, 255, 255);
  // set the font size
  TFTscreen.setTextSize(2);
  // write the text to the top left corner of the screen, 20 rows below the top
  TFTscreen.text("e la usa!\n ", 0, 20);
  // ste the font size very large for the loop
  TFTscreen.setTextSize(2);
  
}

void open_door(){
  digitalWrite(LED_PIN, HIGH);  // turn the LED on (HIGH is the voltage level)
  delay(5000); 
}

void loop() {
  byte buttonState = digitalRead(BUTTON_PIN);
  
  if (buttonState == LOW) {
      open_door(); 
  }
  else {
      digitalWrite(LED_PIN, LOW);   // turn the LED off by making the voltage LOW
  }
  if (Serial.available() > 0) {
    //Erase the previous first line of the screen
    TFTscreen.stroke(0, 0, 0);
    //Write the name again because, if not, sometimes the screen would get black
    TFTscreen.text(personName, 0, 0);
    //Read name from serial
    String name = Serial.readStringUntil('\n');
    if (name == "Gabi"){
      open_door();
    }
    else{    
      //Convert from string to Char Array so the print function of the screen works
      name.toCharArray(personName, name.length()+1);
      // print the sensor value
      TFTscreen.text(personName, 0, 0);
      }

  }
  // convert the reading to a char array
  

  
}

