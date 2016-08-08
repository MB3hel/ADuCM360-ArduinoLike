#ifndef __DIO_H__
#define __DIO_H__

#define HIGH 1
#define LOW 0
#define NO_OUT -1

#define OUT 'O'
#define IN 'I'
#define NONE 'N'

class DIO{

public:
	void setMode(int bar, int pin, char mode);
	void digitalWrite(int bar, int pin, int power);
	int digitalRead(int bar, int pin);
	void digitalToggle(int bar, int pin);

};

#endif
