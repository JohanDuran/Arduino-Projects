#include<SoftwareSerial.h>
SoftwareSerial BT1(3, 2); // RX | TX
char txt;
void setup()
{ 
  Serial.begin(9600);
  BT1.begin(9600);
}
void loop()
{if (Serial.available())
{txt = Serial.read();
BT1.print(txt);
}
if (BT1.available())
{txt = BT1.read();
Serial.print(txt);
}
}
