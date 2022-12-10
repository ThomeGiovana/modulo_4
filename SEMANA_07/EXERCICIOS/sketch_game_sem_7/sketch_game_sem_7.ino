#include <WiFi.h>
#define ledP1vermelho 3
#define ledP1verde 15
#define ledP2vermelho 40
#define ledP2verde 0

const char* ssid = "SHARE-RESIDENTE";
const char* password = "Share@residente";
// const char *ssid = "Inteli-COLLEGE";
// const char *password = "QazWsx@123";
// const char* ssid = "Giovana's Iphone";
// const char* password = "thome123";

int p1;
int p2;
String resposta;
int vencedor;

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

void RespostaPlaquinha(int quem_venceu){
  switch (quem_venceu){
    case 0:{
      Empate();
      break;
    }
    case 1:{
      P1wins();
      Serial.println("1 venceu");
      break;
    }
    case 2:{
      P2wins();
      Serial.println("2 venceu");
      break;
    }
  }
  
}

int PedraPapelTesoura(int p1, int p2){
  // lógica da pedra papel e tesoura
  int subtracao = p1-p2;
  if (subtracao == 0){
    vencedor = 0;
    resposta = "<div class=\"resultado\"><h2>Vencedor: player " + String(vencedor) + "</h2></div>" + "<div class=\"resultado\"> <a href=\"/\"> <button type=\"button\" class=\"btn btn-secondary\">Jogar novamente</button> </a> </div>";
  } else if (subtracao == -2 || subtracao == 1){
    vencedor = 1;
    resposta = "<div class=\"resultado\"><h2>Vencedor: player " + String(vencedor) + "</h2></div>" + "<div class=\"resultado\"> <a href=\"/\"> <button type=\"button\" class=\"btn btn-secondary\">Jogar novamente</button> </a> </div>";
  } else if (subtracao == -1 || subtracao == 2){
    vencedor = 2;
    resposta = "<div class=\"resultado\"><h2>Vencedor: player " + String(vencedor) + "</h2></div>" + "<div class=\"resultado\"> <a href=\"/\"> <button type=\"button\" class=\"btn btn-secondary\">Jogar novamente</button> </a> </div>";
  }
  return vencedor;
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
            client.println(" <style> .player { text-align: center; } .resultado{ text-align: center; } .btn{ margin-top: 5px;margin-bottom: 5px; } </style>");
            client.println("</head>");

            // <body> HTML
            client.println("<body>");

            // buttons para player 1 jogar
            client.println("<div class=\"player\"> <h2>Player 1</h2> <a href=\"/player1/pedra/\"><button type=\"button\" class=\"btn btn-primary\">Pedra</button></a> <a href=\"/player1/papel/\"><button type=\"button\" class=\"btn btn-primary\">Papel</button><a> <a href=\"/player1/tesoura/\"><button type=\"button\" class=\"btn btn-primary\">Tesoura</button><a> </div>");

            // buttons para player 2 jogar
            client.println("<div class=\"player\"> <h2>Player 2</h2> <a href=\"/player2/pedra/\"><button type=\"button\" class=\"btn btn-danger\">Pedra</button></a> <a href=\"/player2/papel/\"><button type=\"button\" class=\"btn btn-danger\">Papel</button><a> <a href=\"/player2/tesoura/\"><button type=\"button\" class=\"btn btn-danger\">Tesoura</button><a> </div>");

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
            // player 2
            if (header.indexOf("GET /player2/pedra/") >= 0)
            {
              Serial.println("p2 pedra 0");
              p2 = 0;
              int vencedor = PedraPapelTesoura(p1, p2);
              client.println(resposta);
              RespostaPlaquinha(vencedor);
            }
            else if (header.indexOf("GET /player2/papel/") >= 0)
            {
              Serial.println("p2 papel 1");
              p2 = 1;
              int vencedor = PedraPapelTesoura(p1, p2);
              client.println(resposta);
              RespostaPlaquinha(vencedor);
            }
            else if (header.indexOf("GET /player2/tesoura/") >= 0)
            {
              Serial.println("p2 tesoura 2");
              p2 = 2;
              int vencedor = PedraPapelTesoura(p1, p2);
              client.println(resposta);
              RespostaPlaquinha(vencedor);
            }

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