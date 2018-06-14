#include <ArduinoJson.h>
#include <Http.h>

unsigned long lastRunTime = 0;
unsigned long waitForRunTime = 0;

unsigned int RX_PIN = 7;
unsigned int TX_PIN = 8;
unsigned int RST_PIN = 12;
HTTP http(9600, RX_PIN, TX_PIN, RST_PIN);

// the setup routine runs once when you press reset:
void setup() {
  Serial.begin(9600);
  while(!Serial);
  Serial.println("Starting!");
  http.configureBearer("movistar.ideasclaro");
}

// functions
void print(const __FlashStringHelper *message, int code = -1){
  if (code != -1){
    Serial.print(message);
    Serial.println(code);
  }
  else {
    Serial.println(message);
  }
}



// the loop routine runs over and over again forever:
void loop() {
  http.connect();
  char response[500];
  Result result = http.get("httpbin.org/get", response);
  
  Serial.println(response);
  print(F("HTTP GET: "), result);
  if (result == SUCCESS) {
    Serial.println(response);
    StaticJsonBuffer<500> jsonBuffer;
    JsonObject& root = jsonBuffer.parseObject(response);
    lastRunTime = millis();
    waitForRunTime = root["waitForRunTime"];
    
    print(F("Last run time: "), lastRunTime);
    print(F("Next post in: "), waitForRunTime);
  }
  
  print(F("HTTP disconnect: "), http.disconnect());  
  http.disconnect();
}


