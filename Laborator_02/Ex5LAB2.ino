const int targetPin = 8;
unsigned long period = 2000;
unsigned long highTime = 0;
unsigned long previousMicros = 0;
bool pinState = LOW;

int brightnessStep = 0;
int fadeAmount = 2;
unsigned long lastFadeTime = 0;
const unsigned long fadeInterval = 40;

void setup() {
  pinMode(targetPin, OUTPUT);
}

void loop() {
  unsigned long currentMillis = millis();
  if (currentMillis - lastFadeTime >= fadeInterval) {
    lastFadeTime = currentMillis;
    
    brightnessStep += fadeAmount;
    if (brightnessStep <= 0 || brightnessStep >= 255) {
      fadeAmount = -fadeAmount;
    }
    
    highTime = (unsigned long)(((float)brightnessStep / 255.0) * (float)period);
  }

  unsigned long currentMicros = micros();
  if (pinState == HIGH) {
    if (currentMicros - previousMicros >= highTime) {
      previousMicros = currentMicros;
      pinState = LOW;
      digitalWrite(targetPin, pinState);
    }
  } else {
    if (currentMicros - previousMicros >= (period - highTime)) {
      previousMicros = currentMicros;
      pinState = HIGH;
      digitalWrite(targetPin, pinState);
    }
  }
}