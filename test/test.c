
#include <stdio.h>

#include <sweep.h>

int main(int argc, char *argv[]){
	sInit(&argc, argv);
        
        S_BOOL quit = S_FALSE;
        sState_t state;
        
        char buf[256];
        int x, y;
        
        while(!quit) {
            switch(sGetState()) {
                case S_ACTION:
                    printf("> ");
                    gets(buf);
                    if(buf[0] == 'q') {
                        quit = S_TRUE;
                    } else if(buf[0] == 'r') {
                        sscanf(buf+2, "%d %d", &x, &y);
                        sReveal(x, y);
                    } else if(buf[0] == 'f') {
                        sscanf(buf+2, "%d %d", &x, &y);
                        sToggleFlag(x, y);
                    }
                    break;
                case S_RENDER:
                    sDebugDumpBoardVisible(stdout);
                    break;
                case S_WON:
                    printf("Won!\n");
                    break;
                case S_LOST:
                    printf("Lost :(\n");
                    sPollQuit();
                    break;
                case S_QUIT:
                    quit = S_TRUE;
                    break;
                default:
                    break;
            }
        }
        
        sQuit();
        
        printf("Quated\n");

	return 0;
}