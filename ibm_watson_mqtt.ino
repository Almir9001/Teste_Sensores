//Verifica qual ESP está sendo utilizado, e importa a lib e wifi correspondente
//#if defined(ESP8266)
//#include <ESP8266WiFi.h>        
//#else
#include <WiFi.h>
//#endif
 
//Lib de MQTT
#include <PubSubClient.h>

//-------------------------------------------------------------------

//Intervalo entre os envios
#define INTERVAL 1000

//pino ligado ao sensor de temperatura
#define sensorPin 25
 
//Substitua pelo SSID da sua rede
#define SSID "LIVE TIM_E82B_2G"
 
//Substitua pela senha da sua rede
#define PASSWORD "h4aenenv8g"
 
//Server MQTT que iremos utlizar
#define MQTT_SERVER "quickstart.messaging.internetofthings.ibmcloud.com"
 
//Nome do tópico que devemos enviar os dados
//para que eles apareçam nos gráficos
#define TOPIC_NAME "iot-2/evt/status/fmt/json"
 
//ID que usaremos para conectar 
//QUICK_START deve permanecer como está
//const String QUICK_START = "d:dq8kfb";
const String QUICK_START = "d:quickstart:arduino:";


//--------------------------------------------------------------------


//No DEVICE_ID você deve mudar para um id único
//Aqui nesse exemplo utilizamos o MAC Address
//do dispositivo que estamos utilizando
//Servirá como identificação no site
//https://quickstart.internetofthings.ibmcloud.com
const String DEVICE_ID = "data_corp_2000";

 
//Concatemos o id do quickstart com o id do nosso dispositivo
const String CLIENT_ID =  QUICK_START + DEVICE_ID;

//Cliente WiFi que o MQTT irá utilizar para se conectar
WiFiClient wifiClient;

//Cliente MQTT, passamos a url do server, a porta e o cliente WiFi
PubSubClient client(MQTT_SERVER, 1883, wifiClient);

//Tempo em que o último envio foi feito
long lastPublishTime = 0;

//Variável para guardarmos o valor da temperatura
float temperatura = 0;

//-------------------------------------------------

void setup() 
{
  Serial.begin(115200);
  //Conectamos à rede WiFi
  setupWiFi();
  //Conectamos ao server MQTT
  connectMQTTServer();
}

//-------------------------------------------------

void loop()  
{
   
  //captura o tempo através da funçãp millis, para exibir a hora
  long now = millis();
 
  //Se o tempo desde o último envio for maior que o intervalo de envio
  if (now - lastPublishTime > INTERVAL) {
    //Atualizamos o tempo em que ocorreu o último envio
    lastPublishTime = now;
    
    //Fazemos a leitura da temperatura
    //readSensor();
    Serial.print("Publish mensagem: ");
    
    //Criamos o json que enviaremos para o server mqtt
    String msg = createJsonString();
    Serial.println(msg);
    
    //Publicamos no tópico onde o servidor espera para receber e gerar o gráfico
    client.publish(TOPIC_NAME, msg.c_str());
  }
}

//-----------------------------------------------------------

void setupWiFi() 
{
  Serial.println();
  Serial.print("Conectando a rede: ");
  Serial.print(SSID);

  //Manda o esp se conectar à rede através do ssid e senha
  WiFi.begin(SSID, PASSWORD);
 
  //Espera até que a conexão com a rede seja estabelecida
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");  // imprime estes pontinhos enquando está tentando se conectar
  }
 
  //Se chegou aqui é porque conectou
  Serial.println("");
  Serial.println("WiFi conectado com sucesso");
}

//-------------------------------------------------------------

//Função responsável por conectar ao server MQTT
void connectMQTTServer() 
{
  Serial.println("Conectando ao MQTT Server...");
  //Se conecta ao id que definimos
  if (client.connect(CLIENT_ID.c_str()) ) {
    //Se a conexão foi bem sucedida
    Serial.println("MQTT conectado com sucesso");
  } else {
    //Se ocorreu algum erro
    Serial.print("Erro ao conectar ao MQTT = ");
    Serial.println(client.state());
  }
} 

//--------------------------------------------------------------

//Função responsável por realizar a leitura de temperatura
void readSensor()
{
   
//      temperatura = analogRead(sensorPin);
//      temperatura = temperatura * (3.3 / 4092);

  int sensorValue = analogRead(sensorPin);
  // print out the value you read:
  Serial.println(sensorValue);
  delay(500);        // delay in between reads for stability
      
      
}

//---------------------------------------------------------------

//Função responsável por criar um Json com os dados lidos do sensor

String createJsonString() 
{
  String data = "{";    
      data+= "\"d\": {";
      data+="\"temperatura\":";
      data+=String(temperatura);
      data+=",";
      data+="}";
      data+="}";
  return data;
}

//-----------------------------------
