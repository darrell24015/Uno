/*
Adafruit Arduino - Lesson 7. RGB led fader
Use serial monitor to check status of switch
use variable switchVal to read switch
print with Serial.println(switchVal)
*/

int redLEDPin = 11;
int greenLEDPin = 10;
int blueLEDPin = 9;

int redSwitchPin = 4;
int greenSwitchPin = 3;
int blueSwitchPin = 2;

int red = 0;
int green = 0;
int blue = 0;


void setup() {
  // Serial.begin(9600);
  pinMode(redLEDPin, OUTPUT);
  pinMode(greenLEDPin, OUTPUT);
  pinMode(blueLEDPin, OUTPUT);
  pinMode(redSwitchPin, INPUT_PULLUP);
  pinMode(greenSwitchPin, INPUT_PULLUP);
  pinMode(blueSwitchPin, INPUT_PULLUP);

}

void loop() {
  // print status switch to serial monitor
  // int switchVal = digitalRead(redSwitchPin);
  // Serial.println(switchVal);
  
  // control level of each LED color
  if (digitalRead(redSwitchPin) == LOW) {
    red ++;
    if (red > 255) red = 0;
  }
  
  if (digitalRead(greenSwitchPin) == LOW) {
    green ++;
    if (green > 255) green = 0;
  }
  
  if (digitalRead(blueSwitchPin) == LOW) {
    blue ++;
    if (blue > 255) blue = 0;
  }
  
  analogWrite(redLEDPin, red);
  analogWrite(greenLEDPin, green);
  analogWrite(blueLEDPin, blue);
  
  delay(10);

}
