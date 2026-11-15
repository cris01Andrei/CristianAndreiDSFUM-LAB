const int latchPin = 8;
const int clockPin = 12;
const int dataPin = 11;

byte digitTable[] = {
  B11111100, B01100000, B11011010, B11110010, B01100110,
  B10110110, B10111110, B11100000, B11111110, B11110110
};

unsigned long minTime = 999999;
unsigned long maxTime = 0;
unsigned long totalTime = 0;
int minVal = 0;
int maxVal = 0;
int rounds = 0;
const int maxRounds = 10;

void setup() {
  Serial.begin(9600);
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  randomSeed(analogRead(0));
}

void loop() {
  if (rounds < maxRounds) {
    int targetNum = random(1000, 10000);
    Serial.println(targetNum);
    
    unsigned long startTime = millis();
    
    bool guessed = false;
    while (!guessed) {
      displayNumber(targetNum);
      if (Serial.available() > 0) {
        int userNum = Serial.parseInt();
        if (userNum == targetNum) {
          unsigned long reactionTime = millis() - startTime;
          totalTime += reactionTime;
          
          if (reactionTime < minTime) {
            minTime = reactionTime;
            minVal = targetNum;
          }
          if (reactionTime > maxTime) {
            maxTime = reactionTime;
            maxVal = targetNum;
          }
          
          rounds++;
          guessed = true;
          delay(1000);
        }
      }
    }
    
    if (rounds == maxRounds) {
      Serial.println("--- STATISTICI ---");
      Serial.print("Timp minim: "); Serial.print(minTime); Serial.print(" ms pentru valoarea "); Serial.println(minVal);
      Serial.print("Timp maxim: "); Serial.print(maxTime); Serial.print(" ms pentru valoarea "); Serial.println(maxVal);
      Serial.print("Media timpilor: "); Serial.print(totalTime / maxRounds); Serial.println(" ms");
      while (true);
    }
  }
}

void displayNumber(int num) {
  int d[4];
  d[0] = num / 1000;
  d[1] = (num / 100) % 10;
  d[2] = (num / 10) % 10;
  d[3] = num % 10;

  for (int i = 0; i < 4; i++) {
    digitalWrite(latchPin, LOW);
    shiftOut(dataPin, clockPin, LSBFIRST, digitTable[d[i]]);
    shiftOut(dataPin, clockPin, LSBFIRST, (1 << i));
    digitalWrite(latchPin, HIGH);
    delay(2);
  }
}