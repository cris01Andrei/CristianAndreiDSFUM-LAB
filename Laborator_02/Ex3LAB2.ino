int ledPin = 9;
int brightness = 0;
int fadeAmount = 5;
unsigned long previousMillis = 0;
int interval = 30;

void setup() {
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
}

void loop() {
  if (Serial.available() > 0) {
    int speedInput = Serial.parseInt();
    if (speedInput > 0) {
      interval = speedInput;
    }
  }

  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    
    analogWrite(ledPin, brightness);
    
    brightness += fadeAmount;
    if (brightness <= 0 || brightness >= 255) {
      fadeAmount = -fadeAmount;
    }
  }
}