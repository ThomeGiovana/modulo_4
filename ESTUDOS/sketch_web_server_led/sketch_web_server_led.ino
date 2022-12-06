/*********
  Rui Santos
  Complete project details at https://randomnerdtutorials.com  
*********/

// Load Wi-Fi library
#include <WiFi.h>

// Credenciais da rede
const char* ssid = "SHARE-RESIDENTE";
const char* password = "Share@residente";

// Porta do servidor
WiFiServer server(80);

// Variável da requisição HTTP
String header;

// Variáveis auxiliares para estados dos leds
String vermelhoState = "off";
String azulState = "off";

#define vermelhoPin 4
#define azulPin 6

// Current time
unsigned long currentTime = millis();
// Previous time
unsigned long previousTime = 0; 
// Define timeout time in milliseconds (example: 2000ms = 2s)
const long timeoutTime = 2000;

void setup() {
  Serial.begin(115200);
  pinMode(vermelhoPin, OUTPUT);
  pinMode(azulPin, OUTPUT);
  // Inicializa leds desligados
  digitalWrite(vermelhoPin, LOW);
  digitalWrite(azulPin, LOW);

  // Estabelece conexão wifi usando credenciais
  Serial.print("Conectando a ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  // Printa o endereço IP da plaquinha 
  Serial.println("");
  Serial.println("Conexão WiFi estabelecida.");
  Serial.println("Endereço IP: ");
  Serial.println(WiFi.localIP());
  // Inicia o servidor
  server.begin();
}

void loop(){
  WiFiClient client = server.available();   // Listen for incoming clients

  if (client) {                             // If a new client connects,
    currentTime = millis();
    previousTime = currentTime;
    Serial.println("Novo cliente.");          // print a message out in the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    
    while (client.connected() && currentTime - previousTime <= timeoutTime) {  // loop while the client's connected
      currentTime = millis();
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        Serial.write(c);                    // print it out the serial monitor
        header += c;
        if (c == '\n') {                    // if the byte is a newline character
          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Conexão: fechada");
            client.println();
            
            // turns the GPIOs on and off
            if (header.indexOf("GET /vermelho/on") >= 0) {
              Serial.println("GPIO vermelho on");
              vermelhoState = "on";
              digitalWrite(vermelhoPin, HIGH);
            } else if (header.indexOf("GET /vermelho/off") >= 0) {
              Serial.println("GPIO vermelho off");
              vermelhoState = "off";
              digitalWrite(vermelhoPin, LOW);
            } else if (header.indexOf("GET /azul/on") >= 0) {
              Serial.println("GPIO azul on");
              azulState = "on";
              digitalWrite(azulPin, HIGH);
            } else if (header.indexOf("GET /azul/off") >= 0) {
              Serial.println("GPIO azul off");
              azulState = "off";
              digitalWrite(azulPin, LOW);
            }
            
            // Display the HTML web page
            client.println("<!DOCTYPE html><html>");
            client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
            client.println("<link rel=\"icon\" href=\"data:,\">");
            // CSS to style the on/off buttons 
            // Feel free to change the background-color and font-size attributes to fit your preferences
            client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
            client.println(".button { background-color: #4CAF50; border: none; color: white; padding: 16px 40px;");
            client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
            client.println(".button2 {background-color: #555555;}</style></head>");
            
            // Web Page Heading
            client.println("<body><h1>ESP32 Web Server</h1>");
            
            // Display current state, and ON/OFF buttons for GPIO vermelho  
            client.println("<p>GPIO vermelho - State " + vermelhoState + "</p>");
            // If the vermelhoState is off, it displays the ON button       
            if (vermelhoState=="off") {
              client.println("<p><a href=\"/vermelho/on\"><button class=\"button\">ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/vermelho/off\"><button class=\"button button2\">OFF</button></a></p>");
            } 
               
            // Display current state, and ON/OFF buttons for GPIO azul  
            client.println("<p>GPIO azul - State " + azulState + "</p>");
            // If the azulState is off, it displays the ON button       
            if (azulState=="off") {
              client.println("<p><a href=\"/azul/on\"><button class=\"button\">ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/azul/off\"><button class=\"button button2\">OFF</button></a></p>");
            }
            client.println("</body></html>");
            
            // The HTTP response ends with another blank line
            client.println();
            // Break out of the while loop
            break;
          } else { // if you got a newline, then clear currentLine
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }
      }
    }
    // Clear the header variable
    header = "";
    // Close the connection
    client.stop();
    Serial.println("Client disconnected.");
    Serial.println("");
  }
}