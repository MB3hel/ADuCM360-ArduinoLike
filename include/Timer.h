#ifndef __TIMER_H__
#define __TIMER_H__

#include <cstdint>

#define TIMER_FREQUENCY_HZ (1000u)
typedef int Ticks;

class Timer{

public:
   void delay(Ticks ticks);
   long millis();
   Timer();

};

#endif
