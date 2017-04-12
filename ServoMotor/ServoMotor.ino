// Mover servo de extremo a extremo con parada en el centro
// Descargar el programa y plano en www.elprofegarcia.com

#include <Servo.h>                // Incluye la libreria Servo
 
Servo servo1;                    // Crea el objeto servo1 con las caracteristicas de Servo
int adelante = 5;
int atras =6;
void setup() 
{ 
  pinMode(adelante,OUTPUT);
  pinMode(atras,OUTPUT);
  servo1.attach(3,600,1500);    // Asocia el servo1 al pin 3, define el min y max del ancho del pulso  
}                               // eso depende del fabricante del servo
  
void loop() 
{                
    digitalWrite(adelante,250);
    delay(2000);
        digitalWrite(adelante,0);
    digitalWrite(atras,250);
    delay(2000);  
    digitalWrite(atras,0);

           
    servo1.write(0);                // Gira el servo a 0 grados  
    delay(700);                     // Espera 700 mili segundos a que el servo llegue a la posicion
   
    servo1.write(90);               // Gira el servo a 90 grados  
    delay(700);  
                      
    servo1.write(180);             //Gira el servo a 180 grados 
    delay(700);                       

  }  
