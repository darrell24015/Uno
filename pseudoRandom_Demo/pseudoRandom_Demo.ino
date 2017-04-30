/*
 * pseudoRandom Demonstration sketch
 * Author: Darrell Little
 * Date: 04/29/2017
 * This code is in the public domain
 */
// Array to hold the pin numbers with LED connected
int ledPin[] = {11,10,9,6};
// Variable to set the delay time to blink
int waitTime = 1000;
// Variable to hold the random LED pin to blink
int randomLED;

void setup() {
  // put your setup code here, to run once:
  // Use reading on Analog pin 0 for a randon seed
  randomSeed(analogRead(0));
  // Initialize each pin in array to Output and Low (off)
  for (int x=0; x<4; x++) {
    pinMode(ledPin[x], OUTPUT);
    digitalWrite(ledPin[x], LOW);
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  // Randomly select a LED pin number
  randomLED = random(0,4);
  // Turn LED on
  digitalWrite(ledPin[randomLED], HIGH);
  delay(waitTime);
  // Turn LED off
  digitalWrite(ledPin[randomLED], LOW);
  delay(waitTime);
}
