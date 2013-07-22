
#include <sweep.h>
#include "g_private.h"

void __dummy(void){
}

sgCallback_t CB_exploded = __dummy;
sgCallback_t CB_acted = __dummy;
sgCallback_t CB_won = __dummy;

void sgSetCBExplode(sgCallback_t callback){
    CB_exploded = callback;
}

void sgSetCBActed(sgCallback_t callback){
    CB_acted = callback;
}

void sgSetCBWon(sgCallback_t callback){
    CB_won = callback;
}