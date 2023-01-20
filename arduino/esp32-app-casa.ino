#include <ArduinoJson.h>
#include <ArduinoJson.hpp>

/*Projeto de aplicativo via WEB para gerenciamento da casa*/

//Declaração das Bibliotecas (Json, wifiManager, httpclient)
#include <ArduinoJson.h>
#include <ArduinoJson.hpp>
#include <WiFiManager.h> // biblioteca do WiFiManager - já instalada
#include <HTTPClient.h>

//PINOS DE ENTRADA::  Declaração de Variáveis e pinagem
const int PortaoPeq  = 19;
const int PortaoGrd  = 21;
const int InfraSala  = 22;
const int InfraCozinha  = 23;

//PINOS DE SAÍDA::  Declaração de Variáveis e pinagem
#define LuzSala 13
#define LuzVaranda 12
#define LuzRua 27
#define LuzSuite 26

//PINOS DE entrada / RESEST DE WIFI:  Declaração de Variáveis e pinagem
const int PIN_ZeraRede  = 14;

//Declaração de Variáveis do HTTP
short int httpResponseCode;
String url;
String httpRequestData,payload;
String rota_leitura;
String PP;
String PG;
String IS;
String IC;

  // variavel de controle da lógica de verificar sinal
bool controlePP = true;
int valorLidoPP = LOW;
bool controlePG = true;
int valorLidoPG = LOW;
bool controleIS = true;
int valorLidoIS = LOW;
bool controleIC = true;
int valorLidoIC = LOW;

void setup() {
  // declara os pinos de ENTRADA
  pinMode(PortaoPeq, INPUT_PULLUP);
  pinMode(PortaoGrd, INPUT_PULLUP);
  pinMode(InfraSala, INPUT_PULLUP);
  pinMode(InfraCozinha, INPUT_PULLUP);
  PP = "OFF";
  PG = "OFF";
  IS = "OFF";
  IC = "OFF";


 // declara os pinos de SAIDA
  pinMode(LuzSala, OUTPUT);
  pinMode(LuzVaranda, OUTPUT);
  pinMode(LuzRua, OUTPUT);
  pinMode(LuzSuite, OUTPUT);
  
  // declara o pino do botão de reset de WIFI como input
  pinMode(PIN_ZeraRede, INPUT_PULLUP);


  Serial.begin(230400);
  WiFiManager wm;

valorLidoPP = digitalRead(PortaoPeq);
valorLidoPG = digitalRead(PortaoGrd);
valorLidoIS = digitalRead(InfraSala);
valorLidoIC = digitalRead(InfraCozinha);


//testa se a conexão com o wifi foi efetuada, senao, restart o ESP
  bool resposta_conexao;    
  resposta_conexao = wm.autoConnect("RedeCadWiFi","12345678"); // password protected ap

  if(!resposta_conexao) {
      Serial.println("Falha ao conectar no WI-FI");
      delay(3000);
      ESP.restart();
  } 
  else {
      //Mostra no serial que a conexão foi realizada com sucesso    
       Serial.println(" >> Conectado com sucesso no wi-fi !!!!");
  }
}

//Funçao para fazer requisição GET na rota de leitura
void Enviar(){
  
  rota_leitura = "PG="+PG; //+"&PG="+PortaoGrd+"&IS="+InfraSala+"&IC="+InfraCozinha;
  HTTPClient http;
  http.addHeader("Content-Type", "text/plain");  
  url = "http://192.168.100.9/leitura?"+rota_leitura;
  http.begin(url.c_str());
  httpResponseCode = http.POST("");
  httpRequestData = http.getString();
  delay(300);
  if (httpResponseCode > 0) {
   // Serial.print("Envio de informação do ESP: ");
    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);
    Serial.println(httpRequestData);
         
  }
  http.end();
}

//ROTA GET do servidor - leitura status geral
void GET_STATUS(){
  rota_leitura = "PP="+PP+"&PG="+PG+"&IS="+IS+"&IC="+IC; 
  HTTPClient http;
  http.addHeader("Content-Type", "text/plain");
  url = "http://192.168.100.9/leitura/status?"+rota_leitura;
  http.begin(url.c_str());
  httpResponseCode = http.GET();
  httpRequestData = http.getString();
  delay(500);
  if (httpResponseCode > 0) {
    //Serial.print("Recebeu informação do servidor ::: ");
    Serial.print("Recebido do GET_STATUS codigo: ");
    Serial.println(httpResponseCode);
    Serial.println(httpRequestData);   
  }
  http.end();
}

void loop() {
  WiFiManager wifiManager;

//Executa as funções GET

 
//Verifica o valor da entrada do sensor Portao pequeno
 if(valorLidoPP == HIGH && controlePP == true){
       digitalWrite(LuzSuite, HIGH);
       controlePP = false;
       Serial.println("Portao Pequeno >>  Aberto  << "); 
       PP = "ON";
       //delay(500);
    
      }else if(valorLidoPP == LOW && controlePP == false) {
         digitalWrite(LuzSuite, LOW);
         controlePP = true;
         Serial.println("Portao Pequeno <<  Fechado  >>");
         PP = "OFF";
        // delay(500);
      }
   valorLidoPP = digitalRead(PortaoPeq);

   //Verifica o valor da entrada do sensor Portao GRANDE
 if(valorLidoPG == HIGH && controlePG == true){
       digitalWrite(LuzSuite, HIGH);
       controlePG = false;
       Serial.println("Portao GRANDE >>  Aberto  << "); 
       PG = "ON";
      // delay(500);
    
      }else if(valorLidoPG == LOW && controlePG == false) {
         digitalWrite(LuzSuite, LOW);
         controlePG = true;
         Serial.println("Portao GRANDE << fechado >>");
         PG = "OFF";
         //delay(500);
      }
   valorLidoPG = digitalRead(PortaoGrd);

     //Verifica o valor da entrada do sensor INFRA SALA
 if(valorLidoIS == HIGH && controleIS == true){
       digitalWrite(LuzSuite, HIGH);
       controleIS = false;
       Serial.println("INFRA SALA >> ACIONADO << "); 
       IS = "ON";
       //delay(500);
    
      }else if(valorLidoIS == LOW && controleIS == false) {
         digitalWrite(LuzSuite, LOW);
         controleIS = true;
         Serial.println("INFRA SALA << Normal >> ");
         IS = "OFF";
         //delay(500);
      }
   valorLidoIS = digitalRead(InfraSala);

    //Verifica o valor da entrada do sensor INFRA Cozinha
 if(valorLidoIC == HIGH && controleIC == true){
       digitalWrite(LuzSuite, HIGH);
       controleIC = false;
       Serial.println("INFRA Cozinha >> ACIONADO << "); 
       IC = "ON";
      // delay(500);
    
      }else if(valorLidoIC == LOW && controleIC == false) {
         digitalWrite(LuzSuite, LOW);
         controleIC = true;
         Serial.println("INFRA Cozinha << Normal >> ");
         IC = "OFF";
         //delay(500);
      }
   valorLidoIC = digitalRead(InfraCozinha);

  GET_STATUS();
delay(500);

}
