/*
  New Blink
  Turns the on-board LED on and off
  Blinks a LED on and off with timing in an array
  This example code is in the public domain
*/

// Connect the anode of the LED to a pin, assign that pin number to variable led
// Connect the cathode of the LED to GND with a 330 ohm resistor inline
// The on-board LED is connected to pin 13
int led = 11;
int board_led = 13;
// Create array with the times to wait between blinks
int waitArray[] = {50,100,300,50,100,300};
int wait = 0;

// The setup routine runs once when you press the reset button
void setup() {
  // initialize the pin as output
  pinMode(led, OUTPUT);
  pinMode(board_led, OUTPUT);
}

// The loop will repeat indefinately
void loop() {
  digitalWrite(board_led,HIGH);
  
  // Use a for loop, blink the LED with times from waitArray
  for (wait=0; wait<6; wait++) {
     digitalWrite(led,HIGH);
     delay(waitArray[wait]);
     digitalWrite(led,LOW);
     delay(waitArray[wait]); 
  }
  
  digitalWrite(board_led,LOW);
  delay(500);
}
