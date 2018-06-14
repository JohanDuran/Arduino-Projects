/**************************************************************
 *
 * This sketch connects to a website and downloads a page.
 * It can be used to perform HTTP/RESTful API calls.
 *
 * For this example, you need to install ArduinoHttpClient library:
 *   https://github.com/arduino-libraries/ArduinoHttpClient
 *   or from http://librarymanager/all#ArduinoHttpClient
 *
 * TinyGSM Getting Started guide:
 *   http://tiny.cc/tiny-gsm-readme
 *
 **************************************************************/
//Flag for DEBUG
#define DEBUG
#ifdef DEBUG
 #define DEBUG_PRINT(textToOut) Serial.println(textToOut)
#else
 #define DEBUG_PRINT(x)
#endif



// Select your modem:
#define TINY_GSM_MODEM_SIM800
// #define TINY_GSM_MODEM_SIM808
// #define TINY_GSM_MODEM_SIM900
// #define TINY_GSM_MODEM_A6
// #define TINY_GSM_MODEM_A7
// #define TINY_GSM_MODEM_M590
// #define TINY_GSM_MODEM_ESP8266

// Use Hardware Serial on Mega, Leonardo, Micro
//#define SerialAT Serial1

// or Software Serial on Uno, Nano
#include <SoftwareSerial.h>
SoftwareSerial SerialAT(10, 11); // RX, TX


// Your GPRS credentials
// Leave empty, if missing user or pass
const char apn[]  = "internet.ideasclaro";
const char user[] = "";
const char pass[] = "";

// Name of the server we want to connect to
const char server[] = "monitoreoagua.ucr.ac.cr";
const int  port     =  80;
// Path to download (this is the bit after the hostname in the URL)
const char resource[] = "/android/test.php";

#include <TinyGsmClient.h>
#include <ArduinoHttpClient.h>

TinyGsm modem(SerialAT);

TinyGsmClient client(modem);
HttpClient http(client, server, port);

void setup() {
  // Set console baud rate
  Serial.begin(9600);
  delay(10);

  // Set GSM module baud rate
  SerialAT.begin(9600);
  delay(3000);

  // Restart takes quite some time
  // To skip it, call init() instead of restart()
 
  DEBUG_PRINT("Initializing modem...");
  modem.restart();

  String modemInfo = modem.getModemInfo();
  DEBUG_PRINT("Modem: ");

  DEBUG_PRINT(modemInfo);

  // Unlock your SIM card with a PIN
  //modem.simUnlock("1234");
}

void loop() {
  for(int i=0;i<100;i++){
    getRequest();
  }
  
}



void getRequest(){
  
  DEBUG_PRINT(F("Waiting for network..."));
  if (!modem.waitForNetwork()) {
    DEBUG_PRINT(" fail");
    delay(10000);
    return;
  }
 
  DEBUG_PRINT(" OK");

  if(!modem.isGprsConnected()){
      DEBUG_PRINT(F("Connecting to "));
      DEBUG_PRINT(apn);
      if (!modem.gprsConnect(apn, user, pass)) {
        DEBUG_PRINT("fail");
        delay(10000);
        return;
      }
  }
 
  DEBUG_PRINT(" OK");


  DEBUG_PRINT(F("Performing HTTP GET request... "));
  int err = http.get(resource);
  if (err != 0) {
    DEBUG_PRINT("failed to connect");
    delay(10000);
    return;
  }

  int status = http.responseStatusCode();
 
  DEBUG_PRINT(status);
  if (!status) {
    delay(10000);
    return;
  }

  while (http.headerAvailable()) {
    String headerName = http.readHeaderName();
    String headerValue = http.readHeaderValue();
    DEBUG_PRINT(headerName + " : " + headerValue);
  }

  int length = http.contentLength();
  if (length >= 0) {
   
    DEBUG_PRINT(String("Content length is: ") + length);
  }
  if (http.isResponseChunked()) {
   
    DEBUG_PRINT("This response is chunked");
  }

  String body = http.responseBody();
 
  DEBUG_PRINT("Response:");
  
  Serial.println(body);

  
  DEBUG_PRINT(String("Body length is: ") + body.length());
  
  // Shutdown

  http.stop();

  //modem.gprsDisconnect();
  DEBUG_PRINT("GPRS disconnected");  
  }
