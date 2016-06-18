/*
* Young Person's Guide to Arduino
* Chapter 9 - Crazy Lights
* Modifications by Darrell Little
* This software is in the public domain
*/

int light[] = {6,7,8,9,10,11,12,13};
int crazy[8];

void setup() {
  // put your setup code here, to run once:
  // Serial.begin(9600);
  randomSeed(analogRead(0));
  for (int x=0; x<8; x++) {
    pinMode(light[x], OUTPUT);
    digitalWrite(light[x], 0);
  }

  // Turn lights on in order

  for (int x=0; x<8; x++) {
    digitalWrite(light[x], HIGH);
    delay(500);
    digitalWrite(light[x], LOW);
      }
    delay(500);
    
   for (int x=8; x>=0; x--) {
    digitalWrite(light[x], HIGH);
    delay(500);
    digitalWrite(light[x], LOW);
   }

    delay(1000);   
  
}

void loop() {
  // put your main code here, to run repeatedly:

 // Crazy Lights!
  for (int z=0; z<8; z++) {
    crazy[z] = random(0,2);
    digitalWrite(light[z], crazy[z]);
  }
  
  delay(200);

}
