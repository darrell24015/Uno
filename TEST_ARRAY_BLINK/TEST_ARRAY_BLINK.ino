int ledArray[] = {15,16,17,18,19,2,3,4,5,6};
int waitArray[] = {25,50,200};
int counter = 0;
int wait = 0;

void setup() {
  for (counter=0; counter<10; counter++) {
    pinMode(ledArray[counter], OUTPUT);
  }
}

void loop() {
  for (counter=0; counter<10; counter++) {
    for (wait=0; wait<3; wait++) {
      digitalWrite(ledArray[counter],HIGH);
      delay(waitArray[wait]);
      digitalWrite(ledArray[counter],LOW);
      delay(waitArray[wait]);
    }
  }
  //wait a short time before repeating cycle
  //delay(300);

}
