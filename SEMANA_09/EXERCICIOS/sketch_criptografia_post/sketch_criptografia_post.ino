#include <String.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

// Credenciais da internet
// const char* ssid = "Inteli-COLLEGE";
// const char* password = "QazWsx@123";
const char* ssid = "Inteli-welcome";
// Variável que armazena o objeto json que vai ser postado na API
char jsonOutput[128];

void postToServer(String frase, String fraseCriptografada){
  Serial.println("Posting JSON data to server...");
  // Block until we are able to connect to the WiFi access point
  HTTPClient http;   
     
    http.begin("https://ur524n-3000.preview.csb.app/teobaldo");  
    http.addHeader("Content-Type", "application/json");         
     
    StaticJsonDocument<200> doc;
    // Add values in the document
    doc["nome"] = "Giovana Thomé";
    doc["turma"] = 3;
    doc["grupo"] = 4;
    doc["mensagem"] = frase;
    doc["mensagem_criptografada"] = fraseCriptografada;
   
    String requestBody;
    serializeJson(doc, requestBody);
     
    int httpResponseCode = http.POST(requestBody);
 
    if(httpResponseCode>0){
       
      String response = http.getString();                       
       
      Serial.println(httpResponseCode);   
      Serial.println(response);
     
    }
}

void criptografia(String frase){
  int i = 0;
  // int size = frase.length();
  // String fraseCriptografada[size];
  String fraseCriptografada = frase;

  for (i=0; i<=frase.length(); i++){
    char letra = frase[i];

    switch (letra) {
      case 'z':{
        fraseCriptografada[i] = 'p';
        break;
      }
      case 'e':{
        fraseCriptografada[i] = 'o';
        break;
      }
      case 'n':{
        fraseCriptografada[i] = 'l';
        break;
      }
      case 'i':{
        fraseCriptografada[i] = 'a';
        break;
      }
      case 't':{
        fraseCriptografada[i] = 'r';
        break;
      }
      case 'p':{
        fraseCriptografada[i] = 'z';
        break;
      }
      case 'o':{
        fraseCriptografada[i] = 'e';
        break;
      }
      case 'l':{
        fraseCriptografada[i] = 'n';
        break;
      }
      case 'a':{
        fraseCriptografada[i] = 'i';
        break;
      }
      case 'r':{
        fraseCriptografada[i] = 't';
        break;
      }
    }
  }

  // Print da frase criptografada
  Serial.println("Frase anterior:");
  Serial.println(frase);
  Serial.println("Frase criptografada:");
  Serial.println(fraseCriptografada);

  // Posta no servidor
  postToServer(frase, fraseCriptografada);
}

void setup() {
  Serial.begin(115200);

  // Conexão com internet 
  WiFi.begin(ssid);
  Serial.print("Conectando à rede WiFi...");
  while( WiFi.status() != WL_CONNECTED ){
    Serial.print(".");
    delay(500);
  }
  Serial.println("\nConexão WiFi estabelecida!");
  Serial.print("Endereço IP: ");
  Serial.println(WiFi.localIP());

  // Criptografia
  String minhaFrase = "estou codando zenit polar";
  criptografia(minhaFrase);
}

void loop() {

}
