int led[] = {6, 9, 10, 11};

void setup() {
  // put your setup code here, to run once:
  // Don't need anything here for this sketch

}

void loop() {
  // Fade in and out each LED in array
    for (int x=0; x<6; x++) {
      for (int fadeValue = 0 ; fadeValue <= 250; fadeValue += 5) {
        analogWrite(led[x], fadeValue);
        delay(20);
    }

    for (int fadeValue = 250 ; fadeValue >= 0; fadeValue -= 5) {
      analogWrite(led[x], fadeValue);
      delay(30);
    }
  }
}
