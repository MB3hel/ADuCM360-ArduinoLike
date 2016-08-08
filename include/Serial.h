#include <string>
#include <cstring>

#define PIN12 12
#define PIN67 67

#include <sstream>

#define ToString( x ) static_cast< std::ostringstream & >( \
        ( std::ostringstream() << std::dec << x ) ).str()

using namespace std;

class Serial{
   long rate;
   int initilized = -1;
	public:
   	int isInitilized();
		void begin(long buadRate, int pins);
		int available();
		char read();
		void print(char c);
		void print(string s);
		void print(char *cs);
		void println(char c);
		void println(string s);
		void println(char *cs);
		void println();
		void print(int i);
		void println(int i);

};
