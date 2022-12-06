// https://www.youtube.com/watch?v=cgoCmYLeaSI&list=PL-3SnJmahyb5mQLq7RgG6HNIUMwXzgDy-&index=8 

#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

const char* ssid = "Inteli-COLLEGE";
const char* password = "QazWsx@123";

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

    int httpCode = client.GET(); // Essa variável não contém o objeto Json, contém o código do status da requisição 

    if (httpCode > 0){
      String payload = client.getString(); // Método get que pega o Json no formato string
      Serial.println("\nStatuscode: " + String(httpCode));    // Printa o código de status da requisição
      Serial.println(payload);

      // Cria o vetor json
      char json[500];
      // remove espaços e quebras de linha
      payload.replace(" ", "");
      payload.replace("\n", "");
      payload.trim();   // Remove todos os espaços em branco à esquerda e à direita da cadeia de caracteres
      payload.remove(0,1);
      // Transforma o json string em um array 
      payload.toCharArray(json, 500);
      Serial.println("json: ");
      Serial.println(json);
      
      // Cria um arquivo estático 
      StaticJsonDocument<200> doc;
      // Descerealiza o documento 
      deserializeJson(doc, json);
      // Serial.println("doc: ");
      // Serial.println(String(doc));

      // Acessa os dados do doc e printa
      int id = doc["id"];
      const char* email = doc["email"];
      Serial.println(String(id) + " - " + String(email) + "\n");

      client.end();

    } else {
      // Serial.println("\nStatuscode: " + String(httpCode));
      Serial.println("Requisição não completada");
    }
    delay(10000);    
  }
}



#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
const char* ssid = "Inteli-COLLEGE";
const char* password = "QazWsx@123";
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
    // Serial.println("You can try to ping me");
    // delay(5000); Utilizado para debug, pode ser deletado
    long rnd = random(1,10); // random variable
    HTTPClient client; // define client
    client.begin("http://jsonplaceholder.typicode.com/comments?id=" + String(rnd));// url to make the request
    int httpCode = client.GET(); // Status code
    if(httpCode > 0){ // Checks if there's no errors
      String payload = client.getString();// Get data!!
      Serial.println("\nStatuscode: " + String(httpCode));
      Serial.println(payload);
      //Deserialize the data
      char json[500];
      payload.replace(" ", "");
      payload.replace("\n", "");
      payload.trim();
      payload.remove(0,1);
      payload.toCharArray(json,500);
      // Create a static json document
      StaticJsonDocument<200> doc;
      deserializeJson(doc, json);
      // Get some data from doc
      int id = doc["id"];
      const char* email = doc["email"];
      Serial.println(String(id) + " - " + String(email) + "\n");
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