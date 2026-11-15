const int latchPin = 8;
const int clockPin = 12;
const int dataPin = 11;

byte charTable[] = {
  B11101110, // A
  B00111110, // b
  B10011100, // C
  B01111010, // d
  B10011110, // E
  B10001110  // F
};

void setup() {
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
}

void loop() {
  for (int i = 0; i < 6; i++) {
    digitalWrite(latchPin, LOW);
    shiftOut(dataPin, clockPin, LSBFIRST, charTable[i]);
    shiftOut(dataPin, clockPin, LSBFIRST, B10000000);
    digitalWrite(latchPin, HIGH);
    delay(5000);
  }
}