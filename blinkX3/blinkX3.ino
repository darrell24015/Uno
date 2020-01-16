/*
  blink
  http://arduino.cc/en/tutorial/blink
  Turns a LED on and off repeatedly
  This example code is in the public domain
*/

// Connect the anode of the LED to a pin, assign that pin number to variable led
// Connect the cathode of the LED to GND with a resistor inline
int led = 13;
// Create array with the times to wait between blinks
int waitArray[] = {50,100,300};
int wait = 0;

// The setup routine runs once when you press the reset button
void setup() {
  // initialize the pin as output
  pinMode(led, OUTPUT);
}

// The loop will repeat indefinately
void loop() {
  // Use a for loop, blink the LED with times from waitArray
  for (wait=0; wait<3; wait++) {
     digitalWrite(led,HIGH);
     delay(waitArray[wait]);
     digitalWrite(led,LOW);
     delay(waitArray[wait]); 
  }
}
