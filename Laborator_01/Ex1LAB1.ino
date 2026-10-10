int mode = 0;
unsigned long previousMillis = 0;
const long interval = 10000;
bool ledState = LOW;

void setup() {
  Serial.begin(9600);
  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);
}

void loop() {
  if (Serial.available() > 0) {
    char optiune = Serial.read();
    
    if (optiune == '1') {
      mode = 1;
      Serial.println("pornit");
      digitalWrite(13, HIGH);
      ledState = HIGH;
    } 
    else if (optiune == '2') {
      mode = 2;
      Serial.println("oprit");
      digitalWrite(13, LOW);
      ledState = LOW;
    } 
    else if (optiune == '3') {
      mode = 3;
      Serial.println("blink");
      previousMillis = millis();
    }
  }

  if (mode == 3) {
    unsigned long currentMillis = millis();
    
    if (currentMillis - previousMillis >= interval) {
      previousMillis = currentMillis;
      ledState = !ledState;
      digitalWrite(13, ledState);
    }
  }
}