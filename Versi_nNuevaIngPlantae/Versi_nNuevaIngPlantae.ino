/* Esta versión ya tiene incluida los leds de cada modo de operacion 
 y se ha hecho un solo indicador led para todos los archivos .csv
 falta aun poder imprimir en la pantalla cuales archivos no han sido cargados 
 e imprimir los acomulados de riego y drenaje.  Y verificar la funcion de diaNoche*/



#include <LiquidCrystal.h> //Librería para la comunicación con las pantallas LCD de 16x2 caracteres.
#include "Arduino.h"
#include <Keypad.h>  //librería para la utilización del keypad
#include <RTClib.h> //Librería para utilizar el reloj en tiempo real "RTC", del módulo I2C.
/********************************************************************************************************/
/*  Declaracion de los pines                  */
/********************************************************************************************************/

/*NOTA: NO SE DEBEN UTILIZAR LOS SIGUIENTES PINES, YA QUE ESTAN RESERVADOS PARA LA SIGUIETES FUNCIONES: 
 Estos son para el funcionamiento de la memoria SD
 SD_pin = pines 10 UNO y 53 MEGA. 
 CS_pin = 4;
 Estos para el fun‌cionamiento del reloj en tiempo real
 SDA _pin = 20; corresponde también a la interrupción 3
 SCL_pin  = 21; corresponde también a la interrupcion 2
 Estos para el funcionamiento de las interrupciones:
 Pin de demanda: 2
 Pin de drenaje alto: 3
 Pin de drenaje bajo: 18
 */


//Pantalla de cristal liquido
//LCD 16x2
const int RS_LCD_pin  = 6;
const int E_LCD_pin   = 7;
const int D4_LCD_pin  = 8;
const int D5_LCD_pin  = 9;
const int D6_LCD_pin  = 11;
const int D7_LCD_pin  = 12;


//BOTONES de entrada
const int boton_prev_pin    = 28;
const int boton_next_pin    = 29;
const int botonFuncion_prev_pin   = 30;
const int botonFuncion_next_pin   = 31;
//Disponibles hasta el 33, porque en la 34 empiezan los Botones de funciones.

//Botones de funciones
const int boton_timer   = 34;
const int boton_temp  = 35;
const int boton_rad   = 36;
const int boton_hs  = 37;
const int boton_dem   = 38;
//Disponibles hasta el 38, porque en la 40 empiezan los LEDs indicadores y 39 es un boton de accionamiento manual


//LEDs indicadores
const int timerLED_pin  = 40;
const int tempLED_pin   = 41;
const int radLED_pin  = 42;
const int hsLED_pin   = 43;
const int demLED_pin  = 44;
const int SDLED_pin = 45;   //Pin de la luz indicadora que se ha inicializado la memoria SD correctamente.
//Disponibles hasta la 45, en la 46 empiezan las salidas...


//CONFIGURACIÓN PARA EL USO DEL KEYPAD
const byte ROWS = 4; // Four rows
const byte COLS = 3; // Three columns
// Define the Keymap
char keys[ROWS][COLS] = {
  {
    '1','2','3'            }
  ,
  {
    '4','5','6'            }
  ,
  {
    '7','8','9'            }
  ,
  {
    '*','0','#'            }
};
// Connect keypad ROW0, ROW1, ROW2 and ROW3 to these Arduino pins.
byte rowPins[ROWS] = { 
  22, 23, 24, 25};
// Connect keypad COL0, COL1 and COL2 to these Arduino pins.
byte colPins[COLS] = { 
  14, 15, 16}; 
Keypad kpd = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );
LiquidCrystal lcd(RS_LCD_pin, E_LCD_pin, D4_LCD_pin, D5_LCD_pin, D6_LCD_pin, D7_LCD_pin);//Inicialización de la librería LiquidCrystal
RTC_DS1307 RTC; //Inicializa el reloj RTC

//vectores para impresion e insersion
String salidas[7][3]={{"A","B","C"},{"xa","ya","za"},{"1","2","3"},{"xb","yb","zb"},{"4","5","6"},{"xc","yc","zd"},{"7""8""8"}};
int tamanoSub []={3,2,3,2};


String main[]={"A","B","C"};

String subMain_A[]={"xa","xa","xa"};
int ValSubMain_A[]={1,2,3};

String subMain_B[]={"xb","xb","xb"};
int ValSubMain_B[]={4,5,6};

String subMain_C[]={"xc","xc","xc"};
int ValSubMain_C[]={7,8,9};

int punteroMain;
int punteroSubMain;

//flags
bool lectureFlag=false;//se activa al leer algo del teclado de 4 botones
bool mainFlag=false;
bool subMainFlag=false;
bool printFlag=false;//se activa cuando hay algo que modificar
bool keyboardFlag=false;//se activa al leer un * del teclado de 4x4
bool changesFlag=false;//se activa si se edito el valor de alguna entrada ej: temp, humedad etc
  
//vector teclado 4 botones
  int pinesTeclado[] = {
    botonFuncion_next_pin, botonFuncion_prev_pin, boton_next_pin, boton_prev_pin};

//puntero a sub menues    
String * valPtr;
void setup(){
  punteroMain=0;
  punteroSubMain=1;
  //val = main;
  Serial.begin(9600);       //Inicialización de la comunicación serial.
  valPtr = subMain_A;
  RTC.begin();        // Inicia la comunicación con el RTC
  Ini_Pines();        //Inicialización de los pines.
  lcd.begin(16,2);    //Inicialización de la pantalla LCD de campo.
  lcd.clear();        //Se limpia la pantalla LCD de campo.
  lcd.print("ingPlantae");
  lcd.setCursor(0,1);
  lcd.print("UCR");
  delay(2);
    lcd.setCursor(0,0);
  lcd.print(main[punteroMain]);
  lcd.setCursor(1,0);
  //colocar la hora aquí
}

void loop(){
  //leemos del teclado de 4 botones
  teclado();//recibimos el numero de la tecla presionada
  imprimir();//imprimimos en pantalla
  //leemos del keyBoard
  //modificamos 
  //imprimimos
  char key = kpd.getKey();  //Con esto puedo obtener las letras que van entrando al sistema, ahora lo que necesito es formar strings y asignarles los nuevos valores a las variables sobre las cuales ingreso un numero
  //pantalla(tecla);
}

//Función para inicializar todos los pines del Arduino, solamente los pines DIGITALES deben ser declarados
void Ini_Pines(){
  int pines_entrada[] = {
  boton_next_pin, boton_prev_pin, botonFuncion_next_pin, botonFuncion_prev_pin, boton_timer, boton_temp, boton_rad, boton_hs, boton_dem};//vector que contiene los pines
  int long_pinesEntrada = sizeof(pines_entrada)/sizeof(int);//Se obtiene la longitud del vector que contiene los pines de entradas
  for(int j=0;j<long_pinesEntrada;j++){
    pinMode(pines_entrada[j], INPUT);//Se declaran todos como entradas
  }
}//Fin Ini_Pines()


//nos movemos dentro del menu
void imprimir(){
if(lectureFlag){
  lectureFlag=false;
  if(mainFlag){
    mainFlag=false;
    lcd.print(main[punteroMain]);
    }else if(subMainFlag){
      subMainFlag=false;
      switch(punteroMain){
        case 0:
        lcd.print(subMain_A[punteroSubMain]);
        break;
        case 1:
        lcd.print(subMain_B[punteroSubMain]);
        break;
        case 2:
        lcd.print(subMain_C[punteroSubMain]);
        break;
        }
      }
  }
}


void formato(){
  String keyString;//Concatenacion de los valores obtenidos mediante el teclado
  char key=' ';//caracter unico devuelto por el teclado
  keyString =" ";  
  while(key != '*'){
    keyString = keyString + key; 
  }
  lcd.print(keyString);
}//inicio funcion formato

void teclado(){
  //char key = kpd.getKey();  //Con esto puedo obtener las letras que van entrando al sistema, ahora lo que necesito es formar strings y asignarles los nuevos valores a las variables sobre las cuales ingreso un numero
  int actual=-1;
    int longitud=sizeof(pinesTeclado)/sizeof(int);
    for (int i =0;i<longitud;i++){
    if (digitalRead(pinesTeclado[i])){
      actual=i;
      i+=longitud;
      lectureFlag=true;
    }  
  }

int pad,hijR,hijC;
  if(actual!=-1){
    switch(actual){
      case 0://main derecha
      mainFlag=true;
      if(punteroMain==0){
        punteroMain=tamanoSub[0];
        }else{
          punteroMain--;
          }
z          hijoF=punteroMain+2;
          hijoC=0;
      break;
      case 1://main izquierda
      mainFlag=true;
            if(punteroMain==tamanoSub[0]){
        punteroMain=0;
        }else{
          punteroMain++;
          }
          hijoF=punteroMain-2;
          hijoC=0;
      break;
      case 2://sub izquierda
      subMainFlag=true;
      hijoC++;
      break;
      case 3://sub derecha
      subMainFlag=true;
            if(punteroMain==3){
        punteroMain=0;
        }else{
          punteroMain++;
          }
      break;
      }
    }
}//teclado que recibe una (o ninguna) de las 4 opciones de botones






