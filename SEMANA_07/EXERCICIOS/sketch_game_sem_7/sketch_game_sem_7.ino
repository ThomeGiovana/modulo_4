#include <WiFi.h>
#define ledP1vermelho 5
#define ledP1verde 6
#define ledP2vermelho 8
#define ledP2verde 9

const char* ssid = "SHARE-RESIDENTE";
const char* password = "Share@residente";
// const char *ssid = "Inteli-COLLEGE";
// const char *password = "QazWsx@123";
// const char* ssid = "Giovana's Iphone";
// const char* password = "thome123";

WiFiServer server(80);

String header;

unsigned long currentTime = millis();
unsigned long previousTime = 0;
const long timeoutTime = 2000;

void P1wins(){
  digitalWrite(ledP1verde, HIGH);
  digitalWrite(ledP2vermelho, HIGH);
  delay(1000);
  digitalWrite(ledP1verde, LOW);
  digitalWrite(ledP2vermelho, LOW);
  delay(1000);
  digitalWrite(ledP1verde, HIGH);
  digitalWrite(ledP2vermelho, HIGH);
  delay(1000);
  digitalWrite(ledP1verde, LOW);
  digitalWrite(ledP2vermelho, LOW);
}

void P2wins(){
  digitalWrite(ledP1vermelho, HIGH);
  digitalWrite(ledP2verde, HIGH);
  delay(1000);
  digitalWrite(ledP1vermelho, LOW);
  digitalWrite(ledP2verde, LOW);
  delay(1000);
  digitalWrite(ledP1vermelho, HIGH);
  digitalWrite(ledP2verde, HIGH);
  delay(1000);
  digitalWrite(ledP1vermelho, LOW);
  digitalWrite(ledP2verde, LOW);
}

void Empate(){
  digitalWrite(ledP1verde, HIGH);
  digitalWrite(ledP1vermelho, HIGH);
  digitalWrite(ledP2verde, HIGH);
  digitalWrite(ledP2vermelho, HIGH);
  delay(1000);
  digitalWrite(ledP1verde, LOW);
  digitalWrite(ledP1vermelho, LOW);
  digitalWrite(ledP2verde, LOW);
  digitalWrite(ledP2vermelho, LOW);
  delay(1000);
  digitalWrite(ledP1verde, HIGH);
  digitalWrite(ledP1vermelho, HIGH);
  digitalWrite(ledP2verde, HIGH);
  digitalWrite(ledP2vermelho, HIGH);
  delay(1000);
  digitalWrite(ledP1verde, LOW);
  digitalWrite(ledP1vermelho, LOW);
  digitalWrite(ledP2verde, LOW);
  digitalWrite(ledP2vermelho, LOW);
}

void setup()
{
  pinMode(ledP1verde, OUTPUT);
  pinMode(ledP1vermelho, OUTPUT);
  pinMode(ledP2verde, OUTPUT);
  pinMode(ledP2vermelho, OUTPUT);

  Serial.begin(115200);
  // Estabelece conexão wifi usando credenciais
  Serial.print("Conectando a ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
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

void loop()
{
  WiFiClient client = server.available();

  if (client)
  {
    currentTime = millis();
    previousTime = currentTime;
    Serial.println("Novo cliente.");
    String currentLine = "";

    while (client.connected() && currentTime - previousTime <= timeoutTime)
    {
      currentTime = millis();
      if (client.available())
      {
        char c = client.read();
        Serial.write(c);
        header += c;
        if (c == '\n')
        {
          if (currentLine.length() == 0)
          {
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Conexão: fechada");
            client.println();

            // <head> HTML
            client.println("<!DOCTYPE html><html>");
            client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
            client.println("<link rel=\"icon\" href=\"data:,\">");
            client.println("<link href=\"https://cdn.jsdelivr.net/npm/bootstrap@5.1.3/dist/css/bootstrap.min.css\" rel=\"stylesheet\" integrity=\"sha384-1BmE4kWBq78iYhFldvKuhfTAU6auU8tT94WrHftjDbrCEXSU1oBoqyl2QvZ6jIW3\" crossorigin=\"anonymous\">");
            client.println(" <style> .player { text-align: center; } .resultado{ text-align: center; } </style>");
            client.println("</head>");

            // <body> HTML
            client.println("<body>");
            client.println("<h1>Teste servidor</h1>");
            client.println("<p>Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum.</p>");

            int p1 = -1;

            // opções para player 1
            client.println("<a href=\"/player1/pedra/\"><button type=\"button\" class=\"btn btn-primary\">Pedra</button></a>");
            client.println("<a href=\"/player1/papel/\"><button type=\"button\" class=\"btn btn-primary\">Papel</button><a>");
            client.println("<a href=\"/player1/tesoura/\"><button type=\"button\" class=\"btn btn-primary\">Tesoura</button><a>");

            // player 1
            if (header.indexOf("GET /player1/pedra/") >= 0)
            {
              Serial.println("p1 pedra 0");
              p1 = 0;
            }
            else if (header.indexOf("GET /player1/papel/") >= 0)
            {
              Serial.println("p1 papel 1");
              p1 = 1;
            }
            else if (header.indexOf("GET /player1/tesoura/") >= 0)
            {
              Serial.println("p1 tesoura 2");
              p1 = 2;
            }

            // se player 1 jogou, opções para player 2 aparecem
            if (p1>-1){
              client.println("<a href=\"/player2/pedra/\"><button type=\"button\" class=\"btn btn-primary\">Pedra</button></a>");
              client.println("<a href=\"/player2/papel/\"><button type=\"button\" class=\"btn btn-primary\">Papel</button><a>");
              client.println("<a href=\"/player2/tesoura/\"><button type=\"button\" class=\"btn btn-primary\">Tesoura</button><a>");
            }

            // player 2
            int p2 = -1;
            if (header.indexOf("GET /player2/pedra/") >= 0)
            {
              Serial.println("p2 pedra 0");
              p2 = 0;
            }
            else if (header.indexOf("GET /player2/papel/") >= 0)
            {
              Serial.println("p2 papel 1");
              p2 = 1;
            }
            else if (header.indexOf("GET /player2/tesoura/") >= 0)
            {
              Serial.println("p2 tesoura 2");
              p2 = 2;
            }

            // lógica da pedra papel e tesoura
            int subtracao = p1-p2;
            String vencedor = "";
            if (subtracao == 0){
              vencedor = "Empate!";
              Empate();
            } else if (subtracao == -2 || subtracao == 1){
              vencedor = "Player 1 venceu!";
              P1wins();
            } else if (subtracao == -1 || subtracao == 2){
              vencedor = "Player 2 venceu!";
              P2wins();
            }

            client.print("<div class=\"resultado\"><p>");
            client.print(vencedor);
            client.println("</p></div>");

            // final da página 
            client.println("</body>");
            client.println("</html>");

            client.println();
            break;
          }
          else
          {
            currentLine = "";
          }
        }
        else if (c != '\r')
        {
          currentLine += c;
        }
      }
    }
    header = "";
    client.stop();
    Serial.println("Client disconnected.");
    Serial.println("");
  }
}