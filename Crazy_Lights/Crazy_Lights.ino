/*
* Young Person's Guide to Arduino
* Chapter 9 - Crazy Lights
* Modifications by Darrell Little
* This software is in the public domain
*/

int light[] = {3,5,6,7,9,10,11,12,13};
int crazy[9];

void setup() {
  // put your setup code here, to run once:
  // Serial.begin(9600);
  randomSeed(analogRead(0));
  for (int x=0; x<9; x++) {
    pinMode(light[x], OUTPUT);
    digitalWrite(light[x], 0);
  }
}

void loop() {
  // put your main code here, to run repeatedly:
 
  for (int z=0; z<9; z++) {
    crazy[z] = random(0,2);
    digitalWrite(light[z], crazy[z]);
  }
  
  delay(200);

}
