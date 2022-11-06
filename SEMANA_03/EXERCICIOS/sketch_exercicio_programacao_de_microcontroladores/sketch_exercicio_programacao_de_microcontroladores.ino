#define ldrPin 11
#define amareloPin 1
#define vermelhoPin 2
#define azulPin 3
#define verdePin 4
#define pinBuzzer 8
#define buttonArmazena 7
#define buttonReproduz 18

#include <vector>
#include <iostream>
#include <string>

int melodia[100];
int cont = 0;

void setup() {
  Serial.begin(115200);
  pinMode(ldrPin, INPUT);
  pinMode(amareloPin, OUTPUT);
  pinMode(vermelhoPin, OUTPUT);
  pinMode(azulPin, OUTPUT);
  pinMode(verdePin, OUTPUT);
  pinMode(pinBuzzer, OUTPUT);
  pinMode(buttonArmazena, INPUT);
  pinMode(buttonReproduz, INPUT);
}

void loop() {

  int ldrRead = analogRead(ldrPin);
  delay(500);
  // valor máximo do LDR lido em testes: ~3000 - escala com 15 intervalos de 200
  int ldrReadRescaled = (ldrRead*15)/3000;
  if (ldrReadRescaled > 15){
    ldrReadRescaled = 15;
  }

  BuzzerPlay(ldrReadRescaled); // toca uma nota diferente a cada leitura
  Serial.println(ldrReadRescaled);
  String strBin = converteBinario(ldrReadRescaled);

  // ligar os LEDs de acordo com o binário
  int i;
  for (i = 0; i < 4; i++){
    if(strBin[i] == '1'){
      digitalWrite(i+1, HIGH);
    } else {
      digitalWrite(i+1, LOW);
    }
  }

  //armazena o número atual em um vetor
  int buttonArmazenaState = digitalRead(buttonArmazena);
  if(buttonArmazenaState == 1){
    armazena(ldrReadRescaled);
    Serial.println("Armazenado!");
  }

  //reproduz o vetor
  int buttonReproduzState = digitalRead(buttonReproduz);
  if(buttonReproduzState == 1){
  Serial.println("Reproduzindo");
    int c;
    for(c=0;c<cont;c++){
      //ligar leds
      String strBin = converteBinario(melodia[c]);
      Serial.println(strBin);
      Serial.println(melodia[c]);
      int i;
      for (i = 0; i < 4; i++){
        if(strBin[i] == '1'){
          digitalWrite(i+1, HIGH);
        } else {
          digitalWrite(i+1, LOW);
        }
      }
      BuzzerPlay(melodia[c]);
      delay(3000);
      melodia[c] = 0;
    }
    cont = 0;
  }

  //----------------------------------------------------------

}

void BuzzerPlay(int n){
  tone(pinBuzzer, n*50);
}

String converteBinario(int ldrReadRescaled){
  // conversão da ldrReadRescaled para binário
  int bin[4];
  int pos = 0;      // posição no vetor
  int valorBin = 8; // 8, 4, 2, 1
  int converted = ldrReadRescaled;

  while (valorBin >= 1){
    if (valorBin <= converted){
      converted = converted - valorBin;
      bin[pos] = 1;
    } else {
      bin[pos] = 0;
    }
    valorBin = valorBin / 2;
    pos++;
  }
  String binario = String(bin[0]) + String(bin[1]) + String(bin[2]) + String(bin[3]);
  return binario;
}

void armazena(int ldrRescaled){
  melodia[cont] = ldrRescaled;
  cont++;
}