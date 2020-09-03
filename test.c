#include <unistd.h>
#include <termios.h>
#include <stdlib.h>

#define quit 'q'

void reset(struct termios *orgin){
	tcsetattr(STDIN_FILENO,TCSAFLUSH,origin);
}

void enableRawInput() {
	struct termios origin,raw;
	tcgetattr(STDIN_FILENO,&origin);// storing a copy of default terminal
	atexit(reset(&origin));// resseting to default at exit of program

	raw = origin

	raw.c_lflag &=  ~(ECHO| ICANON)//disabling flags using bitwise operators

	tcsetattr(STDIN_FILENO,TCSAFLUSH,&raw);	
}

int main() {
	char c;
	while(read(STDIN_FILENO,&c,1)==1 && c  != quit);
	return 0;	
}