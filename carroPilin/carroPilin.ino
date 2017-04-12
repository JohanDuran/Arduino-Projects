// Carro Inalámbrico Bluetooth
int choque = 7;
int pulsador = 0;
int ad = 5;
int at = 6;
int der = 9;
int izq = 10;
int adDirD = 13;
int adDirI = 12;
int atDirD = 4;
int atDirI = 2;
int vel = 255;  // Velocidad de los motores (0-255)
int estado = 'a';  // inicia en off
int adelante = 's';
int atras = 's';
int derP = 's';
int derS = 's';
int izqP = 's';
int izqS = 's';
int on = 's';
int off = 's';
int a = 0;
int b = 0;
int c = 0;
int d = 0;
int e = 0;
int f = 0;//ad
int g = 0;//atr
void setup()  {
  Serial.begin(9600);    // inicia el puerto serial para comunicacion con el Bluetooth
  pinMode(ad, OUTPUT);
  pinMode(at, OUTPUT);
  pinMode(der, OUTPUT);
  pinMode(izq, OUTPUT);
  pinMode(adDirD, OUTPUT);
  pinMode(adDirI, OUTPUT);
  pinMode(atDirD, OUTPUT);
  pinMode(atDirI, OUTPUT);
  pinMode(choque, INPUT);
}

void loop()  {
  if (Serial.available() > 0) {    // lee el bluetooth y almacena en estado
    estado = Serial.read();
  }
  pulsador = digitalRead(choque);
  if (pulsador == HIGH) {
    Serial.println("q");
    estado = 'a';
  }


  if (estado == 'a') {
    off = estado;
    on = 's';
  } else {
    if (estado == 'e') {
      on = estado;
      off = 's';
      estado = 's';
    }
  }
  if (off == 'a') {
    if (g == 0) {
      digitalWrite(ad, 0);
      digitalWrite(at, 0);
      digitalWrite(der, 0);
      digitalWrite(izq, 0);
      digitalWrite(adDirI, LOW);
      digitalWrite(atDirI, LOW);
      digitalWrite(adDirD, LOW);
      digitalWrite(atDirD, LOW);
      int adelante = 's';
      int atras = 's';
      int derP = 's';
      int derS = 's';
      int izqP = 's';
      int izqS = 's';
      int on = 's';
      //int off = 's';
      int a = 0;
      int b = 0;
      int c = 0;
      int d = 0;
      int e = 0;
      int f = 0;
      g++;
    }
  } else {
    if (on == 'e') {
      //g=ad;s=stop; r=reversa;e=auto;a=autoOFF; i=izqPres;m=izqsuelto;m=derePresionado;d=derecha suelto.
      if (estado == 'g') {
        adelante = estado;
        atras = 's';
      } else {
        if (estado == 'r') {
          atras = estado;
          adelante = 's';
        }
      }
      if (estado == 's') {
        digitalWrite(ad, 0);
        digitalWrite(at, 0);
        adelante = 's';
        atras = 's';
        f = 0;
        e = 0;
        //--------------------------------
        digitalWrite(adDirI, HIGH);
        digitalWrite(atDirI, HIGH);
        digitalWrite(adDirD, HIGH);
        digitalWrite(atDirD, HIGH);
        delay(100);
        digitalWrite(adDirI, LOW);
        digitalWrite(atDirI, LOW);
        digitalWrite(adDirD, LOW);
        digitalWrite(atDirD, LOW);
        delay(100);
        digitalWrite(adDirI, HIGH);
        digitalWrite(atDirI, HIGH);
        digitalWrite(adDirD, HIGH);
        digitalWrite(atDirD, HIGH);
        delay(100);
        digitalWrite(adDirI, LOW);
        digitalWrite(atDirI, LOW);
        digitalWrite(adDirD, LOW);
        digitalWrite(atDirD, LOW);
        delay(100);
      }

      if (adelante == 'g') {
        if (e == 0) {
          giro(adelante);
          e++;
        }
      } else {
        if (atras == 'r') {
          if (f == 0) {
            giro(atras);
            f++;
          }
        }
      }
      
      if (estado == 'i') {
        izqP = estado;
      } else {
        if (estado == 'm') {
          izqS = estado;
        } else {
          if (estado == 'n') {
            derP = estado;
          } else {
            if (estado == 'd') {
              derS = estado;
            }
          }
        }
      }

      if (a == 0) {
        if (izqP == 'i') {
          digitalWrite(adDirI, HIGH);
          digitalWrite(atDirI, HIGH);
          delay(100);
          digitalWrite(adDirI, LOW);
          digitalWrite(atDirI, LOW);
          delay(100);
          digitalWrite(adDirI, HIGH);
          digitalWrite(atDirI, HIGH);
          delay(100);
          digitalWrite(adDirI, LOW);
          digitalWrite(atDirI, LOW);
          digitalWrite(der, 0);
          digitalWrite(izq, vel);
          delay(170);
          izqS = 0;
          a++;
          b = 0;
        }
      } else {
        if (b == 0) {
          if (izqS == 'm') {
            digitalWrite(izq, 0);
            digitalWrite(der, vel);
            delay(30);
            b++;
            a = 0;
            izqP = 0;
          }
        }
      }

      if (c == 0) {
        if (derP == 'n') {
          digitalWrite(adDirD, HIGH);
          digitalWrite(atDirD, HIGH);
          delay(100);
          digitalWrite(adDirD, LOW);
          digitalWrite(atDirD, LOW);
          delay(100);
          digitalWrite(adDirD, HIGH);
          digitalWrite(atDirD, HIGH);
          delay(100);
          digitalWrite(adDirD, LOW);
          digitalWrite(atDirD, LOW);
          digitalWrite(izq, 0);
          digitalWrite(der, vel);
          delay(170);
          derS = 0;
          c++;
          d = 0;
        }
      } else {
        if (d == 0) {
          if (derS == 'd') {
            digitalWrite(der, 0);
            digitalWrite(izq, vel);
            delay(30);
            d++;
            c = 0;
            derP = 0;
          }
        }
      }
      digitalWrite(der, 0);
      digitalWrite(izq, 0);
      g = 0;
      off = 's';
    }
  }
}

void giro(int dir) {
  if (dir == 'g') {
    digitalWrite(at, 0);
    digitalWrite(ad, vel);
    f = 0;
  } else {
    if (dir == 'r') {
      digitalWrite(ad, 0);
      digitalWrite(at, vel);
      e = 0;
    }
  }
}

