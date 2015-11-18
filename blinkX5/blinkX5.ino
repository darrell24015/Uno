/*
  blink
  http://arduino.cc/en/tutorial/blink
  Turns a LED on and off repeatedly
  This example code is in the public domain
*/

// Connect the anode of the LED to a pin, assign that pin number to variable led
// Connect the cathode of the LED to GND with a resistor inline
// Pin 13 is also connected the LED on the board, this is the "On" light
int led = 12;
int onLight = 13;
// Create array with the times to wait between blinks
int waitArray[] = {50,100,300,50,100,300};
int wait = 500;
int i;

// The setup routine runs once when you press the reset button
void setup() {
  // initialize the pins as output
  pinMode(led, OUTPUT);
  pinMode(onLight, OUTPUT);
}

// The loop will repeat indefinately
void loop() {
  // Before the loop, turn the onboard LED on, then off before the next loop
  // Use a for loop, blink the LED with times from waitArray
  digitalWrite(onLight,HIGH); 
    for (i=0; i<6; i++) {
       digitalWrite(led,HIGH);
       delay(waitArray[i]);
       digitalWrite(led,LOW);
       delay(waitArray[i]); 
      }
  digitalWrite(onLight,LOW);
  delay(wait);
}
