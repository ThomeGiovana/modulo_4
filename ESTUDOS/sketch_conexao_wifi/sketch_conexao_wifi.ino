#include <WiFi.h>;

const char* ssid = "SHARE-RESIDENTE";
const char* password = "Share@residente";

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  Serial.print("Connectando a wifi");
  // Laço de repetição que verifica a conexão com a internet
  while(WiFi.status() != WL_CONNECTED){
    Serial.print(".");
    delay(500);
  }
  // Quando a conexão é estabelecida
  Serial.println("\nConectado à rede WiFi!");
  Serial.print("Endereço de IP da plaquinha: ");
  // Endereço de IP local que vamos pingar
  Serial.println(WiFi.localIP());
}

void loop() {
  // Checa de novo a conexão com a internet 
  if (WiFi.status() == WL_CONNECTED){
    Serial.println("Você pode tenar me pingar");
    delay(5000);
  }
  else {
    Serial.println("Conexão perdida");
  }
}

/*
  Agora, a plaquinha ESP32 pode ficar conectada apenas na fonte de alimentação.
  Em algum computador, abrir o prompt de comando e pingar o endereço de IP da plaquinha com o comando:
  ping <endereçoIP>
*/
