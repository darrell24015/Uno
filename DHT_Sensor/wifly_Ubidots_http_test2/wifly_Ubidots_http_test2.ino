#include <Arduino.h>
#include <SoftwareSerial.h>
#include <WiFly.h>
#include "HTTPClient.h"

/* Ubidots configuration
#define TOKEN "MwfUgzsePHX23qkwzobofEh6OcIs97"  //Replace with your TOKEN
#define HumidityID "55443559762542161bf77cb3"
#define TemperatureID "554456c77625423c665ab445" //Replace with your variable ID
*/
 
#define SSID      "HOMENET12"
#define KEY       "royalonion473"
// WIFLY_AUTH_OPEN / WIFLY_AUTH_WPA1 / WIFLY_AUTH_WPA1_2 / WIFLY_AUTH_WPA2_PSK
#define AUTH      WIFLY_AUTH_WPA2_PSK
 
#define HTTP_POST_URL "http://things.ubidots.com/api/v1.6/variables/55443559762542161bf77cb3/values?token=MwfUgzsePHX23qkwzobofEh6OcIs97"
//#define HTTP_POST_DATA "Hello world!"
 
// Pins' connection
// Arduino       WiFly
//  2    <---->    TX
//  3    <---->    RX
SoftwareSerial uart(2, 3);
WiFly wifly(uart);
HTTPClient http;
char get;
 
void setup() {
  Serial.begin(9600);    
  Serial.println("------- WIFLY HTTP --------");
  
  
  uart.begin(9600);         // WiFly UART Baud Rate: 9600
  // Wait WiFly to init
  delay(3000);
 
  // check if WiFly is associated with AP(SSID)
  if (!wifly.isAssociated(SSID)) {
    while (!wifly.join(SSID, KEY, AUTH)) {
      Serial.println("Failed to join " SSID);
      Serial.println("Wait 1 second and try again...");
      delay(1000);
    }
    
    wifly.save();    // save configuration, 
  }
 
  Serial.println("\r\n\r\nTry to post data to url - " HTTP_POST_URL);
  Serial.println("-------------------------------");
  delay(3000);
  
  while (http.post(HTTP_POST_URL, "{\"value\": 45}\r\n", 10000) < 0) {
  }
  while (wifly.receive((uint8_t *)&get, 1, 1000) == 1) {
    Serial.print(get);
  }
   
  if (wifly.commandMode()) {
    Serial.println("\r\n\r\nEnter command mode. Send \"exit\"(with \\r) to exit command mode");
  }
}
 
 
void loop() {
  int c;
  while (wifly.available()) {
    c = wifly.read();
    if (c > 0) {
      Serial.write((char)c);
    }
  }
  
  while (Serial.available()) {
    c = Serial.read();
    if (c >= 0) {
      wifly.write((char)c);
    }
  }
}
