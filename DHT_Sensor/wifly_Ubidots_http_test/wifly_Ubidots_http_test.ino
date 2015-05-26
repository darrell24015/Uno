/*
This sketch is based on the original wifly_http example provided by
SeeedStudio.  This test should send a static value to Ubidots using 
the short token created in my Ubidots profile
*/

#include <Arduino.h>
#include <SoftwareSerial.h>
#include <WiFly.h>
#include <Debug.h>
#include <HTTPClient.h>

/* Ubidots configuration
#define TOKEN "MwfUgzsePHX23qkwzobofEh6OcIs97"  //Replace with your TOKEN
#define HumidityID "55443559762542161bf77cb3"
#define TemperatureID "554456c77625423c665ab445" //Replace with your variable ID
*/

#define HTTP_POST_URL "http://things.ubidots.com/api/v1.6/variables/55443559762542161bf77cb3/values?token=MwfUgzsePHX23qkwzobofEh6OcIs97"
#define HTTP_POST_DATA "{\"value\":45}"

// WiFi configuration
#define AUTH WIFLY_AUTH_WPA2_PSK
#define SSID "HOMENET12" // WiFi network to join
#define KEY "royalonion473" // WiFi password

SoftwareSerial uart(2, 3); // set these pins on the Xbee WiFi shield XB_TX and XB_RX
WiFly wifly(&uart); // create a WiFly object using the UART we created above
HTTPClient http; // create a HTTPClient object
char get; // variable to hold the HTTP response

void setup() {
  uart.begin(9600); // start the serial connection to the Xbee WiFi
  Serial.begin(9600); // start the serial monitor connection
  delay(3000); // wait 3 seconds
  wifly.reset();
  delay(15000); // wait 15 seconds

Serial.println("Joining: " SSID);
    if (wifly.join(SSID, KEY, AUTH)) {
      Serial.println("---------- WiFi Enabled ---------");
      Serial.println("------------- OK -------------"); 
   } else {
     Serial.println("---------- WiFi FAILED ----------"); 
   }
   
  Serial.println("\r\n\r\nTry to post data to url in variable HTTP_POST_URL");
  Serial.println("-------------------------------");
  while (http.post(HTTP_POST_URL, HTTP_POST_DATA, 10000) < 0) {
  }
  while (wifly.receive((uint8_t *)&get, 1, 1000) == 1) {
    Serial.print(get);
  }
  
  if (wifly.commandMode()) {
    Serial.println("\r\n\r\nEnter command mode. Send \"exit\"(with \\r) to exit command mode");
  }
} // end of setup()

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

} // end of loop()
