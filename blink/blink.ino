/*
  blink
  http://arduino.cc/en/tutorial/blink
  Turns a LED on and off repeatedly
  This example code is in the public domain
*/

// Connect the anode of the LED to pin 12, assign pin 12 to variable led
// Connect the cathode of the LED to GND
int led = 13;

// The setup routine runs once when you press the reset button
void setup() {
  // initialize the pin as output
  pinMode(led, OUTPUT);
}

// The loop will repeat indefinately
void loop() {
  digitalWrite(led, HIGH); // Turn the led on, HIGH = 5V 
  delay(300); // Wait time
  digitalWrite(led, LOW); // Turn the led off, LOW = 0V
  delay(300); // Wait time
}
