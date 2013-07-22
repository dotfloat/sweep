
#include <sweep.h>

extern sgGame_t game;

int sReveal(int x, int y){
    sgReveal(game, x, y);
    
    return 0;
}

int sToggleFlag(int x, int y){
    sgToggleFlag(game, x, y);
}