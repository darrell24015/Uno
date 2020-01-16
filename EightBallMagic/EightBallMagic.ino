/*
 * EightBallMagic
 * Author: Darrell Little - UselessApps.net
 * 
 * Ask the Eight Ball anything, it will tell you no lies!
 * 
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 * 
 * Edit: 06/18/2016 
 * Updated code using new Arduboy library and Arduino IDE 1.6.9
 * Removed
 * #include <audio.h>
 * #include <EEPROM.h>
 * #include <core.h>
 * 
 */

#include <SPI.h>
#include <Arduboy.h>

#include "bitmaps.h"

Arduboy myArduboy;

// Store answers in an array
char* answers[] = {
  "  It is certain", "Reply hazy try again",
  "It is decidedly so", " Ask again later",
  " Without a doubt", "Better not tell you",
  " Yes, definately", "Cannot predict now",
  "You may rely on it", " Ask again later",
  "As I see it, yes", "Do not count on it",
  "   Most likely", "  My reply is no",
  "Outlook good", "My sources say no",
  "    Yes    ", "Outlook not so good",
  "Signs point to yes", "  Very doubtful"
};

int answerCount = 20; // the number of answers in the array

char* answer;

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
  eightBall();
}

void notPressed() {
  myArduboy.clearDisplay();
  myArduboy.setCursor(12, 42);
  myArduboy.print("Press the A Button");
  myArduboy.display();
  tuneNo();
  delay(500);
}

void thinking(){
  myArduboy.clearDisplay();
  myArduboy.drawSlowXYBitmap(0,5,small,56,56,1);
  myArduboy.setCursor(57,45);
  myArduboy.print("   Thinking   ");
  myArduboy.display();
  delay(1500);
}

void theAnswer() {
  thinking();
  answer = answers[random(answerCount)];
  
  for(int i = -8; i < 36; i = i + 2)
  {
    myArduboy.clearDisplay();
    myArduboy.setCursor(8, i);
    myArduboy.print(answer);
    myArduboy.display();
    // Need small delay, scrolls too fast!
    delay(75);
  }
  tuneYes();
  delay(1500);
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

void eightBall() {
  myArduboy.clearDisplay();
  myArduboy.drawSlowXYBitmap(0,0,eightball,128,46,1);
  myArduboy.setCursor(10,56);
  myArduboy.print("Eight Ball Magic");
  myArduboy.display();
  delay(3000);
}

void titleScreen() {
  myArduboy.clearDisplay();
  myArduboy.setCursor(1, 12);
  myArduboy.print("Think Of A Question");
  myArduboy.setCursor(1, 32);
  myArduboy.print("To Ask the 8-Ball");
  myArduboy.setCursor(1, 52);
  myArduboy.print("Press the A Button");
  myArduboy.display();
  }

void setup() {
  myArduboy.initRandomSeed();
  myArduboy.start();
  myArduboy.setFrameRate(60);
  myArduboy.setCursor(28, 5);
  myArduboy.print("Hello World!");
  myArduboy.display();
  delay(1500);
  intro();
}

void loop() {
  titleScreen();
  
  if (myArduboy.pressed(A_BUTTON)) 
      {
        theAnswer();
      }
  else if 
       (myArduboy.pressed(DOWN_BUTTON) ||
        myArduboy.pressed(UP_BUTTON) ||
        myArduboy.pressed(LEFT_BUTTON) ||
        myArduboy.pressed(RIGHT_BUTTON) ||
        myArduboy.pressed(B_BUTTON))
        {
          notPressed();
        }   
}
