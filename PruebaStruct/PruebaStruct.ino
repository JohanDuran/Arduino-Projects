const int tamano=1;

struct myE{
String main;
char *buff[tamano];
};
void setup(){
  Serial.begin(9600);
  myE b;
        
   int *ptr;
  ptr = (int*)( &tamano );
  *ptr = 5; // I'm a liar, a is now 5
  myE b1;
  myE b2;
  myE b3;
  myE b4;
  myE b5;
  myE b6;
  myE b7;
  myE b8;
  myE b9;
  b.buff[0]= "hola";
  b.buff[1]= "hola1";
  b.buff[2]= "hola2";
  b.buff[3]= "hola3";
  b.buff[4]= "hola4";
  for (int i =0;i<5;i++){
      Serial.println(b.buff[i]);
    }


}

void loop(){

}
