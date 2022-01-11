#include "TP1_2.h"


int main(void)
{
	write(STDOUT_FILENO, BONJOUR, strlen(BONJOUR));
	write(STDOUT_FILENO, SHELL, strlen(SHELL));
	
	exit(EXIT_SUCCESS); 
}

