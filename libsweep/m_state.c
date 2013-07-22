
#include <sweep.h>

extern sgGame_t game;

sState_t state;

void cbacted(){
    state = S_RENDER;
}

void cbexplode(){
    state = S_LOST;
}

void cbwon(){
    state = S_WON;
}

void sInitStates(void){
    sgSetCBActed(cbacted);
    sgSetCBExplode(cbexplode);
    sgSetCBExplode(cbwon);
    
    state = S_RENDER;
}

sState_t sGetState(void){
    switch(state) {
        case S_RENDER:
            state = S_ACTION;
            return S_RENDER;
            break;
        default:
            return state;
            break;
    }
    return S_QUIT;
}

void sPollQuit(void){
    state = S_QUIT;
}

sbBoard_t sGetBoard(void){
    return sgGetBoard(game);
}