// Código Acelerômetro

// biblioteca SparkFun (necessário instalar 'Sketch -> Include Library -> Manage Libraries... -> pesquisar SparkFun MMA8452)
#include <SparkFun_MMA8452Q.h>
// biblioteca para comunicação 
#include <Wire.h>

#define ACE_SDA  4 // jumper roxo
#define ACE_SCL  5 // jumper verde

// endereço padrão do acelerômetro
MMA8452Q acelerometro(0x1C);

void setup() {
  // inicia a comunicação das portas especificadas 
  Wire.begin(ACE_SDA, ACE_SCL);
  acelerometro.init();
  Serial.begin(115200);
}

void loop() {
  acelerometro.read();
  Serial.println(acelerometro.x);
  delay(100);
}
