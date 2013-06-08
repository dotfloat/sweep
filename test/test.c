
#include <stdio.h>

#include <sweep.h>

int main(int argc, char *argv[]){
	sInit(&argc, argv);
        
        S_BOOL quit = S_FALSE;
        sState_t state;
        
        sDebugDumpBoard(stdout);
        
        while(!quit) {
            state = sGetState();
            
            switch(state) {
                case S_STATE_GAME:
//                    sDebugDumpBoardVisible();
                    break;
                case S_STATE_QUIT:
                    quit = S_TRUE;
                    break;
                default:
                    break;
            }
        }
        sQuit();

	return 0;
}