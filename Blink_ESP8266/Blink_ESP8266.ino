/*
* Blink for esp8266
*/

#define ESP8266_LED 2

void setup() {
  // put your setup code here, to run once:
  pinMode(ESP8266_LED, OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(ESP8266_LED, HIGH);
  delay(1000);
  digitalWrite(ESP8266_LED, LOW);
  delay(1000);

}
