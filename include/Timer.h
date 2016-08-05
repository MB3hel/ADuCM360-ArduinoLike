#include <cstdint>

#define TIMER_FREQUENCY_HZ (1000u)
typedef int Ticks;

class Timer{

public:
   void delay(Ticks ticks);
   long millis();
   Timer();

};
