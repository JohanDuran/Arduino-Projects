#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>

// Set these to run example.
#define FIREBASE_HOST "ingplantae-8f4df.firebaseio.com"
#define FIREBASE_AUTH "7NaPpdfquRwTFkzQHo1jPiYKtaW7kdXTSHavdRey"
#define WIFI_SSID "jaja"
#define WIFI_PASSWORD "12345678"
#define MINUTO 6000
#define SEGUNDO 1000

int stamp = 0;

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
}

//sendData(random(100),random(22,37),random(60,100),random(15,30),random(60,100),stamp, "datos");

void loop() {
  getData();
  /*Codigo para el MEGA*/
  int sensorsValues[5]={1,2,3,4,5};//Este debe ser reemplazado por el arreglo de sensores de chico
  String valuesToSend=concatenateData(sensorsValues[0],sensorsValues[1],sensorsValues[2],sensorsValues[3],sensorsValues[4]);
  /*Acá se debe enviar hacía el ESP*/
  
  /*Codigo para el ESP*/
  String datos = "1,2,3,4,5,"; 
  //IMPORTANTE datos son los valores leídos que vienen de MEGA
  //uploadData(datos, stamp,"datos");
  stamp++;
  delay(SEGUNDO*10);
}


String getData(){
  FirebaseObject payload=Firebase.get("Alarms"); 
  //StaticJsonBuffer<200> buf;
  Serial.println(payload.json());
  //JsonObject& data = buf.parseObject(payload);
  //Serial.println(data);  

}



/*Funciones del lado del ESP*/

//recibe el string que viene por serial y retorna un arreglo con los valores de los sensores.
void uploadData(String data, int stamp, String path){
  int values[5];
  int currentIndex = 0;
  int nextIndex = 0;
  //String fecha;
  int index=0;
  for (int i = 0; i < data.length(); i++) {
    if (data.substring(i, i+1) == ",") {
      values[index] = data.substring(currentIndex, i).toInt();
      Serial.println(values[index]);
      index++;
      currentIndex = i+1;
    }
  }
  //sendData(values[0],values[1],values[2],values[3],values[4], stamp, path);
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

/*--------------------------------------------------------------------------------------------*/

/*Funciones del lado del MEGA*/
//Concatenar los valores el el string con este formato nivel_agua, temperatura, humedad_relativa, luz, humedad_suelo
//No manejar fecha para este caso aún
String concatenateData(int nivel_agua, int temperatura, int humedad_relativa, int luz, int humedad_suelo){
  return String(nivel_agua)+","+String(temperatura)+","+String(humedad_relativa)+","+String(luz)+","+String(humedad_suelo)+",";
}
