#include <string>
#include <cstring>

#define PIN12 12
#define PIN67 67

using namespace std;

class Serial{
   long rate;
	public:
		void begin(long buadRate);
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
		void setPins(int pins);
};
