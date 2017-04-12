#define trigPin 13
#define echoPin 12

void setup() {
  // put your setup code here, to run once:
  pinMode(trigPin, OUTPUT);//configuración de pines
  pinMode(echoPin, INPUT);//configuración de pines
  Serial.begin(9600);//abrir puerto serie
}

void loop() {
  // put your main code here, to run repeatedly:
  long duration, distance;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin,HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin,LOW);
  duration = pulseIn(echoPin, HIGH);//obtener tiempo de viaje
  distance= (duration / 2)/29.1;
  Serial.println(distance);
  delay(500);
}



  //for (int i = 0; i <= 255; i++) {
//    digitalWrite(led, HIGH); //encender LED
//    Serial.println(i);
//    delay(10);
//  }
//
//  for (int i = 0; i <= 255; i++) {
//    digitalWrite(led, LOW); //apagar LED
//    Serial.println(i);
//    delay(10);
//  }
