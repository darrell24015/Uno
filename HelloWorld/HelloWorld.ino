
/*
 * HelloWorld
 * Author: Darrell Little - UselessApps.net
 * 
 * Displays opening screen and then plays a sound on button press
 * 
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 */

#include <SPI.h>
#include <audio.h>
#include <Arduboy.h>
#include <core.h>
#include <EEPROM.h>

Arduboy myArduboy;

// Initiate variables
String buttonPressed = "None";
byte pad;
boolean start = false;          // In title screen or start game
boolean paused = false;        // If game has been paused
char text[16];                // General string buffer
boolean initialDraw = false; // If the initial screen draw has happened

void intro() {
  for(int i = -8; i < 45; i = i + 2)
  {
    myArduboy.clearDisplay();
    myArduboy.setCursor(20, i);
    myArduboy.print("THIS IS ARDUBOY!");
    myArduboy.display();
    // Need small delay, scrolls too fast!
    delay(75);
  }
  
  tuneYes();
}

void getPressed() {
  if (myArduboy.pressed(UP_BUTTON)) {
    buttonPressed = "UP"; 
  }
    else if (myArduboy.pressed(LEFT_BUTTON)) {
      buttonPressed = "LEFT";   
    }
    else if (myArduboy.pressed(DOWN_BUTTON)) {
      buttonPressed = "DOWN";  
    }
    else if (myArduboy.pressed(RIGHT_BUTTON)) {
      buttonPressed = "RIGHT";      
    }
    drawPressed();
}

void drawPressed() {
  myArduboy.clearDisplay();
  myArduboy.setCursor(32, 22);
  myArduboy.print("You pressed:");
  myArduboy.setCursor(32, 42);
  myArduboy.print(buttonPressed);
  myArduboy.display();
  tuneYes();
  delay(500); 
}

void notPressed() {
  myArduboy.clearDisplay();
  myArduboy.setCursor(22, 42);
  myArduboy.print("Wrong Button!");
  myArduboy.display();
  buttonPressed = "WRONG";
  tuneNo();
  delay(500);
}

void tuneYes() {
  myArduboy.tunes.tone(987, 160);
  delay(160);
  myArduboy.tunes.tone(1318, 400);
  delay(500);
}

void tuneNo() {
  myArduboy.tunes.tone(1318, 400);
  delay(160);
  myArduboy.tunes.tone(987, 160);
  delay(500);
}

void titleScreen() {
  //Clears the screen
  myArduboy.clearDisplay();
  myArduboy.setCursor(10, 12);
  myArduboy.print("Press Button");
  myArduboy.setCursor(10, 32);
  myArduboy.print("Up Left Down Right");
  myArduboy.setCursor(10, 52);
  myArduboy.print("Last Press: " + buttonPressed);
  myArduboy.display();
  }

void setup() {
  myArduboy.start();
  myArduboy.setFrameRate(60);
  myArduboy.setCursor(29, 22);
  myArduboy.print("Hello World!");
  myArduboy.display();
  delay(1500);
  intro();
}

void loop() {
  titleScreen();
  
  if (myArduboy.pressed(UP_BUTTON) || 
      myArduboy.pressed(DOWN_BUTTON) ||
      myArduboy.pressed(RIGHT_BUTTON) ||
      myArduboy.pressed(LEFT_BUTTON)) 
      {
        getPressed();
      }
  else if 
       (myArduboy.pressed(A_BUTTON) ||
        myArduboy.pressed(B_BUTTON))
        {
          notPressed();
        }   
}
