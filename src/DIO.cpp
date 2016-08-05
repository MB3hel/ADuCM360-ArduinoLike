#include <ADuCM360.h>
#include "DIO.h"
#include "DioLib.h"
#include <string>
#include <cstring>
#include <sstream>
#include <algorithm>

using namespace std;

ADI_GPIO_TypeDef* bars[] = {pADI_GP0, pADI_GP1, pADI_GP2};

//OEN Values
uint32_t bar0out[] = {GP0OEN_OEN0_OUT, GP0OEN_OEN1_OUT, GP0OEN_OEN2_OUT, GP0OEN_OEN3_OUT, GP0OEN_OEN4_OUT, GP0OEN_OEN5_OUT, GP0OEN_OEN6_OUT, GP0OEN_OEN7_OUT};
uint32_t bar0in[] = {GP0OEN_OEN0_IN, GP0OEN_OEN1_IN, GP0OEN_OEN2_IN, GP0OEN_OEN3_IN, GP0OEN_OEN4_IN, GP0OEN_OEN5_IN, GP0OEN_OEN6_IN, GP0OEN_OEN7_IN};
uint32_t bar1out[] = {GP1OEN_OEN0_OUT, GP1OEN_OEN1_OUT, GP1OEN_OEN2_OUT, GP1OEN_OEN3_OUT, GP1OEN_OEN4_OUT, GP1OEN_OEN5_OUT, GP1OEN_OEN6_OUT, GP1OEN_OEN7_OUT};
uint32_t bar1in[] = {GP1OEN_OEN0_IN, GP1OEN_OEN1_IN, GP1OEN_OEN2_IN, GP1OEN_OEN3_IN, GP1OEN_OEN4_IN, GP1OEN_OEN5_IN, GP1OEN_OEN6_IN, GP1OEN_OEN7_IN};
uint32_t bar2out[] = {GP2OEN_OEN0_OUT, GP2OEN_OEN1_OUT, GP2OEN_OEN2_OUT, GP2OEN_OEN3_OUT, GP2OEN_OEN4_OUT, GP2OEN_OEN5_OUT, GP2OEN_OEN6_OUT, GP2OEN_OEN7_OUT};
uint32_t bar2in[] = {GP2OEN_OEN0_IN, GP2OEN_OEN1_IN, GP2OEN_OEN2_IN, GP2OEN_OEN3_IN, GP2OEN_OEN4_IN, GP2OEN_OEN5_IN, GP2OEN_OEN6_IN, GP2OEN_OEN7_IN};

//Write Values
uint32_t bar0low[] = {GP0OUT_OUT0_LOW, GP0OUT_OUT1_LOW, GP0OUT_OUT2_LOW, GP0OUT_OUT3_LOW, GP0OUT_OUT4_LOW, GP0OUT_OUT5_LOW, GP0OUT_OUT6_LOW, GP0OUT_OUT7_LOW};
uint32_t bar0high[] = {GP0OUT_OUT0_HIGH, GP0OUT_OUT1_HIGH, GP0OUT_OUT2_HIGH, GP0OUT_OUT3_HIGH, GP0OUT_OUT4_HIGH, GP0OUT_OUT5_HIGH, GP0OUT_OUT6_HIGH, GP0OUT_OUT7_HIGH};

uint32_t bar1low[] = {GP1OUT_OUT0_LOW, GP1OUT_OUT1_LOW, GP1OUT_OUT2_LOW, GP1OUT_OUT3_LOW, GP1OUT_OUT4_LOW, GP1OUT_OUT5_LOW, GP1OUT_OUT6_LOW, GP1OUT_OUT7_LOW};
uint32_t bar1high[] = {GP1OUT_OUT0_HIGH, GP1OUT_OUT1_HIGH, GP1OUT_OUT2_HIGH, GP1OUT_OUT3_HIGH, GP1OUT_OUT4_HIGH, GP1OUT_OUT5_HIGH, GP1OUT_OUT6_HIGH, GP1OUT_OUT7_HIGH};

uint32_t bar2low[] = {GP2OUT_OUT0_LOW, GP2OUT_OUT1_LOW, GP2OUT_OUT2_LOW, GP2OUT_OUT3_LOW, GP2OUT_OUT4_LOW, GP2OUT_OUT5_LOW, GP2OUT_OUT6_LOW, GP2OUT_OUT7_LOW};
uint32_t bar2high[] = {GP2OUT_OUT0_HIGH, GP2OUT_OUT1_HIGH, GP2OUT_OUT2_HIGH, GP2OUT_OUT3_HIGH, GP2OUT_OUT4_HIGH, GP2OUT_OUT5_HIGH, GP2OUT_OUT6_HIGH, GP2OUT_OUT7_HIGH};

uint32_t bar0tgl[] = {GP2TGL_TGL0, GP2TGL_TGL1, GP2TGL_TGL2, GP2TGL_TGL3, GP2TGL_TGL4, GP2TGL_TGL5, GP2TGL_TGL6, GP2TGL_TGL7};
uint32_t bar1tgl[] = {GP1TGL_TGL0, GP1TGL_TGL1, GP1TGL_TGL2, GP1TGL_TGL3, GP1TGL_TGL4, GP1TGL_TGL5, GP1TGL_TGL6, GP1TGL_TGL7};
uint32_t bar2tgl[] = {GP2TGL_TGL0, GP2TGL_TGL1, GP2TGL_TGL2, GP2TGL_TGL3, GP2TGL_TGL4, GP2TGL_TGL5, GP2TGL_TGL6, GP2TGL_TGL7};

char modes[3][8];
int outputs[3][8];

uint32_t getModeForPin(int bar, int pin, char mode){

	switch(bar){

		case 0:
			if(mode == OUT)
				return bar0out[pin];
			else
				return bar0in[pin];
		case 1:
				if(mode == OUT)
					return bar0out[pin];
				else
					return bar0in[pin];
		case 2:
				if(mode == OUT)
					return bar0out[pin];
				else
					return bar0in[pin];
		default:
			return 0;

	}

}

uint32_t getPowerForPin(int bar, int pin, int power){

	switch(bar){

		case 0:
			if(power == LOW)
				return bar0low[pin];
			else
				return bar0high[pin];
		case 1:
			if(power == LOW)
				return bar1low[pin];
			else
				return bar1high[pin];
		case 2:
			if(power == LOW)
				return bar2low[pin];
			else
				return bar2high[pin];
		default:
			return 0;

	}

}

uint32_t getToggleForPin(int bar, int pin){

   switch(bar){

      case 0:
         return bar0tgl[pin];
      case 1:
         return bar1tgl[pin];
      case 2:
         return bar2tgl[pin];
      default:
         return 0;

   }

}

void DIO::setMode(int bar, int pin, char mode){

	modes[bar][pin] = mode;

	uint32_t oendata = 0;

	for(int i = 0; i < 8; i++){

		oendata = oendata | getModeForPin(bar, i, modes[bar][i]);

	}

	ADI_GPIO_TypeDef* b = bars[bar];
	DioOen(b, oendata);

}

void DIO::digitalWrite(int bar, int pin, int power){

	if(modes[bar][pin] == OUT)
		outputs[bar][pin] = power;

	uint32_t outdata = 0;

	for(int i = 0; i < 8; i++){

		outdata = outdata | getPowerForPin(bar, i, outputs[bar][i]);

	}

	ADI_GPIO_TypeDef* b = bars[bar];
	DioWr(b, outdata);

}

string toBinaryString( unsigned long n ){

  string result;

  do result.push_back( '0' + (n & 1) );
  while (n >>= 1);

  reverse( result.begin(), result.end() );

  return result;

}

int DIO::digitalRead(int bar, int pin){

	uint32_t i = DioRd(bars[bar]);
	string data = toBinaryString(i);

	char c = data.at(7 - pin); //P0_4 LOW == 11101111
	                           //P0_5 LOW == 11110111

	if(c == '1')
	   return HIGH;
	else
	   return LOW;

}

void DIO::digitalToggle(int bar, int pin){

   DioTgl(bars[bar], getToggleForPin(bar, pin));

}
