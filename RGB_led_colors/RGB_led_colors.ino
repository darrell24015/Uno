/*
Adafruit Arduino - Lesson 3. RGB led
*/

int redPin = 11;
int greenPin = 10;
int bluePin = 9;

// uncomment next line if using a Common Anode LED
// #define COMMON_ANODE

void setup() {
  // Set each pin mode to output
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);

}

void loop() {
  /* Loop through different color combinations
      by varying the number for RGB and send
      to the setColor funtion
  */
  
  setColor(255, 0, 0); // pure red
  delay(1000);
  setColor(0, 255, 0); // pure green
  delay(1000);
  setColor(0, 0, 255); // pure blue
  delay(1000);
  
  setColor(255, 255, 0); //yellow red + green
  delay(1000);
  setColor(80, 0, 80); // purple red + blue
  delay(1000);
  setColor(0, 255, 255); // aqua green + blue
  delay(1000);
  setColor(0, 0, 0); // no color
  delay(1000);

}

/* Create function to accept the level for each 
    color and write that to each pin
*/
void setColor(int red, int green, int blue) {
  // If using a Common Anode LED
  #ifdef COMMON_ANODE
    red = 255 - red;
    green = 255 - green;
    blue = 255 - blue;
  #endif
  
    analogWrite(redPin, red);
    analogWrite(greenPin, green);
    analogWrite(bluePin, blue);
}
