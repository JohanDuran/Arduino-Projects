/*
   El ESP8266 debe estar pre-configurado a 115200 Baudios
   Conectar el ESP8266 de acuerdo al diagrama UNO_ESP_JSON
*/

#include <SoftwareSerial.h>
//para el sensor ultrasonico
#define trigPin 13
#define echoPin 12
SoftwareSerial mySerial(3, 2); //Pines: RX conectado a D3, TX conectado a D2

//
//#define DEBUG_ESP8266 //Comentar si no se quiere imprimir la respuesta del ESP8266
#define ESP8266_OK //Confirmar si el comando AT fue recibido


#define SSID   "AP-12805"
#define PASS   "nadieselasabe"

String server = "AT+CIPSTART=\"TCP\",\"192.168.0.107\",80";  //Direccion del servidor al que se envían los datos
String JSON = "GET /Proyectos/Web-Projects-Generals/ArduinoPHPPost/phpPost/test.php?a=125&b=26 HTTP/1.1\r\nHost: 192.168.0.107:80\r\n\r\n\r\n\r\n"; //Header post/JSON
String trama; // Almacena el comando AT que envía el largo del dato a enviarse al servidor

//-----------------------------------------------------------------------------------------------------------------
void setup() {

  Serial.begin(9600);             // Inicializacion del Monitor Serial a 115200
  mySerial.begin(9600);           // Inicializacion  puerto serial virtual
  Serial.println("Manejo Modulo ESP8266 con Arduino UNO");// Mensaje de inicialización

  //para el sensor ultrasonico
  pinMode(trigPin, OUTPUT);//configuración de pines
  pinMode(echoPin, INPUT);//configuración de pines
  
  //*********************Pruebas iniciales**************************
  Serial.println("AT");
  SendCmd("AT", 60);
  Serial.println("ATE1");
  SendCmd("ATE1", 60); //ATE1: Habilita replica/echo del cmd enviado
  Serial.println("ATE0");
  SendCmd("ATE0",60); //ATE0: Deshabilita replica/echo del cmd enviado
  Serial.println("AT+UART");
  SendCmd("AT+UART=9600,8,1,0,0", 60);

  conectarWIFI();                 // Función para conectar el módulo ESP8266 a la red WiFi selecccionada
  delay(20);
}

void loop() {
  //******************Toma de datos***********************************
  //int sensorValue = analogRead(A0);

  //Serial.println(distance);
  delay(100);
  //*****************Conexión con el servidor*************************
  //String datos = "{\"id1\":\"12\"}";
  //String temp = JSON;
  //JSON = JSON + String(datos.length()) + "\r\n\r\n" + datos;
  Serial.println(JSON);
  trama = "AT+CIPSEND=" + String(JSON.length());
  Serial.println(trama);
  SendCmd(server, 60);
  mySerial.println(trama);
  delay(100);
  String views = sendData(JSON, 2000, 2);
  //mySerial.println(JSON);
  
  //JSON = temp;
  resetESP();
  delay(5000);
}


//****************************************** FUNCIONES****************************************************************//

void conectarWIFI() {       // Función que permite conectarse al servidor específicado en el string server
  Serial.println("AT+CWMODE");
  SendCmd("AT+CWMODE=3", 60);
  Serial.println("AP");
  String AP = "AT+CWJAP=\""; AP += SSID; AP += "\",\""; AP += PASS; AP += "\""; // Comando AT para la conexión WiFi seleccionada con el SSID y PASS
  SendCmd(AP, 60);
  Serial.println("AT");
  SendCmd("AT", 60);
}

void resetESP() {
  Serial.println("RST");
  mySerial.println("AT+RST");        // Deshabilita el echo de los comandos enviados
  delay(20);
  conectarWIFI();                 // Función para conectar el módulo ESP8266 a la red WiFi selecccionada
}

void leer() {
  while (mySerial.available()) {
    String recibido = "";
    if (mySerial.available()) {
      recibido += (char)mySerial.read();
    }
    Serial.print(recibido);
  }
}

bool findOK() {                     //Función que permite verificar el resultado "OK" del comando AT 
  if (mySerial.find("OK"))         // Si se localiza OK en la respuesta del ESP8266
  {
    Serial.println("OK");
    return true;                    // Devuelve "True"
  }
  else
  {
    //Serial.println("!OK");
    return false;                   // Retorna "False"
  }
}

void SendCmd (String ATcmd, int Tespera) {

#ifdef DEBUG_ESP8266
  mySerial.println(ATcmd);
  delay(10); //Tiempo a esperar para abrir el puerto mySerial
  leer();
#endif

#ifdef ESP8266_OK
  while (!findOK()) {
    mySerial.println(ATcmd);
    delay(Tespera); //Tiempo a esperar para abrir el puerto mySerial
  }
#endif
  delay(60);
}



String sendData(String command, const int Goldout, boolean debug)
{
  String response = "";

  mySerial.print(command); // send the read character to the Serial1

  long int Gold = millis();

  while ( (Gold + Goldout) > millis())
  {
    while (mySerial.available())
    {

      // The esp has data so display its output to the serial window
      char c = mySerial.read(); // read the next character.
      response += c;
    }
  }

  if (debug)
  {
    Serial.print(response);
  }

  return response;
}


