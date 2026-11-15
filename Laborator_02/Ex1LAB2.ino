void setup() {
  for (int i = 8; i <= 13; i++) {
    pinMode(i, OUTPUT);
  }
}

void loop() {
  for (int val = 0; val < 64; val++) {
    for (int i = 0; i < 6; i++) {
      int pinState = (val >> i) & 0x01;
      digitalWrite(8 + i, pinState);
    }
    delay(500);
  }
}