#define ldrPin 11
#define amareloPin 4
#define vermelhoPin 6
#define azulPin 15
#define verdePin 17
#define pinBuzzer 1

void setup() {
  Serial.begin(115200);
  // put your setup code here, to run once:
  pinMode(ldrPin, INPUT);
  pinMode(amareloPin, OUTPUT);
  pinMode(vermelhoPin, OUTPUT);
  pinMode(azulPin, OUTPUT);
  pinMode(verdePin, OUTPUT);

  pinMode(pinBuzzer, OUTPUT);
}

void loop() {

  int ldrRead = analogRead(ldrPin);
  // uma execução por segundo
  delay(1000);

  if (ldrRead < 250){
    digitalWrite(amareloPin, HIGH);
    digitalWrite(vermelhoPin, LOW);
    digitalWrite(azulPin, LOW);
    digitalWrite(verdePin, LOW);

  } else if (ldrRead >= 250 && ldrRead < 500){
    digitalWrite(amareloPin, LOW);
    digitalWrite(vermelhoPin, HIGH);
    digitalWrite(azulPin, LOW);
    digitalWrite(verdePin, LOW);

  } else if (ldrRead >=500 && ldrRead < 800){
    digitalWrite(amareloPin, LOW);
    digitalWrite(vermelhoPin, LOW);
    digitalWrite(azulPin, HIGH);
    digitalWrite(verdePin, LOW);

  } else if (ldrRead >=800){
    digitalWrite(amareloPin, LOW);
    digitalWrite(vermelhoPin, LOW);
    digitalWrite(azulPin, LOW);
    digitalWrite(verdePin, HIGH);

  }

  // tone(pinBuzzer, 200);
}