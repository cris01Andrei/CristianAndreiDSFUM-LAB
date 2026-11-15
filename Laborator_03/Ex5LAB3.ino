const int latchPin = 8;
const int clockPin = 12;
const int dataPin = 11;

const int btn1 = A1;
const int btn2 = A2;
const int btn3 = A3;

String text = "dECEbAL_Si_FiUL_SAU_LOCUiESC_PE_PLAiUL_dACiEi";

byte getCharEncoder(char c) {
  switch (c) {
    case 'A': case 'a': return B11101110;
    case 'b': return B00111110;
    case 'C': return B10011100;
    case 'c': return B00011010;
    case 'd': return B01111010;
    case 'E': case 'e': return B10011110;
    case 'F': return B10001110;
    case 'i': return B00001000;
    case 'J': return B01110000;
    case 'L': return B00011100;
    case 'O': case 'o': return B11111100;
    case 'P': return B11001110;
    case 'S': case 's': return B10110110;
    case 'U': case 'u': return B01111100;
    case '_': return B00000010;
    default: return B00000000;
  }
}

bool paused = false;
unsigned long lastScrollTime = 0;
int scrollIndex = 0;

void setup() {
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  pinMode(btn1, INPUT_PULLUP);
  pinMode(btn2, INPUT_PULLUP);
  pinMode(btn3, INPUT_PULLUP);
}

void loop() {
  if (digitalRead(btn1) == LOW || digitalRead(btn2) == LOW || digitalRead(btn3) == LOW) {
    paused = !paused;
    delay(300);
  }

  if (!paused && millis() - lastScrollTime > 300) {
    lastScrollTime = millis();
    scrollIndex++;
    if (scrollIndex >= text.length()) {
      scrollIndex = 0;
    }
  }

  char dispChars[4];
  for (int i = 0; i < 4; i++) {
    int idx = (scrollIndex + i) % text.length();
    dispChars[i] = text[idx];
  }

  for (int i = 0; i < 4; i++) {
    digitalWrite(latchPin, LOW);
    shiftOut(dataPin, clockPin, LSBFIRST, getCharEncoder(dispChars[i]));
    shiftOut(dataPin, clockPin, LSBFIRST, (1 << (3 - i)));
    digitalWrite(latchPin, HIGH);
    delay(2);
  }
}