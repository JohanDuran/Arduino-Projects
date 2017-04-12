int led = 2;
int estado = 'b';
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);    // inicia el puerto serial para comunicacion con el Bluetooth
  pinMode(led, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (Serial.available() > 0) {    // lee el bluetooth y almacena en estado
    estado = Serial.read();
    
  if (estado == 'b') {
    digitalWrite(led, LOW);
  }
  if (estado = 'c') {
    digitalWrite(led, HIGH);
      delay(1000);
  }
  }else{
    digitalWrite(led, LOW);    
    }
  
}
