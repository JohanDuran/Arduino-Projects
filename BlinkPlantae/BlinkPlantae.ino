


#include <LiquidCrystal.h> //LibrerÃ­a para la comunicaciÃ³n con las pantallas LCD de 16x2 caracteres.
#include "Arduino.h"
#include <Keypad.h>  //librerÃ­a para la utilizaciÃ³n del keypad
#include <wire.h>
#include <RTClib.h> //LibrerÃ­a para utilizar el reloj en tiempo real "RTC", del mÃ³dulo I2C.

/*
  Blink
  Turns on an LED on for one second, then off for one second, repeatedly.

  Most Arduinos have an on-board LED you can control. On the Uno and
  Leonardo, it is attached to digital pin 13. If you're unsure what
  pin the on-board LED is connected to on your Arduino model, check
  the documentation at http://www.arduino.cc

  This example code is in the public domain.

  modified 8 May 2014
  by Scott Fitzgerald
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


//CONFIGURACIÃ“N PARA EL USO DEL KEYPAD
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
LiquidCrystal lcd(RS_LCD_pin, E_LCD_pin, D4_LCD_pin, D5_LCD_pin, D6_LCD_pin, D7_LCD_pin);//InicializaciÃ³n de la librerÃ­a LiquidCrystal
RTC_DS1307 RTC; //Inicializa el reloj RTC

char * menu[7][3] = {{"menuA!", "menuB!", "menuC!"}, {"subA1", "subA2", "subA3"}, {"1", "2", "3"}, {"subB1", "subB2", "subB3"}, {"4", "5", "6"}, {"subC1", "subC2", "subC3"}, {"7", "8", "9"}};

int mainPtr;
int subPos[3] = {1, 3, 5};
int tamano[3] = {3, 3, 3};
int iter;
// the setup function runs once when you press reset or power the board
void setup() {
  mainPtr = 0;
  iter = 0;
  Serial.begin(9600);
  // initialize digital pin 13 as an output.
}

// the loop function runs over and over again forever
void loop() {
  Serial.println("fefefffwfwefwef");
  imprimir();

  delay(10 * 1000);
  Serial.end();
}

void imprimir() {
  for (int i = 0; i < 3; i++) {
    Serial.println("soy el menu principal ");
    Serial.println(menu[0][i]);
    for (int j = 0; j < tamano[i]; j++) {
      Serial.println("soy el submenu ");
      Serial.println(menu[subPos[i]][j]);
      Serial.println("mis valores son ");
      Serial.println(menu[subPos[i]+1][j]);
    }
  }
}

