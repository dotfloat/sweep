
#include <sys/time.h>

#include <sweep.h>

float sGetTimeSgl(void){
    struct timeval t;
    gettimeofday(&t, 0);

    return (t.tv_sec + (float)t.tv_usec/1000000);
}

double sGetTimeDbl(){
    struct timeval t;
    gettimeofday(&t, 0);

    return (t.tv_sec + (double)t.tv_usec/1000000);
}