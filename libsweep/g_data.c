
#include "g_private.h"

uint16_t sweepGetWidth(sweep_t g){
    return sweepBoardWidth(g->board);
}

uint16_t sweepGetHeight(sweep_t g){
    return sweepBoardHeight(g->board);
}

sweep_board_t sweepGetBoard(sweep_t g){
    return g->board;
}