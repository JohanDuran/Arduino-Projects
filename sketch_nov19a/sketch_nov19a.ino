int adelante=6;
int atras = 5;
int velocidad = 255;
void setup() {
  // put your setup code here, to run once:
pinMode(adelante,OUTPUT);
pinMode(atras,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
digitalWrite(atras,0);
digitalWrite(adelante,velocidad);
delay(10000);
digitalWrite(adelante,0);
digitalWrite(atras,velocidad);
delay(10000);
}
