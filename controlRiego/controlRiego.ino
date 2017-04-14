/*
 * TimeAlarmExample.pde
 *
 * This example calls alarm functions at 8:30 am and at 5:45 pm (17:45)
 * and simulates turning lights on at night and off in the morning
 * A weekly timer is set for Saturdays at 8:30:30
 *
 * A timer is called every 15 seconds
 * Another timer is called once only after 10 seconds
 *
 * At startup the time is set to Jan 1 2011  8:29 am
 */

// Questions?  Ask them here:
// http://forum.arduino.cc/index.php?topic=66054.0

#include <TimeLib.h>
#include <TimeAlarms.h>

AlarmId id;

//pin interruptor de motor
int pinInterruptor=2;

void setup() {
  Serial.begin(9600);
  while (!Serial) ; // wait for Arduino Serial Monitor

  setTime(17,30,0,7,3,17); // set time to Saturday 8:29:00am Jan 1 2011

  // create the alarms, to trigger at specific times
  Alarm.alarmRepeat(5,30,0, WaterAlarm);  // 5:30am every day
  Alarm.alarmRepeat(18,20,0,WaterAlarm);  // 6:45pm every day
  //Alarm.alarmRepeat(dowSaturday,8,30,30,WeeklyAlarm);  // 8:30:30 every Saturday

  // create timers, to trigger relative to when they're created
  //Alarm.timerRepeat(15, Repeats);           // timer for every 15 seconds
  //id = Alarm.timerRepeat(2, Repeats2);      // timer for every 2 seconds
  //Alarm.timerOnce(10, OnceOnly);            // called once after 10 seconds
  pinMode(pinInterruptor,OUTPUT);
}

void loop() {
  digitalClockDisplay();
  Alarm.delay(1000); // wait one second between clock display
}

// functions to be called when an alarm triggers:
void WaterAlarm() {
  Serial.println("Giving water to plants");
  digitalWrite(pinInterruptor,HIGH);
  delay(18000);
  digitalWrite(pinInterruptor,LOW);
  delay(1000);
}

void EveningAlarm() {
  Serial.println("Giving water to plants");
}



void digitalClockDisplay() {
  // digital clock display of the time
  Serial.print(hour());
  printDigits(minute());
  printDigits(second());
  Serial.println();
}

void printDigits(int digits) {
  Serial.print(":");
  if (digits < 10)
    Serial.print('0');
  Serial.print(digits);
}

