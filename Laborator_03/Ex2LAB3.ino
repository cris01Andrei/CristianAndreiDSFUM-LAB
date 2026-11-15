const int latchPin = 8;
const int clockPin = 12;
const int dataPin = 11;

const int btnUp = A1;
const int btnDown = A2;
const int btnReset = A3;

int counter = 0;
bool lastUpState = LOW;
bool lastDownState = LOW;
bool lastResetState = LOW;

byte digitTable[] = {
  B11111100, B01100000, B11011010, B11110010, B01100110,
  B10110110, B10111110, B11100000, B11111110, B11110110
};

void setup() {
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  pinMode(btnUp, INPUT_PULLUP);
  pinMode(btnDown, INPUT_PULLUP);
  pinMode(btnReset, INPUT_PULLUP);
}

void loop() {
  bool currentUp = (digitalRead(btnUp) == LOW);
  bool currentDown = (digitalRead(btnDown) == LOW);
  bool currentReset = (digitalRead(btnReset) == LOW);

  if (currentUp && !lastUpState) {
    if (counter < 9999) counter++;
  }
  if (currentDown && !lastDownState) {
    if (counter > 0) counter--;
  }
  if (currentReset && !lastResetState) {
    counter = 0;
  }

  lastUpState = currentUp;
  lastDownState = currentDown;
  lastResetState = currentReset;

  displayNumberDynamic(counter);
}

void displayNumberDynamic(int num) {
  int d[4];
  d[0] = num / 1000;
  d[1] = (num / 100) % 10;
  d[2] = (num / 10) % 10;
  d[3] = num % 10;

  bool show = false;
  for (int i = 0; i < 4; i++) {
    if (i == 3) show = true;
    if (i == 2 && num >= 10) show = true;
    if (i == 1 && num >= 100) show = true;
    if (i == 0 && num >= 1000) show = true;

    if (show) {
      digitalWrite(latchPin, LOW);
      shiftOut(dataPin, clockPin, LSBFIRST, digitTable[d[i]]);
      shiftOut(dataPin, clockPin, LSBFIRST, (1 << i));
      digitalWrite(latchPin, HIGH);
      delay(3);
    }
  }
}