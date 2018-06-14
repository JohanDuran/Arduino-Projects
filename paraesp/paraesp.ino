#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>

// Set these to run example.
#define FIREBASE_HOST "ingplantae-8f4df.firebaseio.com"
#define FIREBASE_AUTH "7NaPpdfquRwTFkzQHo1jPiYKtaW7kdXTSHavdRey"
#define WIFI_SSID "ImagineXYZ"
#define WIFI_PASSWORD "delunoalnueve"
#define MINUTO 6000
#define SEGUNDO 1000

// Constantes para com ard-eps
const int ideps = 0;
const int sdaeps = 1;
const int scleps = 2;
int comandos[2];

int contadorCiclos;
int delete1 = 0; //variable que debe ser eliminada
int id  = 0;
int sda = 1;
int scl = 2;

i2c.setup(id, sda, scl, i2c.SLOW);

void setup() {
  Serial.begin(9600);

  // connect to wifi.
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);

  // Com ard-eps setup

  //inicia
}


void loop() {
  sendData(random(100),random(22,37),random(60,100),random(15,30),random(60,100),delete1, "datos");
  delete1++;
  delay(SEGUNDO*10);
  comandos[1] = 6;
  comandos[2] = 9;
  sendToArduino(comandos[1], comandos[2]);
}


void sendData(int nivel_agua, int temperatura, int humedad_relativa, int luz, int humedad_suelo,int timestamp, String path){
  StaticJsonBuffer<200> jsonBuffer;
  
  JsonObject& root = jsonBuffer.createObject();
  root["time"] = timestamp;
  
  JsonObject& data = root.createNestedObject("sensors_values");
  data["nivel_agua"]=nivel_agua;
  data["temperatura"]=temperatura;
  data["humedad_relativa"]=humedad_relativa;
  data["luz"]=luz;
  data["humedad_suelo"]=humedad_suelo;
  Firebase.push(path, root);
}

void sendToArduino(int command1, int command2){
  print(command1);
  delay(1000);
  
}
