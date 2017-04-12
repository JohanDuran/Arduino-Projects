int lamp = 10;
int estado;
void setup() {
  // put your setup code here, to run once:
  pinMode(lamp, OUTPUT);
  Serial.begin(9600);    // inicia el puerto serial para comunicacion con el Bluetooth
}

void loop() {
  // put your main code here, to run repeatedly:
  if (Serial.available() > 0) {    // lee el bluetooth y almacena en estado
    estado = Serial.read();
   // digitalWrite(lamp,HIGH);
    //delay(1000);
    //digitalWrite(lamp,LOW);
    //delay(1000);        
    printf("%c",estado);
    if (estado == 'e') {
      digitalWrite(lamp, HIGH);
    } else {
      if (estado == 'a') {
        digitalWrite(lamp, LOW);
      }
    }
  }
}

