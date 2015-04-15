/*
 blink6
 ---------------------------------------------
 Turns on six LED lights in a specific pattern
 @author Darrell Little
 This example code is in the public domain
 ---------------------------------------------
*/
// set up array and variables
// each led is assigned a pin number in the array
// change the order of the array for a different pattern
int ledArray[] = {9,10,11,3,5,8};
int counter = 0;
int countDown = 0;
int timer = 100;

void setup() {
  // initialize all the pins in the array as output
  for (counter=0; counter < 6; counter++) {
    pinMode(ledArray[counter], OUTPUT);
   }
}

void loop() {
  // put your main code here, to run repeatedly
  // turn the lights on in order 2 times
  for (countDown=2; countDown > 0; countDown--) {
     for (counter=0; counter < 6; counter++) {
       digitalWrite(ledArray[counter], HIGH);
       delay(timer);
       digitalWrite(ledArray[counter], LOW);
       delay(timer);
     }
  }
  // flash all lights 4 times
  for (countDown=4; countDown > 0; countDown--) {
    for (counter=0; counter < 6; counter++) {
      digitalWrite(ledArray[counter], HIGH);
    }
      delay(timer);
    for (counter=0; counter < 6; counter++) {
      digitalWrite(ledArray[counter], LOW);
    }
      delay(timer);
  }
    // wait a short time before repeating cycle
    delay(300);
}

