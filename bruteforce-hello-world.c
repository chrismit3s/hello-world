#include<stdbool.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<unistd.h>

#define DELAY		15
#define PRINTABLE	"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz!§$%&/=?#*+-"

void typewrite_char(unsigned char c);
int get_random(int min, int max);

int main(void){
	char *p, str[] = "Hello world!";

	for(p = str; *p != 0; ++p)
		typewrite_char(*p);
	printf("\n");

	return EXIT_SUCCESS;
}

void typewrite_char(unsigned char c){
	//check if its a printable char
	if(strchr(PRINTABLE, c) == NULL){
		printf("%c", c);
		return;
	}

	//generate random chars until its a hit
	unsigned char r;
	printf(" ");
	while((r = PRINTABLE[get_random(0, strlen(PRINTABLE) - 1)]) != c){
		printf("\b%c", r);
		fflush(stdout);
		usleep(DELAY * 1000);
	}
	printf("\b%c", c);

	return;
}
int get_random(int min, int max){
	// initalize rand()
	static bool seed_set = false;
	if(!seed_set){
		srand(time(NULL));
		seed_set = true;
	}

	return min + rand() / (RAND_MAX / (max - min + 1) + 1);
}
