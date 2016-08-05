#include "Serial.h"
#include "Timer.h"
#include "DIO.h"

extern "C"{

#include "Communication.h"

}

Timer timer;
Serial serial;
DIO dio;

namespace ArduinoLike{

   void delay(Ticks ticks){

      timer.delay(ticks);

   }

   long millis(){

      return timer.millis();

   }

   void pinMode(int bar, int pin, char mode){

   	dio.setMode(bar, pin, mode);

   }

   void digitalWrite(int bar, int pin, int power){

   	dio.digitalWrite(bar, pin, power);

   }

   void digitalToggle(int bar, int pin){

   	dio.digitalToggle(bar, pin);

   }

   int digitalRead(int bar, int pin){

   	return dio.digitalRead(bar, pin);

   }

}
