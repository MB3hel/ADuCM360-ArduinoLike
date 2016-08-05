#include <stdio.h>
#include <stdlib.h>
#include <ADuCM360.h>
#include "diag/Trace.h"
#include "ArduinoLike.h"

using namespace std;
using namespace ArduinoLike;

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Wmissing-declarations"
#pragma GCC diagnostic ignored "-Wreturn-type"

const unsigned use_irq = 1;

int main(int argc, char* argv[]){

   pinMode(0, 4, OUT);
   pinMode(0, 5, OUT);

   serial.begin(B9600);

   long lastToggle1 = 0;
   long lastToggle2 = 0;
   long lastSerial = 0;

   long toggle1 = 1000;
   long toggle2 = 500;
   long serialMessage = 500;

   while (1){

         long ms = millis();

         if(ms - lastToggle1 >= toggle1){

               digitalToggle(0, 4);
               lastToggle1 = ms;

         }

         if(ms - lastToggle2 >= toggle2){

               digitalToggle(0, 5);
               lastToggle2 = ms;

         }

         if(ms - lastSerial >= serialMessage){

               serial.begin(B9600, PIN12);
               serial.println("PC");
               delay(5);//Time to spit out before switch ports

               serial.begin(B9600, PIN67);
               serial.println("Arduino");
               delay(10);//Time to spit out before switch ports

               lastSerial = millis();

         }

   }

}

#pragma GCC diagnostic pop
