#include <SoftwareSerial.h>
SoftwareSerial SSoft(3, 2); // RX Pin 3 Receptor | TX Pin 2 Transmisor
char caracter;
void setup()
{
Serial.begin(9600);
SSoft.begin(9600);
}
void loop()
{
if (SSoft.available())
{
caracter = SSoft.read();
Serial.print(caracter);
}
if (Serial.available())
{
caracter = Serial.read();
SSoft.print(caracter);
}
}
