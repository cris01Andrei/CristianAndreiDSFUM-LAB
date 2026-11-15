int ledPin = 9;
int brightness = 0;
int fadeAmount = 5;
unsigned long previousMillis = 0;
const long interval = 30;

void setup() {
  pinMode(ledPin, OUTPUT);
}

void loop() {
  unsigned long currentMillis = millis();
  
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    
    analogWrite(ledPin, brightness);
    
    brightness = brightness + fadeAmount;
    
    if (brightness <= 0 || brightness >= 255) {
      fadeAmount = -fadeAmount;
    }
  }
}