  #include <Ethernet.h>
  #include <SPI.h>

  byte mac[] = {  0x90, 0xA2, 0xDA, 0x0D, 0xF6, 0xFF }; 
  byte ip[] = {  192, 168 , 0 , 105};
  byte gateway[] = { 192 , 168 , 0 , 1};      

  EthernetClient client;

  String temp= "data=1033";  
  bool conectar=false;
  void setup()
  {
  Ethernet.begin(mac, ip, gateway);
  Serial.begin(9600);
  Serial.println(Ethernet.localIP());
  delay(1000);
  delay(1000);
  }

  void loop()                                           
  {       
    delay(1000);
    delay(1000);
    Serial.println();
    Serial.println("connecting...");
    do{
      conectar = client.connect("127.0.0.1",8080);
    }while(!conectar);
    Serial.println("conected");
    if (conectar){        
      int var=rand();
      Serial.println(var);
      temp="data="+String(var);     
      Serial.println(temp);              
      Serial.println("Sending to Server: ");                    
      client.println("POST /Proyectos/ArduinoPHPPost/test.php HTTP/1.1");           
      Serial.print("POST /Proyectos/ArduinoPHPPost/test.php HTTP/1.1");           
      client.println("Host: 192.168.0.100");
      client.println("Content-Type: application/x-www-form-urlencoded");
      client.println("Connection: close");
      client.println("User-Agent: Arduino/1.0");
      client.print("Content-Length: ");
      client.println(temp.length());
      client.println();
      client.print(temp);
      client.println();                                           
    }
    delay(5000);
    client.stop();

//  if (client.available()) {
//   char c = client.read();
//   Serial.print(c);
//  }
//
//  if (!client.connected())  {
//    Serial.println();
//    Serial.println("disconnecting.");
//    client.stop();
//    for(;;)
//      ;
//   }                               
  }
