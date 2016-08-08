#ifndef __ARDUINO_LIKE_H
#define __ARDUINO_LIKE_H

#include "Serial.h"
#include "Timer.h"
#include "DIO.h"
#include <cstdlib>
#include "ArduinoEthernet/dependency/IPAddress.h"

typedef bool boolean;
typedef uint8_t byte;

typedef unsigned int word;

#define word(...) makeWord(__VA_ARGS__)

inline unsigned int makeWord(unsigned int w) { return w; }
inline unsigned int makeWord(unsigned char h, unsigned char l) { return (h << 8) | l; }

using namespace std;

extern "C"{

#include "Communication.h"

}

static Timer timer;
static Serial serial;
static DIO dio;

extern "C"{

static void __empty() {
   // Empty
}
void yield(void) __attribute__ ((weak, alias("__empty")));

}

inline string ipToString(IPAddress addr){

	char b1[3];
	char b2[3];
	char b3[3];
	char b4[3];

	itoa(addr[0], b1, 10);
	itoa(addr[1], b2, 10);
	itoa(addr[2], b3, 10);
	itoa(addr[3], b4, 10);

	String address = String(b1) + "." + String(b2) + "." + String(b3) + "." + String(b4);

	return address.c_str();

}

inline void delay(Ticks ticks){

   timer.delay(ticks);

}

inline long millis(){

   return timer.millis();

}

inline void pinMode(int bar, int pin, char mode){

   dio.setMode(bar, pin, mode);

}

inline void digitalWrite(int bar, int pin, int power){

   dio.digitalWrite(bar, pin, power);

}

inline void digitalToggle(int bar, int pin){

   dio.digitalToggle(bar, pin);

}

inline int digitalRead(int bar, int pin){

   return dio.digitalRead(bar, pin);

}

inline long random(long howbig)
{
  if (howbig == 0) {
    return 0;
  }
  return rand() % howbig;
}

inline long random(long howsmall, long howbig)
{
  if (howsmall >= howbig) {
    return howsmall;
  }
  long diff = howbig - howsmall;
  return random(diff) + howsmall;
}


#endif
