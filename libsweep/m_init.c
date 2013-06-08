
#include <stdio.h>

#include <sweep.h>

sgGame_t game = NULL;

int __sInit(int *argc, char **argv, short maj, short min, short rev){
    if(maj != SWEEP_VER_MAJOR || min != SWEEP_VER_MINOR) {
        return S_FALSE;
        /* Add "incompatible libsweep version" to error stack */
    }
    
    sCmdlineParse(argc, argv);
    
    game = sgInit();
    
    sgStart(game, SG_EASY);
    
    

    return S_TRUE;
}

void sQuit(void){
    sgDestroy(game);
    
	/* do something */
}
