/*
Avocado Beginner Board
Use the potentiometer (pot) on analog pin 5 to  
turn on a light and play a tone in the C scale.

Speaker is on digital pin 8

Code for Tone 
created 21 Jan 2010
modified 30 Aug 2011
by Tom Igoe
 http://www.arduino.cc/en/Tutorial/Tone

This example code is in the public domain.
*/

#include "pitches.h"

int notes[] = {NOTE_C3,NOTE_D3,NOTE_E3,NOTE_F3,NOTE_G3,NOTE_A3,NOTE_B3,NOTE_C4};
char light[] = {6,5,3,10,9,7,13,12};
int pot = A5;
int sp = 8;


void setup() {
  // put your setup code here, to run once:
  for (int x = 0; x < 8; x++) {
    pinMode(light[x], OUTPUT);
  }

}

void loop() {
  // put your main code here, to run repeatedly:
  int Select = analogRead(pot);
  int LightNum = int(Select/128);
  for (int x = 0; x < 8; x++) {
    digitalWrite(light[x], LOW);
  }
  digitalWrite(light[LightNum], HIGH);
  tone(sp,notes[LightNum],100);
  
  delay(100);
  
  // noTone(sp);

}
