/*
Input Pullup Serial

Switch attached from pin 2 to ground
Built-in LED on pin 13

This example code is in the public domain
*/

void setup() {
  // start serial connection
  Serial.begin(9600);
  // configure pin 2 as input with internal pull-up resistor
  pinMode(2, INPUT_PULLUP);
  pinMode(13, OUTPUT);

}

void loop() {
  // read the pushbutton value to a variable
  int sensorVal = digitalRead(2);
  Serial.println(sensorVal);
  
  // Pin 2 is HIGH when open (button not pushed)
  // LOW when pressed
  // Turn on pin 13 LED when button pressed (LOW)
  if (sensorVal == HIGH) {
    digitalWrite(13, LOW);
  }
  else {
    digitalWrite(13, HIGH);
  }

}
