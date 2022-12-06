#include <ArduinoJson.h>
#include <HTTPClient.h>
#include <WiFi.h>

//Vetores com nomes de rede e senhas dos Access Points
const char* SSIDS[4]={"Inteli-COLLEGE","baconzitos1","baconzitos2","baconzitos3"};
const char* PWD[4]={"QazWsx@123","baconzitos1","baconzitos2","baconzitos3"};
//Variável que continua ou não o MENU 2
int parar=0;
//Variável para medir a distância
int distancia[3]={0,0,0};
int indice=0;
// Definições para o FTM
// Number of FTM frames requested in terms of 4 or 8 bursts (allowed values - 0 (No pref), 16, 24, 32, 64)
const uint8_t FTM_FRAME_COUNT = 16;
// Requested time period between consecutive FTM bursts in 100’s of milliseconds (allowed values - 0 (No pref) or 2-255)
const uint16_t FTM_BURST_PERIOD = 2;
// Semaphore to signal when FTM Report has been received
xSemaphoreHandle ftmSemaphore;
// Status of the received FTM Report
bool ftmSuccess = true;
/*void Triangulacao{
  
}*/
void postDataToServer() {
 
  Serial.println("Posting JSON data to server...");
  // Block until we are able to connect to the WiFi access point
  HTTPClient http;   
     
    http.begin("https://ur524n-3000.preview.csb.app/teobaldo");  
    http.addHeader("Content-Type", "application/json");         
     
    StaticJsonDocument<200> doc;
    // Add values in the document
    //
    doc["sensor"] = "gps";
    doc["time"] = 1351824120;
   
    // Add an array.
    //
    JsonArray data = doc.createNestedArray("data");
    for(int i=0; i<3; i++)
    {
      data.add(distancia[i]);
    }
     
    String requestBody;
    serializeJson(doc, requestBody);
     
    int httpResponseCode = http.POST(requestBody);
 
    if(httpResponseCode>0){
       
      String response = http.getString();                       
       
      Serial.println(httpResponseCode);   
      Serial.println(response);
     
    }
    else {
     
      //Serial.printf("Error occurred while sending HTTP POST: %s\n", httpClient.errorToString(statusCode).c_str());
       
    }
     
}
//Uma função para ler todos os dados da conexão WiFi
void DadosConexao(){
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.println("Subnet Mask: ");
  Serial.println(WiFi.subnetMask());
  Serial.println("Gateway IP: ");
  Serial.println(WiFi.gatewayIP());
  Serial.println("DNS IP: ");
  Serial.println(WiFi.dnsIP());
  Serial.println("BroadCast: ");
  Serial.println(WiFi.broadcastIP());
  Serial.println("MAC address: ");
  Serial.println(WiFi.macAddress());
  Serial.println("Network ID: ");
  Serial.println(WiFi.networkID());
  Serial.println("PSK: ");
  Serial.println(WiFi.psk());
  Serial.println("BSSID: ");
  Serial.println(WiFi.BSSIDstr());
  Serial.println("RSSI: ");
  Serial.println(WiFi.RSSI());
}
// FTM report handler with the calculated data from the round trip
void onFtmReport(arduino_event_t *event) {
  const char * status_str[5] = {"SUCCESS", "UNSUPPORTED", "CONF_REJECTED", "NO_RESPONSE", "FAIL"};
  wifi_event_ftm_report_t * report = &event->event_info.wifi_ftm_report;
  // Set the global report status
  ftmSuccess = report->status == FTM_STATUS_SUCCESS;
  if (ftmSuccess) {
    // The estimated distance in meters may vary depending on some factors (see README file)
    distancia[indice]=report->dist_est;
    Serial.printf("FTM Estimate: Distance RAW: %.4f,Distance: %.4f m, Return Time: %u ns\n", (float)report->dist_est, (float)(report->dist_est-4000) / 10000, report->rtt_est);
    // Pointer to FTM Report with multiple entries, should be freed after use
    //free(report->ftm_report_data);
  } else {
    Serial.print("FTM Error: ");
    Serial.println(status_str[report->status]);
  }
  // Signal that report is received
  xSemaphoreGive(ftmSemaphore);
}
// Initiate FTM Session and wait for FTM Report
bool getFtmReport(){
  if(!WiFi.initiateFTM(FTM_FRAME_COUNT, FTM_BURST_PERIOD)){
    Serial.println("FTM Error: Initiate Session Failed");
    return false;
  }
  // Wait for signal that report is received and return true if status was success
  return xSemaphoreTake(ftmSemaphore, portMAX_DELAY) == pdPASS && ftmSuccess;
}
//Função para um Menu de escolha cujo intuito é mostrar todas as possibilidades do Wifi.
//Conectar separadamente nos APs e depois fazer a triangulação
int menu()
{
  Serial.println(F("\nEscolha uma opção:"));
  Serial.println(F("0 - Scan de redes"));
  Serial.println(F("1 - Conectar no beacon 1\n"));
  Serial.println(F("2 - Conectar no beacon 2\n"));
  Serial.println(F("3 - Conectar no beacon 3\n"));
  Serial.println(F("4 - Conectar nos 3 beacons (sequencialmente) \n"));
  Serial.println(F("5 - Conectar no WIFI e enviar dados para o servidor.  \n"));
  //fica aguardando enquanto o usuário nao enviar algum dado
  while(!Serial.available()){};
  //recupera a opção escolhida
  int op = (int)Serial.read();
  //remove os proximos dados (como o 'enter ou \n' por exemplo) que vão por acidente
  while(Serial.available()) {
    if(Serial.read() == '\n') break; 
    Serial.read();
  }
  return (op-48);//do valor lido, subtraimos o 48 que é o ZERO da tabela ascii
}
//Utilizado na função CONECTAR, para continuar mostrando os dados da conexão enquanto permanecer
//conectado. 
int menu2()
{
  Serial.println(F("\nEscolha uma opção 2:"));
  //fica aguardando enquanto o usuário nao enviar algum dado
  while(!Serial.available()){};
  //recupera a opção escolhida
  int op = (int)Serial.read();
  //remove os proximos dados (como o 'enter ou \n' por exemplo) que vão por acidente
  while(Serial.available()) {
    if(Serial.read() == '\n') break; 
    Serial.read();
  }
  return (op-48);//do valor lido, subtraimos o 48 que é o ZERO da tabela ascii
}
//Função para conectar em APs sem medição FTM
void Conectar(int rede)
{
  Serial.println("Conectando na rede: ");
  Serial.println(rede);
  WiFi.begin(SSIDS[rede],PWD[rede]);
      while (WiFi.status() != WL_CONNECTED) {
        Serial.print("Tentando novamente!");
        delay(500);
      }
      while(parar==0)
      {
        Serial.println("WiFi connected");
        //DadosConexao();
        postDataToServer();      
        parar = menu2();
      }
      parar=0;
      WiFi.disconnect();
      Serial.println("Desconectei!");
}
//Função para conectar num AP sem medição FTM. Futuramente para conectar na internet e enviar 
//os dados dos sensores
void MedirDistancia(int rede){
  // Create binary semaphore (initialized taken and can be taken/given from any thread/ISR)
  ftmSemaphore = xSemaphoreCreateBinary();
  
  // Listen for FTM Report events
  WiFi.onEvent(onFtmReport, ARDUINO_EVENT_WIFI_FTM_REPORT);
  
  // Connect to AP that has FTM Enabled
  Serial.println("Connecting to FTM Responder");
  WiFi.begin(SSIDS[rede], PWD[rede]);
  while (WiFi.status() != WL_CONNECTED) {
    delay(2000);
    Serial.print(".");
    WiFi.disconnect();
    delay(2000);
    WiFi.reconnect();
    delay(2000); 
  }
  Serial.println("");
  Serial.println("WiFi Connected");
  Serial.print("Initiating FTM session with Frame Count ");
  Serial.print(FTM_FRAME_COUNT);
  Serial.print(" and Burst Period ");
  Serial.print(FTM_BURST_PERIOD * 100);
  Serial.println(" ms");
  getFtmReport();
}

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA); 
}

void loop() {
  int opcao = menu();
  switch(opcao)
  {
    case 0:
    {
      Serial.println("Escaneando redes!");
      int n = WiFi.scanNetworks();
      Serial.println("scan done");
      if (n == 0) {
          Serial.println("no networks found");
      } 
      else {
        Serial.print(n);
        Serial.println(" networks found");
        for (int i = 0; i < n; ++i) {
          // Print SSID and RSSI for each network found
          Serial.print(i + 1);
          Serial.print(": ");
          Serial.print(WiFi.SSID(i));
          Serial.print(" (");
          Serial.print(WiFi.RSSI(i));
          Serial.print(")");
          Serial.println((WiFi.encryptionType(i) == WIFI_AUTH_OPEN)?" ":"*");
          delay(10);
        }
      }
      break;
    }
    case 1:
      Serial.println("Conectando no beacon 1!");
      //Conectar(0);
      indice=0;
      MedirDistancia(1);
      break;
    case 2:
      Serial.println("Conectando no beacon 2!");
      //Conectar(2);
      indice=1;
      MedirDistancia(2);
      break;
    case 3:
      Serial.println("Conectando no beacon 3!");
      //Conectar(3);
      //WiFi.disconnect();
      indice=2;
      MedirDistancia(3);
      break;
    case 4:
      Serial.println("Rotação de beacons!");
      for(int i=1; i<4;i++)
      {
        indice=i-1;
        MedirDistancia(i);
      }
      break;
    case 5:
      Serial.println("Conectar na internet e enviar dados para o servidor!");
      Conectar(0);
      break;
    default:
      Serial.println("Opção fora do padrão!");
      break;
  }
  Serial.println("Distancias:");
  for(int i=0;i<3;i++)
  {
    Serial.println(distancia[i]);
  }
   

}
