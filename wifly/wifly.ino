/*
  Basic sketch for WiFly shield RN171
 
 This is a basic example to post a value on Ubidots with a simple
 Function "save_value".
 
 You need:
 * Arduino
 * WiFly Shield RN171
 * WiFly library
 
 Pins' connection
 Arduino       WiFly
  2    <---->    TX
  3    <---->    RX
 
 created 20 Aug. 2014
 by Mateo Velez - Metavix
 
 This example code is in the public domain.
 
 */
//-------------------------------------------------------------
//------------------------------Libraries----------------------
//-------------------------------------------------------------
#include <Arduino.h>
#include <SoftwareSerial.h>
#include <WiFly.h>
//-------------------------------------------------------------
//---------------------Ubudots Information---------------------
//-------------------------------------------------------------
/*
  API key f4a44b0bbbfdc25207c5841ba91ada2c2bc9235c
  Humidity variable is 55443559762542161bf77cb3
  Temperature variable is 554456c77625423c665ab445
  WiFlyToken BxauWP1rrYSbDL69LxdPoD5ErHBlwZ65ihEMuHFiiOLyJhsPyb7JLy1JTmOW
  shortToken MwfUgzsePHX23qkwzobofEh6OcIs97
*/
//-------------------------------------------------------------
//---------------------Network Configuration-------------------
//-------------------------------------------------------------
/* Change the AUTH according to your network settings
   If is open change to WIFLY_AUTH_OPEN
   If is WPA1 change to WIFLY_AUTH_WPA1
   If is WPA1_2 change to WIFLY_AUTH_WPA1
   If is WPA2 change to WIFLY_AUTH_WPA1
*/
#define SSID      "HOMENET12"
#define KEY       "royalonion473"
#define AUTH      WIFLY_AUTH_WPA2_PSK

SoftwareSerial uart(2, 3);
WiFly wifly(uart);
unsigned long start_millis = 0;

void setup() {
  Serial.begin(9600);
  Serial.println("------- Attempt to connect WiFly --------");
  
  uart.begin(9600);
  if (!wifly.isAssociated(SSID)) {
  while (!wifly.join(SSID, KEY, AUTH)) 
  {    
      Serial.println("Failed to join " SSID);
      Serial.println("Wait 3 seconds and try again...");
      delay(3000);
   }
    wifly.save();    
  }
  Serial.println("--------WiFly Connected--------");
}



void loop() {
  int reset = 0;
  
  // int valor = analogRead(A0);
  int valor = 45;  // use a static value for testing
  
  // call save_value() function
  while ((save_value(valor)) < 0) 
  {
    reset++;
    if(reset == 10)
    {
      asm volatile ("  jmp 0");  
    }
  }

//   Uncomment for debug

  char r;
   while (wifly.receive((uint8_t *)&r, 1, 1000) == 1) 
    {    
      Serial.print(r);
   }
   Serial.println("------- Pause 30 seconds -------");
   delay(30000);
}

// function to send data to Ubidots
int save_value(int dato)
{
  char post_data_buf[32];
  snprintf(post_data_buf, sizeof(post_data_buf), "{\"value\": %d}\r\n", dato);

  char host[20];
  uint16_t port;
  
  
  if (!wifly.connect("things.ubidots.com", 80)) {
    Serial.println("Failed to connect.\r\n");
    return -2;
  }
  
  // Send request
  char buf[200];
  //dont forget change your id and your token
  snprintf(buf, sizeof(buf), "POST /api/v1.6/variables/55443559762542161bf77cb3/values HTTP/1.1\r\nContent-Type: application/json\r\nContent-Length: %d\r\nX-Auth-Token: MwfUgzsePHX23qkwzobofEh6OcIs97\r\nHost: things.ubidots.com\r\n\r\n",strlen(post_data_buf));
  wifly.send(buf);
  
  // Send body
  if (post_data_buf != NULL) {
    wifly.send(post_data_buf);
  }
   wifly.send("\r\n");
  return 0;
}


