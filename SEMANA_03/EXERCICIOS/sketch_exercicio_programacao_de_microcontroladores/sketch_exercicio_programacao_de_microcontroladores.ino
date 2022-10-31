// portas
#define ldrPin 11
#define amareloPin 4
#define vermelhoPin 6
#define azulPin 15
#define verdePin 17
#define pinBuzzer 8

#include <vector>

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
  delay(500);

  // valor máximo do LDR lido em testes: ~3000 - escala com 15 intervalos de 200
  // definição de intervalo de 0 a 15
  int ldrReadRescaled = (ldrRead*15)/3000;
  if (ldrReadRescaled > 15){
    ldrReadRescaled = 15;
  }
  Serial.println(ldrReadRescaled);

  // toca uma nota diferente a cada leitura
  BuzzerPlay(ldrReadRescaled);

  // conversão da ldrReadRescaled para binário
  int bin[4];
  int converted = ldrReadRescaled;
  if(8<=converted){
    converted = converted-8;
    bin[0] = 1;
  } else {
    bin[0] = 0;
  }
  if(4<=converted){
    converted = converted-4;
    bin[1] = 1;
  } else {
    bin[1] = 0;
  }
  if(2<=converted){
    converted = converted-2;
    bin[2] = 1;
  } else {
    bin[2] = 0;
  }
  if(1==converted){
    converted = converted-1;
    bin[3] = 1;
  } else {
    bin[3] = 0;
  }

  // ligar os LEDs de acordo com o binário
  if (bin[0] == 1){
    digitalWrite(amareloPin, HIGH);
  } else {
    digitalWrite(amareloPin, LOW);
  }

  if (bin[1] == 1){
    digitalWrite(vermelhoPin, HIGH);
  } else {
    digitalWrite(vermelhoPin, LOW);
  }

  if (bin[2] == 1){
    digitalWrite(azulPin, HIGH);
  } else {
    digitalWrite(azulPin, LOW);
  }

  if (bin[3] == 1){
    digitalWrite(verdePin, HIGH);
  } else {
    digitalWrite(verdePin, LOW);
  }

}

void BuzzerPlay(int n){
  tone(pinBuzzer, n*50);
}