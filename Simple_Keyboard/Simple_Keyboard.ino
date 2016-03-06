/*
Simple Keyboard for Arduino
Based on SUG4R'S BLOG Simple Piezo Piano Using Arduino
https://godspeech.wordpress.com/2012/06/06/simple-piezo-piano-using-arduino/
See link for wiring diagram
*/
int speaker = 13; // digital pin for piezo speaker
int buttonPins[] = { 2, 3, 4, 5, 6, 7, 8, 9 }; // input pins for buttons
//Notes         'c'  , 'd',  'e',  'f',  'g', 'a',  'b',  'C'
int tones[] = { 1915, 1700, 1519, 1432, 1275, 1136, 1014, 956 }; //frequency
int playNote = 0;
int buttonState = 0;
void setup() {
  // put your setup code here, to run once:
  for (int x = 0; x < 8; x++) {
   pinMode(buttonPins[x], INPUT); 
  }  
  pinMode(speaker, OUTPUT);
  digitalWrite(speaker, LOW);
}
void loop() {
  // put your main code here, to run repeatedly:
  for (int x = 0; x < 8; x++) {
    buttonState = digitalRead(buttonPins[x]);
    if (buttonState == HIGH) {
      playNote = tones[x];
      digitalWrite(speaker, HIGH);
      delayMicroseconds(playNote);
      digitalWrite(speaker, LOW);
      delayMicroseconds(playNote);      
    }
    else digitalWrite(speaker, LOW); // if no button pressed, turn off piezo    
  }
}
