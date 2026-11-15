const int numPins = 6;
const int pins[numPins] = {8, 9, 10, 11, 12, 13};
unsigned long periods[numPins] = {2000, 2500, 1500, 3000, 1800, 2200};

unsigned long highTimes[numPins] = {0, 0, 0, 0, 0, 0};
unsigned long previousMicros[numPins] = {0, 0, 0, 0, 0, 0};
bool pinStates[numPins] = {LOW, LOW, LOW, LOW, LOW, LOW};

int brightness[numPins] = {0, 40, 80, 120, 160, 200};
int fadeAmounts[numPins] = {2, 3, 1, 4, 2, 3};
unsigned long lastFadeTimes[numPins] = {0, 0, 0, 0, 0, 0};
const unsigned long fadeInterval = 30;

void setup() {
  for (int i = 0; i < numPins; i++) {
    pinMode(pins[i], OUTPUT);
  }
}

void loop() {
  unsigned long currentMillis = millis();
  if (currentMillis - lastFadeTimes[0] >= fadeInterval) {
    for (int i = 0; i < numPins; i++) {
      lastFadeTimes[i] = currentMillis;
      brightness[i] += fadeAmounts[i];
      if (brightness[i] <= 0 || brightness[i] >= 255) {
        fadeAmounts[i] = -fadeAmounts[i];
      }
      highTimes[i] = (unsigned long)(((float)brightness[i] / 255.0) * (float)periods[i]);
    }
  }

  unsigned long currentMicros = micros();
  for (int i = 0; i < numPins; i++) {
    if (pinStates[i] == HIGH) {
      if (currentMicros - previousMicros[i] >= highTimes[i]) {
        previousMicros[i] = currentMicros;
        pinStates[i] = LOW;
        digitalWrite(pins[i], pinStates[i]);
      }
    } else {
      if (currentMicros - previousMicros[i] >= (periods[i] - highTimes[i])) {
        previousMicros[i] = currentMicros;
        pinStates[i] = HIGH;
        digitalWrite(pins[i], pinStates[i]);
      }
    }
  }
}