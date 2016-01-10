/* Grove_LED_Button
* Demo of Grove - Starter Kit
* Loovee  2013-3-10
* This demo will show you how to use Grove Touch Sensor Button to control a LED
* Also works the same way with the mechanical button
* Grove - Button connect to D3
* Grove - LED connect to D7
*/

// Define your pins
const int pinButton = 3;
const int pinLED = 7;
const int boardLED = 13;

void setup() {
  // put your setup code here, to run once:
  pinMode(pinButton, INPUT);
  pinMode(pinLED, OUTPUT);
  pinMode(boardLED, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (digitalRead(pinButton)) {
    digitalWrite(pinLED, HIGH);
    digitalWrite(boardLED, HIGH);
    }
  
  else {
     digitalWrite(pinLED, LOW);
     digitalWrite(boardLED, LOW);
  }
  
  delay(10);

}
