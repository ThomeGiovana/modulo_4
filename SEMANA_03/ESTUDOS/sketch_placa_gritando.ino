#define buzzer 1
#define button 2

void setup() {
  pinMode(buzzer, OUTPUT);
  pinMode(button, INPUT_PULLUP);
  Serial.begin(115200);
}

void loop() {
  int currentState = digitalRead(button);
  Serial.println(currentState);
  if(currentState == 0){
    digitalWrite(buzzer, HIGH);
  } else {
    digitalWrite(buzzer, 0);
  }
}