
#include <stdio.h>

#include <sweep.h>

int main(int argc, char *argv[]){
	sInit();

	const char *s = sFindGlobalConfig(NULL);

	printf("%s\n", s?s:"<nil>");

	return 0;
}