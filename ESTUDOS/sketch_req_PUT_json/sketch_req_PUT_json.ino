// https://www.youtube.com/watch?v=cgoCmYLeaSI&list=PL-3SnJmahyb5mQLq7RgG6HNIUMwXzgDy-&index=8 

#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

const char* ssid = "Inteli-COLLEGE";
const char* password = "QazWsx@123";
char jsonOutput[128];

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  Serial.print ("Connecting to WiFi");
  while (WiFi.status () != WL_CONNECTED) {
    Serial.print(".");
    delay (500);
  }
  Serial.println("\nConnected to the WiFi network");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.println(WiFi.localIP());
}

void loop(){
  if((WiFi.status() == WL_CONNECTED)){ //Check the current connection

    // delay(5000); Utilizado para debug, pode ser deletado
    long rnd = random(1,10); // define qual post vamos dar o put de update 
    HTTPClient client; // define client
    client.begin("http://jsonplaceholder.typicode.com/posts/" + String(rnd));// url to make the request
    client.addHeader("Content-Type", "application/json"); // cabeçalho que especifica o tipo de conteúdo para a API

    // especifica uma capacidade estática para o json document
    const size_t CAPACITY = JSON_OBJECT_SIZE(3); // 3 itens do 
    StaticJsonDocument<CAPACITY> doc;

    // criação de um objeto json para, após, preencher o doc
    JsonObject obj = doc.to<JsonObject>();

    // especificação dos campos a serem alterados
    obj["id"] = rnd;
    obj["title"] = "Título da Giovana";
    obj["body"] = "body da Giovana";

    // serializando o json doc object
    serializeJson(doc, jsonOutput);
    Serial.println(jsonOutput); 

    int httpCode = client.PUT(String(jsonOutput)); // Status code

    if(httpCode > 0){ // Checks if there's no errors
      String payload = client.getString();// Get data!!
      Serial.println("\nStatuscode: " + String(httpCode));
      Serial.println(payload);
      client.end();
    }
    else{
      Serial.println("Error on HTTP request");
    }
  }
  else{
    Serial.println("Connection lost");
  }
  delay(10000);
}
