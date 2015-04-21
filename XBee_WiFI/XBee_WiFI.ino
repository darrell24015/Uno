#include <Debug.h>
#include <Arduino.h>
#include <SoftwareSerial.h>
#include <WiFly.h>
#include <WiFlyClient.h>
#define SSID "HOMENET12"
#define KEY "royalonion473"
#define AUTH WIFLY_AUTH_WPA2_PSK  // or WIFLY_AUTH_WPA1, WIFLY_AUTH_WEP, WIFLY_AUTH_OPEN

// set up serial port
SoftwareSerial uart(2, 3); // set these pins on the Xbee WiFi shield XB_TX and XB_RX
WiFly wifly(&uart); // create a WiFly object using the UART we created above

void setup() {
  // put your setup code here, to run once:
  uart.begin(9600); // start the serial connection
  Serial.begin(9600); // start the Arduino serial monitor window connection
  delay(3000); // wait 3 seconds
  Serial.println("---------- WiFi TEST ---------");
  wifly.reset();
  
  Serial.println("Joining: " SSID);
  if (wifly.join(SSID, KEY, AUTH)) {
   Serial.println("OK"); 
  } else {
   Serial.println("FAILED"); 
  }
  
  if (wifly.commandMode()) {
    Serial.println("Now in command mode. Send \"exit\"(with \\r) to exit command mode");
  }
  delay(5000);
  // display the WiFi parameters
  wifly.sendCommand("get wlan\r");
  char c;
  while (wifly.receive((uint8_t *)&c, 1, 300) > 0) {
    Serial.print((char)c);
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  
  // if there is data available from the shield
  while (wifly.available()) {
    Serial.write(wifly.read()); // display the data in the serial monitor window
  }
  // if a command has been entered
  while (Serial.available()) {
   wifly.write(Serial.read()); // send the command to the WiFi shield
  } 
}
