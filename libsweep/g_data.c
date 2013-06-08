
#include "g_private.h"

uint16_t sgGetWidth(sgGame_t g){
    return sbGetWidth(g->board);
}

uint16_t sgGetHeight(sgGame_t g){
    return sbGetHeight(g->board);
}

sbBoard_t sgGetBoard(sgGame_t g){
    return g->board;
}