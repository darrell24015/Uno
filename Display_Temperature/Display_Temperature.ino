#include "DHT.h"
#include "U8glib.h"

#define DHTPIN 2     // what pin DHT is connected to
#define backlight_pin 6 // PWM pin for the display LED
#define DHTTYPE DHT11 // Which type DHT you're using
float h;
float f;

// Initialize DHT sensor for normal 16mhz Arduino
DHT dht(DHTPIN, DHTTYPE);
// Initialize u8g, change the pins to match how it is connected
U8GLIB_PCD8544 u8g(13, 12, 9, 11, 10);  // CLK=13, DIN=12, CE=9, DC=11, RST=10

void draw(void) {
  u8g.setFont(u8g_font_profont11);  // select font
  u8g.drawStr(0, 10, "T: ");  // put string of display at position X, Y
  u8g.drawStr(0, 20, "H: ");
  u8g.setPrintPos(15, 10);  // set position
  u8g.print(f);  // display temperature from DHT11
  u8g.drawStr(50, 10, "F ");
  u8g.setPrintPos(15, 20);
  u8g.print(h);  // display humidity from DHT11
  u8g.drawStr(50, 20, "% ");
  u8g.drawStr(0,30, "Temperature &");
  u8g.drawStr(0,40, "Humidity");
}

void setup() {
  // put your setup code here, to run once:
  dht.begin();
  analogWrite(backlight_pin, 10);  // Set the Backlight intensity
  u8g.setRot180(); // flip screen, if required
}

void loop() {
  // put your main code here, to run repeatedly:
  h = dht.readHumidity();
  f = dht.readTemperature(true);
  u8g.firstPage();  
  do {
    draw();
  } while( u8g.nextPage() );
  
  delay(5000);  // Delay of 5sec before accessing DHT11

}
