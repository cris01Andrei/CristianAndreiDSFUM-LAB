const int targetPin = 8;
unsigned long period = 2000;
unsigned long highTime = 1000;
unsigned long previousMicros = 0;
bool pinState = LOW;

void setup() {
  Serial.begin(9600);
  pinMode(targetPin, OUTPUT);
}

void loop() {
  if (Serial.available() > 0) {
    float voltage = Serial.parseFloat();
    if (voltage < 0.0) voltage = 0.0;
    if (voltage > 5.0) voltage = 5.0;
    
    highTime = (unsigned long)((voltage / 5.0) * (float)period);
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