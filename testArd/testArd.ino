int izquierdaA = 5;//puente H
int izquierdaR = 6;//puente H
int derechaA = 10;//puente H
int derechaR = 9;//puente H
int dirDer = 8;
int dirIzq = 9;
int estado = 's';
int velocidad = 255;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);//se inicia comunicación serial a 9600 baudios
  pinMode(adelante, OUTPUT);
  pinMode(atras, OUTPUT);
  pinMode(derechaA, OUTPUT);
  pinMode(izquierdaA, OUTPUT);
  pinMode(derechaR, OUTPUT);
  pinMode(izquierdaR, OUTPUT);
  pinMode(dirDer, OUTPUT);
  pinMode(dirIzq, OUTPUT);
  pinMode(centro, OUTPUT);
}

void loop() {
  //s = detener todo, r = reversa, a = adelante, d=derecha, i = izquierda. 
  if (Serial.available() > 0) {
    estado = Serial.read();
    if (estado == 's') {
      digitalWrite(derechaA, 0);
      digitalWrite(izquierdaA, 0);
      digitalWrite(derechaR, 0);
      digitalWrite(izquierdaR, 0);
      delay(1000);
    }

    if (estado == 'a') {
      digitalWrite(derechaR, 0);
      digitalWrite(izquierdaR, 0);
      digitalWrite(derechaA, velocidad);
      digitalWrite(izquierdaA, velocidad);
      delay(1000);
    }
    
    if (estado == 'r') {
      digitalWrite(derechaA, 0);
      digitalWrite(izquierdaA, 0);
      digitalWrite(derechaR, velocidad);
      digitalWrite(izquierdaR, velocidad);
      delay(1000);
    }    

    if (estado == 'i') {
      digitalWrite(izquierdaA, 0);
      digitalWrite(izquierdaR, 0);
      digitalWrite(derechaR, velocidad);
      digitalWrite(derechaA, velocidad);
      delay(1000);
    }

    if (estado == 'd') {
      digitalWrite(izquierdaR, 0);
      digitalWrite(derechaR, 0);
      digitalWrite(derechaA, 0);
      digitalWrite(izquierdaA, velocidad);
      delay(1000);
    }

    if (estado == 'l') {
      digitalWrite(izquierdaA, 0);
      digitalWrite(izquierdaR, 0);
      digitalWrite(derechaR, velocidad);
      digitalWrite(derechaA, 0);
      delay(1000);
    }

    if (estado == 'r') {
      digitalWrite(derechaR, 0);
      digitalWrite(derechaA, 0);
      digitalWrite(izquierdaA, 0);
      digitalWrite(izquierdaR, velocidad);
      delay(1000);
    }
  } else {
      digitalWrite(izquierdaR, 0);
      digitalWrite(derechaR, 0);
      digitalWrite(derechaA, 0);
      digitalWrite(izquierdaA, 0);
      delay(1000);
  }
}

