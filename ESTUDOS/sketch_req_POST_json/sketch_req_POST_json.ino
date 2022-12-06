// https://www.youtube.com/watch?v=cgoCmYLeaSI&list=PL-3SnJmahyb5mQLq7RgG6HNIUMwXzgDy-&index=8 

#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

const char* ssid = "Inteli-COLLEGE";
const char* password = "QazWsx@123";
// Variável que armazena o objeto json que vai ser postado na API
char jsonOutput[128];

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  Serial.print("Conectando à rede WiFi...");

  while( WiFi.status() != WL_CONNECTED ){
    Serial.print(".");
    delay(500);
  }

  Serial.println("\nConexão WiFi estabelecida!");
  Serial.print("Endereço IP: ");
  Serial.println(WiFi.localIP());

}

void loop() {
  if( WiFi.status() == WL_CONNECTED ){
    HTTPClient client;

    // Especifica a URL e faz a requisição
    client.begin("https://jsonplaceholder.typicode.com/posts");
    client.addHeader("Content-Type", "application/json");

    // Especifica uma capacidade fixa para o JSON document
    const size_t CAPACITY = JSON_OBJECT_SIZE(1);
    StaticJsonDocument<CAPACITY> doc;

    // O JSON document está vazio, então precisamos mudá-lo
    // Add nested items to your doc object
    JsonObject object = doc.to<JsonObject>();
    object["title"] = "Giovana Thomé";

    serializeJson(doc, jsonOutput);

    int httpCode = client.POST(String(jsonOutput));

    if (httpCode > 0){
      String payload = client.getString(); 
      Serial.println("\nStatuscode: " + String(httpCode));    // Printa o código de status da requisição
      Serial.println(payload);

      client.end();

    } else {
      // Serial.println("\nStatuscode: " + String(httpCode));
      Serial.println("Requisição não completada");
    }
    delay(10000);    
  }
}
