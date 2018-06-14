#include <ArduinoJson.h>
#include <Http.h>

unsigned long lastRunTime = 0;
unsigned long waitForRunTime = 0;

unsigned int RX_PIN = 11;
unsigned int TX_PIN = 10;
unsigned int RST_PIN = 12;
HTTP http(9600, RX_PIN, TX_PIN, RST_PIN);


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


// the setup routine runs once when you press reset:
void setup() {
  Serial.begin(9600);
  while(!Serial);
  Serial.println("Starting!");
  http.configureBearer("internet.claroideas");
  Serial.println("APN Configured");
}

// the loop routine runs over and over again forever:
void loop() {
  Serial.println("connecting");
  http.connect();
  
  char response[128];
  Result result = http.get("monitoreoagua.ucr.ac.cr/android/nearbyRiver.php?lat=9.832829&lng=-84.232197&dist=2000", response);
  delay(5000);
  //Serial.println(response);
  print(F("HTTP GET: "), result);
  if (result == SUCCESS) {
    Serial.println(response);
    StaticJsonBuffer<32> jsonBuffer;
    JsonObject& root = jsonBuffer.parseObject(response);
    lastRunTime = millis();
    waitForRunTime = root["waitForRunTime"];
    
    print(F("Last run time: "), lastRunTime);
    print(F("Next post in: "), waitForRunTime);
  }

  
  Serial.println("desconnecting");
  http.disconnect();
}


