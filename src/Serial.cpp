#include "Serial.h"
#include <string>
#include <cstring>
#include <stdlib.h>

#define CTRL_C_ 	    3
#define BS_       	 8
#define TAB_    		 9
#define CR_     		 13
#define LF_       	 10
#define SPC_          32
#define SP_           127

using namespace std;

extern "C"{

	#include "Communication.h"
	//#include "UrtLib.h"

}

void intHandeler(void){

	unsigned short  status;
		char c;

		status = UrtIntSta(pADI_UART);

		if (status & COMIIR_NINT)
			return;

		switch (status & COMIIR_STA_MSK) {

			case COMIIR_STA_RXBUFFULL:
				UART_ReadChar(&c);

				uart_rx_buffer[uart_rcnt++] = c;
				if (uart_rcnt == UART_RX_BUFFER_SIZE) {

					uart_rcnt--;
					UART_WriteChar(BS_, UART_WRITE_IN_INT);

				}

				UART_WriteChar(c, UART_WRITE_IN_INT);

				break;

			case COMIIR_STA_TXBUFEMPTY:
				if (uart_tcnt) {

					uart_tbusy = UART_TRUE;
					uart_tcnt--;
					UART_WriteChar(uart_tx_buffer[uart_tpos++], UART_WRITE);

					if (uart_tpos == UART_TX_BUFFER_SIZE) {

						uart_tpos = 0;

					}

				} else {

					uart_tbusy = UART_FALSE;

				}
				break;

			default:
				break;

		}

}


extern "C"{

	void UART_Int_Handler (void){

		intHandeler();

	}

}

int Serial::isInitilized(){

	return initilized;

}

void Serial::begin(long buadRate, int pins){

   rate = buadRate;
   initilized = pins;

   UART_Init(buadRate, COMLCR_WLS_8BITS, pins);

}

int Serial::available(){

	return uart_rcnt;

}

char Serial::read(){

	uart_rcnt--;
	uart_rx_buffer[uart_rcnt] = 0;

	return uart_rx_buffer[sizeof(uart_rx_buffer) - 1];

}

void Serial::print(char c){

	UART_WriteChar(c, UART_WRITE_IN_INT);

}

void Serial::print(string s){

	char *cstr = new char[s.length() + 1];
	strcpy(cstr, s.c_str());

	UART_WriteString(cstr);

}

void Serial::print(char *cs){

	UART_WriteString(cs);

}

void Serial::println(char c){

	UART_WriteChar(c, UART_WRITE_IN_INT);
	UART_WriteString("\r\n");

}

void Serial::println(string s){

	char *cstr = new char[s.length() + 1];
	strcpy(cstr, s.c_str());

	UART_WriteString(cstr);
	UART_WriteString("\r\n");

}

void Serial::println(char *cs){

	UART_WriteString(cs);
	UART_WriteString("\r\n");

}

void Serial::println(){

	UART_WriteString("\r\n");

}

void Serial::print(int i){

	char buf[20];
	itoa(i, buf, 10);
	UART_WriteString(buf);

}

void Serial::println(int i){

	char buf[20];
	itoa(i, buf, 10);
	UART_WriteString(buf);
	UART_WriteString("\r\n");

}
