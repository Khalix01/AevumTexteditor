#include <unistd.h>
#include <termios.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

//Constants:
#define CTRL_KEY(key) ((key)& 0x1f ) //defineing macro for ctrl + key

struct termios origin;

void reset(){
	tcsetattr(STDIN_FILENO,TCSAFLUSH,&origin);
}

void end(cost char *error){
	fprintf(stderr,error);
	exit(1);
}

void enableRawInput() {
	struct termios raw;
	if(tcgetattr(STDIN_FILENO,&origin)==-1) end("Getting terminal fail");// storing a copy of default terminal
	atexit(reset);// resseting to default at exit of program

	raw = origin;
	raw.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);// disabling  flags using bit wis e operators
	raw.c_oflag &= ~(OPOST);
	raw.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG);

	raw.c_cflag |= (CS8); // setting character size  to 8

	if(tcsetattr(STDIN_FILENO,TCSAFLUSH,&raw)==-1) end("Setting terminal fail");
}

int main() {
	enableRawMode();
	char c;
	while (read(STDIN_FILENO, &c, 1) == 1 && c != 'q') {
		if (iscntrl(c)) {
			printf("%d\n", c);
		} else {
		printf("%d ('%c')\n", c, c);
		}
	}	
}