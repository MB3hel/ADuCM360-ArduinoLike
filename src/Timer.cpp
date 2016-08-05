#include "Timer.h"
#include "cortexm/ExceptionHandlers.h"
#include "cmsis_device.h"
#include "GptLib.h"

volatile Ticks delayCount;
bool started = false;

long counter = 0;

void Timer::delay (Ticks ticks){

   delayCount = ticks;
   while (delayCount != 0u);

}

void tick (){

   if (delayCount != 0u) {

      delayCount--;

   }

   counter++;

}

long Timer::millis(){

   return counter;

}

void SysTick_Handler (){

   tick();

}

Timer::Timer(){

   SysTick_Config (SystemCoreClock / TIMER_FREQUENCY_HZ);

}
