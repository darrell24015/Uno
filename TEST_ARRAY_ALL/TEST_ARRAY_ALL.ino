// Variables for Pins 
int ledArray[] = {15,16,17,18,19,2,3,4,5,6};
int waitArray[] = {25,50,200};
int counter = 0;
int wait = 0;

//TMP36 Temperature Sensor
int temperaturePin = 0;

float getVoltage(int pin) {
 return (analogRead(pin) * .004882814); //converting from a 0 to 1023 digital range
                                        // to 0 to 5 volts (each 1 reading equals ~ 5 millivolts
}

void setup() {
  for (counter=0; counter<10; counter++) {
    pinMode(ledArray[counter], OUTPUT);
  }
  
  Serial.begin(9600); // Start connection to Serial Monitor
  
} // End of setup()

void loop() {
  for (counter=0; counter<10; counter++) {
      digitalWrite(ledArray[counter],HIGH);      
  }
  
  // leave all lights on for 10 seconds
  
  delay(10000);
  
  for (counter=0; counter<10; counter++) {
    digitalWrite(ledArray[counter],LOW);  
  }
  
 float temperature = getVoltage(temperaturePin);  //getting the voltage reading from the temperature sensor
 temperature = (temperature - .5) * 100;          //converting from 10 mv per degree with 500 mV offset
                                                  //to degrees ((voltage - 500mV) times 100)
 Serial.println(temperature);
 
  //wait a short time before turning LED array back on
  
  delay(500);

} // End of loop()
