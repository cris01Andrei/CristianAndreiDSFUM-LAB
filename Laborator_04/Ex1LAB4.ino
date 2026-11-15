const int buzzerPin = 8;

int melody[] = {
  392, 523, 523, 523, 587, 659, 698, 392,
  659, 523, 587, 392, 523, 523, 523, 587,
  659, 698, 784, 659, 523, 587, 523, 392,
  698, 698, 698, 784, 880, 698, 784, 659,
  523, 587, 659, 587, 523, 392, 523, 392
};

int noteDurations[] = {
  4, 4, 8, 8, 4, 4, 2, 4,
  4, 4, 2, 4, 4, 8, 8, 4,
  4, 4, 2, 4, 4, 4, 2, 4,
  4, 8, 8, 4, 4, 4, 2, 4,
  4, 4, 4, 4, 4, 4, 2, 1
};

void setup() {
  pinMode(buzzerPin, OUTPUT);
}

void loop() {
  for (int thisNote = 0; thisNote < 40; thisNote++) {
    int noteDuration = 1000 / noteDurations[thisNote];
    tone(buzzerPin, melody[thisNote], noteDuration);
    
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    noTone(buzzerPin);
  }
  delay(3000);
}