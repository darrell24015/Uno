// Derived from code written by ladyada at Adafruit, public domain
// Combined DHT11 sensor with XBee WiFi shield
// Designed to send measurements to Ubidots
// API key f4a44b0bbbfdc25207c5841ba91ada2c2bc9235c
// Humidity variable is 55443559762542161bf77cb3
// Temperature variable is 554456c77625423c665ab445
// WiFlyToken BxauWP1rrYSbDL69LxdPoD5ErHBlwZ65ihEMuHFiiOLyJhsPyb7JLy1JTmOW
// shortToken MwfUgzsePHX23qkwzobofEh6OcIs97
//#include<stdlib.h>  // needed to convert float to string (dtostrf)
#include <DHT.h>
#include <Arduino.h>
#include <SoftwareSerial.h>
#include <Debug.h>
#include <WiFly.h>
#include <WiFlyClient.h>

/* Ubidots configuration
#define TOKEN "MwfUgzsePHX23qkwzobofEh6OcIs97"  //Replace with your TOKEN
#define HumidityID "55443559762542161bf77cb3"
#define TemperatureID "554456c77625423c665ab445" //Replace with your variable ID
*/

// WiFi configuration
#define AUTH WIFLY_AUTH_WPA2_PSK
#define SSID "HOMENET12" // WiFi network to join
#define KEY "royalonion473" // WiFi password
#define DHTPIN 7     // which pin DHT11 is connected to

// Uncomment whatever type you're using!
#define DHTTYPE DHT11   // DHT 11 
//#define DHTTYPE DHT22   // DHT 22  (AM2302)
//#define DHTTYPE DHT21   // DHT 21 (AM2301)

// Connect pin 1 (on the left) of the sensor to +5V
// NOTE: If using a board with 3.3V logic like an Arduino Due connect pin 1
// to 3.3V instead of 5V!
// Connect pin 2 of the sensor to whatever your DHTPIN is
// Connect pin 4 (on the right) of the sensor to GROUND
// Connect a 10K resistor from pin 2 (data) to pin 1 (power) of the sensor

// Initialize DHT sensor for normal 16mhz Arduino
DHT dht(DHTPIN, DHTTYPE);
// NOTE: For working with a faster chip, like an Arduino Due or Teensy, you
// might need to increase the threshold for cycle counts considered a 1 or 0.
// You can do this by passing a 3rd parameter for this threshold.  It's a bit
// of fiddling to find the right value, but in general the faster the CPU the
// higher the value.  The default for a 16mhz AVR is a value of 6.  For an
// Arduino Due that runs at 84mhz a value of 30 works.
// Example to initialize DHT sensor for Arduino Due:
//DHT dht(DHTPIN, DHTTYPE, 30);

int led = 5;
SoftwareSerial uart(2, 3); // set these pins on the Xbee WiFi shield XB_TX and XB_RX
WiFly wifly(&uart); // create a WiFly object using the UART we created above

void setup() {
  uart.begin(9600); // start the serial connection to the Xbee WiFi
  Serial.begin(9600); // start the serial monitor connection
  delay(3000); // wait 3 seconds
  wifly.reset();
  delay(15000); // wait 15 seconds
  
  Serial.println("----------DHT11 Sensor Initiated----------");
  dht.begin();
  pinMode(led, OUTPUT);
  
  Serial.println("Joining: " SSID);
    if (wifly.join(SSID, KEY, AUTH)) {
      Serial.println("---------- WiFi Enabled ---------");
      Serial.println("------------- OK -------------"); 
   } else {
     Serial.println("---------- WiFi FAILED ----------"); 
   }
}

void loop() {

  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  digitalWrite(led, HIGH); // Turn the led on while taking measurements
  // Read humidity
  float h = dht.readHumidity();
  // Read temperature as Celsius
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit
  float f = dht.readTemperature(true);
  
  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  // Compute heat index
  // Must send in temp in Fahrenheit!
  float hi = dht.computeHeatIndex(f, h);
  Serial.println("---------- Raw Sensor Data ----------");
  Serial.print("Humidity: "); 
  Serial.print(h);
  Serial.print(" %\t");
  Serial.print("Temperature: "); 
  Serial.print(t);
  Serial.print(" *C ");
  Serial.print(f);
  Serial.print(" *F\t");
  Serial.print("Heat index: ");
  Serial.print(hi);
  Serial.println(" *F");
 
  // Convert floats to int before sending to Ubidots
      int tempS = (int) f;
    
  // Convert humidity to string for UbiDots
      int humiS = (int) h;
  Serial.println("---------- Converted Data ----------");
  Serial.print("Humidity: ");
  Serial.print(humiS);
  Serial.print(" %\t");
  Serial.print("Temperature: ");
  Serial.print(tempS);
  Serial.println(" *F\t");

   if ((save_value(humiS)) == 0) {
   Serial.println("Data successfully sent to Ubidots.com");
  } else {
    char r;
    while (wifly.receive((uint8_t *)&r, 1, 1000) == 1)
     {
       Serial.print(r);
     }
  }
  
  digitalWrite(led, LOW); // Turn the led off
  
  // Wait 15 minutes between measurements
  Serial.println("---------- Wait 15 minutes for next measurement ----------");
  delay(900000);
  // Wait 30 seconds between measurements
  // Serial.println("---------- Waiting 30 seconds for next measurement ----------");
  // delay(30000);
}

  // Function for Ubidots API
  int save_value(int data) {
  char post_data_buf[32];
  snprintf(post_data_buf, sizeof(post_data_buf), "{\"value\": %d}\r\n", data);

  char host[20];
  uint16_t port;


  if (!wifly.connect("things.ubidots.com", 80)) {
    Serial.println("Failed to connect to Ubidots.com!\r\n");
    return -2;
  }

  // Send request
  char buf[400];
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

