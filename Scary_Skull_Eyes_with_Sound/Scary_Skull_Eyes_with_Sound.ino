/*********************************************************************
 * Scary Halloween Skull Eyes with Sound
 * Author: Darrell Little
 * Date: October 15, 2017
 * This software is in the Public Domain
 * Creative Commons Zero v1.0 Universal
 * The Creative Commons CC0 Public Domain Dedication waives copyright interest 
 * in any work created and dedicates it to the world-wide public domain. 
 * 
 * PIR sensor power is connected to 5 volts, negative to ground
 * Use a function to return a boolean (True or False) if the PIR
 * sensor detects motion
 * 
 * When motion is detected 
 * play an audio file while
 * flashing the LED eyes multiple times using a function by passing it
 * number of times to blink and delay time.
 * 
 * MP3 Player Credits
 * Based on open source library:
 *   DFPlayer - A Mini MP3 Player For Arduino
 *   <https://www.dfrobot.com/index.php?route=product/product&product_id=1121>
 *   <Angelo.qiao@dfrobot.com>
 *   WARNING: Must use voltage dropping 1k resistors on software serial TX/RX lines
 *   to the DFPlayer.
 *   
 * Additional credits to Let's Code Blacksburg workshop
 * https://github.com/LetsCodeBlacksburg/arduino-talking-skull
 * LCBB_Talking-Skull_ping-servo-dfplayer_complete
 * By tweeks-pub1@theweeks.org
 *   
 *********************************************************************/

#include <SoftwareSerial.h>
#include <DFRobotDFPlayerMini.h>

// Set the constant values and variables used
const int led1 = 11; // one of two LED eyes
const int led2 = 10; // second of two LED eyes
const int pir = 6; // pin connected to the PIR sensor output
int sensorValue = LOW; // initial value of sensor reading

// DFPlayer mp3 player variables
const int ardRX = 2;       // The SoftwareSerial Receive line (Use 1K resistor, goes to DFPlayer TX)
const int ardTX = 3;       // The SoftwareSerial Transmit line (Use 1K resistor, goes to DFPlayer RX)
const int dfBusy = 12;     // Coming from DFPlayer pin 16, is active low (HIGH = not playing a sound)
int soundFile = 1;           // initial soundFile value
int fileCount = 15;         // Either set the # of files on SD card, or load it from myDFPlayer.readFileCounts()
int setVol = 20;           //Set volume value (0~30)

// Create SoftwareSerial instance
SoftwareSerial mySoftwareSerial(ardRX,ardTX); // Set the RX, TX pins

// Create DFPlayer instance
DFRobotDFPlayerMini myDFPlayer;

// Function to initialize the DFPlayer
void initDFPlayer() {
  if (myDFPlayer.begin(mySoftwareSerial)) {
    // configure settings
    myDFPlayer.setTimeOut(500); //Set serial communictaion time out 500ms
    myDFPlayer.volume(setVol);  //Set volume value (0~30).
    myDFPlayer.EQ(DFPLAYER_EQ_NORMAL);
    myDFPlayer.outputDevice(DFPLAYER_DEVICE_SD);
  }
}

// Function for reading the PIR sensor
// Return true if motion is detected
boolean isMotionDetected() {
  sensorValue = digitalRead(pir);
  if (sensorValue == HIGH) { // the sensor reads HIGH if motion is detected
    return true;
  }
  else
  {
    return false; // no motion
  }
}

// Function to blink the eyes rapidly multiple times
// pass to the function two values
void blinkEyes(int blinkRepeats, int waitTime) {
  for (int i = 0; i < blinkRepeats; i++) {
    turnOnEyes();
    delay(waitTime);
    turnOffEyes();
    delay(waitTime);
  }
}

// Function to turn on the LED eyes
void turnOnEyes() {
  digitalWrite(led1, HIGH);
  digitalWrite(led2, HIGH);
}

// Function to turn off the LED eyes
void turnOffEyes() {
  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);
}

void setup() {
  // Put your setup code here, initialize the pins as input or output
  pinMode(pir, INPUT);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(ardRX, INPUT);       
  pinMode(ardTX, OUTPUT);      
  pinMode(dfBusy, INPUT);
  // Start SoftwareSerial, initialize DFPlayer
  mySoftwareSerial.begin(9600);
  initDFPlayer();

} // end of setup() function

void loop() {
  // put your main code logic here, to run repeatedly
  // If played the last soundFile, then reset to 1
  if (soundFile == fileCount+1) {
    soundFile = 1;
  }
  
  if (isMotionDetected()) {
    myDFPlayer.play(soundFile);  // Play the next mp3 file
    delay(100);
    while(digitalRead(dfBusy) == false) {
      // Blink the LED eyes while mp3 is playing
      blinkEyes(3,150);
    }

  soundFile++;  // Increment the file number
  delay(3000); 
  }
  else {
    turnOffEyes();
  }

} // end of loop() function
