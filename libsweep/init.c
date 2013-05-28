
#include <stdio.h>

#include <sweep.h>

int __sInit(short maj, short min, short rev){

	/* check for correct version */
	
	printf("Welcome from libsweep version %d.%d-%d\n", maj, min, rev);

	return S_TRUE;
}

void sQuit(void){

	/* do something */
}