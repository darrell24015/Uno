/*
  blink2
  Turns two LED lights on and off repeatedly at different rates
  This example code is in the public domain
*/

// Connect the red LED to pin 10 and the green LED to pin 12
int red = 10;
int green = 12;
int wait1 = 100;
int wait2 = 50;

// The setup routine runs each time you press the reset button
void setup() {
  // initialize the pins as output
  pinMode(red, OUTPUT);
  pinMode(green, OUTPUT);
}

void loop() {
  // Turn the LED lights on with HIGH, change the wait time as desired
  digitalWrite(red, HIGH);
  delay(wait1);
  digitalWrite(green, HIGH);
  delay(wait1);
  digitalWrite(red, LOW);
  delay(wait2);
  digitalWrite(green, LOW);
  delay(wait2);

}
