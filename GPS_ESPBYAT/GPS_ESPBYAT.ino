/*
  Blink
  Turns on an LED on for one second, then off for one second, repeatedly.

  Most Arduinos have an on-board LED you can control. On the UNO, MEGA and ZERO 
  it is attached to digital pin 13, on MKR1000 on pin 6. LED_BUILTIN is set to
  the correct LED pin independent of which board is used.
  If you want to know what pin the on-board LED is connected to on your Arduino model, check
  the Technical Specs of your board  at https://www.arduino.cc/en/Main/Products
  
  This example code is in the public domain.

  modified 8 May 2014
  by Scott Fitzgerald
  
  modified 2 Sep 2016
  by Arturo Guadalupi
  
  modified 8 Sep 2016
  by Colby Newman
*/
#include <SoftwareSerial.h>
#define DEBUG_ESP8266 //Comentar si no se quiere imprimir la respuesta del ESP8266
#define ESP8266_OK //Confirmar si el comando AT fue recibido
SoftwareSerial mySerial(3, 2); // RX | TX

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  Serial.begin(115200);
  mySerial.begin(38400);
  sendCmd("AT",60);
  sendCmd("AT+CWMODE=3",100);
  sendCmd("AT+CWJAP=\"AP-12805\",\"nadieselasabe\"",100);
  //sendCmd("AT+CWJAP?",100);
  //sendCmd("AT+CIPSTA?",100);
  sendCmd("AT+CIPSTART=\"TCP\",\"192.168.0.103\",8081",100);
  String url="/Proyectos/ArduinoPHPPost/phpPost/test.php?id1=12";
  String host="192.168.0.103:8081";
  String datos=String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" + 
               "Connection: keep-alive\r\n\r\n";
  //String datos="GET /Proyectos/ArduinoPHPPost/phpPost/test.php?id1=12 HTTP/1.1\r\nHost: 192.168.0.103\r\n\r\n";
  Serial.println(datos);
  sendCmd("AT+CIPSEND="+ String(datos.length()),100);
  sendCmd(datos,100);
    
}

// the loop function runs over and over again forever
void loop() {
  }


  void sendCmd (String ATcmd, int Tespera) {

#ifdef DEBUG_ESP8266
  mySerial.println(ATcmd);
  delay(10); //Tiempo a esperar para abrir el puerto mySerial
  Serial.println(leer());
#endif

#ifdef ESP8266_OK
  while (!findOK()) {
    mySerial.println(ATcmd);
    delay(Tespera); //Tiempo a esperar para abrir el puerto mySerial
  }
#endif
  delay(60);
}


String leer() {
  String recibido = "";
  while (mySerial.available()) {
    if (mySerial.available()) {
      recibido += (char)mySerial.read();
    }
    //Serial.print(recibido);
  }
  return recibido;
}

bool findOK() {                     
  if (mySerial.find("OK")){         
    Serial.println("OK");
    return true;                    
  }else{
    //Serial.println("!OK");
    return false;
    }
}
