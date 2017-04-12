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
    '1', '2', '3'
  }
  ,
  {
    '4', '5', '6'
  }
  ,
  {
    '7', '8', '9'
  }
  ,
  {
    '*', '0', '#'
  }
};
// Connect keypad ROW0, ROW1, ROW2 and ROW3 to these Arduino pins.
byte rowPins[ROWS] = {
  22, 23, 24, 25
};
// Connect keypad COL0, COL1 and COL2 to these Arduino pins.
byte colPins[COLS] = {
  14, 15, 16
};
Keypad kpd = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );
LiquidCrystal lcd(RS_LCD_pin, E_LCD_pin, D4_LCD_pin, D5_LCD_pin, D6_LCD_pin, D7_LCD_pin);//Inicialización de la librería LiquidCrystal
RTC_DS1307 RTC; //Inicializa el reloj RTC

//vectores correspondientes al menú
String menu[3] = {"Medicamentos", "Plantas", "Vehiculos"};
String medicamentos[2][2] = {{"inyeccion", "pastilla"}, {"0", "0"}};
String plantas[3][3] = {{"Medicinale", "hornamentale", "Venenosa"}, {"0", "0", "0"}};
String vehiculos[4][4] = {{"4x4", "4x2", "2x2", "2x4"}, {"0", "0", "0", "0"}};
int tamano[4] = {3, 2, 3, 4}; //tamaños de cada vector del menu, submenues
int ptrMenu;//puntero a la posición del menú que estamos
int ptrSubMenu;


//flags
bool lectureFlag = false; //se activa al leer algo del teclado de 4 botones
bool menuFlag = false;
bool subMenuFlag = false;
bool printFlag = false; //se activa cuando hay algo que modificar
bool keyboardFlag = false; //se activa al leer un * del teclado de 4x4
bool changesFlag = false; //se activa si se edito el valor de alguna entrada ej: temp, humedad etc

//vector teclado 4 botones
int pinesTeclado[] = {
  botonFuncion_next_pin, botonFuncion_prev_pin, boton_next_pin, boton_prev_pin
};


void setup() {
  // put your setup code here, to run once:
  ptrMenu = 0;
  ptrSubMenu = -1;
  Serial.begin(9600);       //Inicialización de la comunicación serial.
  RTC.begin();        // Inicia la comunicación con el RTC
  Ini_Pines();        //Inicialización de los pines.
  lcd.begin(16, 2);   //Inicialización de la pantalla LCD de campo.
  lcd.clear();        //Se limpia la pantalla LCD de campo.
  Serial.print("ingPlantae\n");
  //lcd.print("ingPlantae");
  //lcd.setCursor(0, 1);
  //lcd.print("UCR");
  Serial.print("UCR\n");
  delay(2);
  lcd.setCursor(0, 0);
  //lcd.print(menu[ptrMenu]);
  lcd.setCursor(1, 0);
  Serial.print(menu[ptrMenu] + "\n");
  //colocar la hora aquí
}

void loop() {
  // put your main code here, to run repeatedly:
  //***INICIO de lectura de teclado de 4 botones***///
  if (Serial.available() > 0) {
    char tec='-';
    teclado();
    if (lectureFlag) {//si se modificó algún valor
      lectureFlag = false; //hacemos la acción y la desactivamos
      //ahora vemos que fue lo modificado menú o subMenú
      if (menuFlag) { //si se modifico el menú
        menuFlag = false; //desactivamos la bandera del menú
        //lcd.print(menu[ptrMenu]);
        Serial.println(menu[ptrMenu]);
      } else if (subMenuFlag) { //vemos si fue del subMenu
        subMenuFlag = false; //desactivamos la bandera
        switch (ptrMenu) {
          case 0:
            //lcd.print(medicamentos[0][ptrSubMenu]);
            Serial.println(medicamentos[0][ptrSubMenu]);
            break;
          case 1:
            //lcd.print(plantas[0][ptrSubMenu]);
            Serial.println(plantas[0][ptrSubMenu]);
            break;
          case 2:
            //lcd.print(vehiculos[0][ptrSubMenu]);
            Serial.println(vehiculos[0][ptrSubMenu]);
            break;
        }
      }
    }
    //***FIN de lectura de teclado de 4 botones***///
    if (ptrSubMenu != -1) {
      Serial.println("jajaja");
      //tecla = kpd.getKey();
      int tecla = Serial.read();
      Serial.println(tecla);
      if (tecla == 48) { //esto quiere decir que queremos editar el campo
        Serial.println("entrando a formato");
        String valor = formato();
        Serial.println("saliendo de formato");
        switch (ptrMenu) {
          case 0:
            Serial.println("antes " + medicamentos[1][ptrSubMenu]);
            medicamentos[1][ptrSubMenu] = valor;
            Serial.println("Después " + medicamentos[1][ptrSubMenu]);

            break;
          case 1:
            Serial.println("antes " + plantas[1][ptrSubMenu]);
            plantas[1][ptrSubMenu] = valor;
            Serial.println("Después " + plantas[1][ptrSubMenu]);
            break;
          case 2:
            Serial.println("antes " + vehiculos[1][ptrSubMenu]);
            vehiculos[1][ptrSubMenu] = valor;
            Serial.println("Después " + vehiculos[1][ptrSubMenu]);
            break;
        }
      }
    }
  }
}


//Función para inicializar todos los pines del Arduino, solamente los pines DIGITALES deben ser declarados
void Ini_Pines() {
  int pines_entrada[] = {
    boton_next_pin, boton_prev_pin, botonFuncion_next_pin, botonFuncion_prev_pin, boton_timer, boton_temp, boton_rad, boton_hs, boton_dem
  };//vector que contiene los pines
  int long_pinesEntrada = sizeof(pines_entrada) / sizeof(int); //Se obtiene la longitud del vector que contiene los pines de entradas
  for (int j = 0; j < long_pinesEntrada; j++) {
    pinMode(pines_entrada[j], INPUT);//Se declaran todos como entradas
  }
}//Fin Ini_Pines()


//nos movemos dentro del menu
void imprimir() {

}


String formato() {
  String keyString;//Concatenacion de los valores obtenidos mediante el teclado
  char key = ' '; //caracter unico devuelto por el teclado
  keyString = " ";
  do {
    keyString = keyString + key;
    //lcd.print(keyString);
    Serial.println(keyString);
    //key = kpd.getKey();
    key = Serial.read();
  } while (key != '#');

  return keyString;
}//inicio funcion formato

void teclado() {
  char actual = 'e';//valor de la tecla presionada
  int longitud = sizeof(pinesTeclado) / sizeof(int);
  //leemos para ver si se presionó alguna tecla
  //for (int i = 0; i < longitud; i++) {
  //if (digitalRead(pinesTeclado[i])) {
  //actual = i;
  //break;
  //}
  actual = Serial.read();
  //Serial.println(actual);
  //analizamos las opciones
  int tamanoSubMenu;
  if (actual != 'e') {
    lectureFlag = true;
    switch (actual) {
      case '0'://caso menú a la izquierda
        menuFlag = true;//notificamos que se ha modificado el menú
        ptrSubMenu = -1; //al mover en el menú nos ubicamos en el primero del subMenu
        //subMenuFlag=false;
        if (ptrMenu == 0) {
          ptrMenu = tamano[0] - 1; //última posición
        } else {
          ptrMenu --;
        }
        break;
      case '1'://caso menú a la derecha
        menuFlag = true;//notificamos que se ha modificado el menú
        ptrSubMenu = -1; //al mover en el menú nos ubicamos en el primero del subMenu
        //subMenuFlag=false;
        if (ptrMenu == tamano[0] - 1) {
          ptrMenu = 0;//primera posición
        } else {
          ptrMenu ++;
        }
        break;
      case '2'://caso subMenu derecha
        subMenuFlag = true;
        if (ptrSubMenu == -1) {
          ptrSubMenu = 0;
        }
        tamanoSubMenu = tamano[ptrMenu + 1]; // en esta posición obtenemos el tamaño del subMenu actual
        if (ptrSubMenu == 0) {
          ptrSubMenu = tamanoSubMenu - 1;
        } else {
          ptrSubMenu--;
        }
        break;
      case '3'://caso subMenu izquierda
        subMenuFlag = true;
        tamanoSubMenu  = tamano[ptrMenu + 1]; // en esta posición obtenemos el tamaño del subMenu actual
        if (ptrSubMenu == tamanoSubMenu - 1 ) {
          ptrSubMenu = 0;
        } else {
          ptrSubMenu++;
        }
        break;
    }
  }
}//teclado que recibe una (o ninguna) de las 4 opciones de botones


