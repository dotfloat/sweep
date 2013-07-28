
#include <stdlib.h>
#include <string.h>

#include <sweep.h>
#include "b_private.h"

uint16_t sweepBoardWidth(sweep_board_t board){
    return board->width;
}

uint16_t sweepBoardHeight(sweep_board_t board){
    return board->height;
}

sweep_linear_t sweepBoardCellLinearize(sweep_cell_t c){
    if(S_20(c) == SWEEP_OPEN) return S_1(c);
    return SWEEP_L_CLOSED + S_2(c) - 1;
}

sweep_cell_t *sweepBoardAllocMap(sweep_board_t board){
    return malloc(sizeof(sweep_cell_t)*board->width*board->height);
}

sweep_cell_t sweepBoardCellRaw(sweep_board_t board, uint16_t x, uint16_t y){
    return board->map[y*board->width+x];
}

sweep_linear_t sweepBoardCellVisible(sweep_board_t board, uint16_t x, uint16_t y){
    sweep_cell_t c = board->map[y*board->width+x];
    return sweepBoardCellLinearize(c);
}

sweep_cell_t sweepBoardCellFlags(sweep_board_t board, uint16_t x, uint16_t y){
    return S_20(board->map[y*board->width+x]);
}

int sweepBoardDataRaw(sweep_board_t board, sweep_cell_t *map){
    memcpy(map, board->map, sizeof(sweep_cell_t)*board->width*board->height);
    return S_TRUE;
}

int sweepBoardDataVisible(sweep_board_t board, sweep_linear_t *map){
    int x, y;
    sweep_cell_t c;
    size_t s;
    for(y=0; y<board->height; y++) {
        for(x=0; x<board->width; x++) {
            s = y*board->width+x;
            c = board->map[s];
            map[s] = sweepBoardCellLinearize(c);
        }
    }
    
    return 0;
}

int sweepBoardDataFlags(sweep_board_t board, sweep_cell_t *map){
    int x, y;
    sweep_cell_t c;
    size_t s;
    for(y=0; y<board->height; y++) {
        for(x=0; x<board->width; x++) {
            s = y*board->width+x;
            c = board->map[s];
            map[s] = S_20(c);
        }
    }
    
    return 0;
}

void sweepBoardSetCellRaw(sweep_board_t board, sweep_cell_t cell, uint16_t x, uint16_t y){
    board->map[y*board->width+x] = cell;
}

/* need to fix mark stuff */
void sweepBoardToggleFlag(sweep_board_t board, uint16_t x, uint16_t y)
{
    sweep_cell_t c = board->map[y*board->width+x];
    if(S_20(c) == SWEEP_CLOSED) {
        c = SWEEP_FLAG | S_1(c);
    } else if(S_20(c) == SWEEP_FLAG && board->mark) {
        c = SWEEP_MARK | S_1(c);
    } else if(S_20(c) == SWEEP_FLAG || S_20(c) == SWEEP_MARK) {
        c = SWEEP_CLOSED | S_1(c);
    }
    board->map[y*board->width+x] = c;
}
int sweepBoardCountNeighbors(sweep_board_t board, uint16_t x, uint16_t y){
    int n = 0;

    #define X(Sx, Sy, Px, Py) \
        sweep_cell_t c = board->map[ Py*Sx + Px ]; \
        if(S_20(c) == SWEEP_OPEN || S_20(c) == SWEEP_FLAG || S_20(c) == SWEEP_MARK) n++;
    
        SWEEP_XMACRO_local
    #undef X

    return n;
}

S_BOOL sweepBoardHasExploded(sweep_board_t board){
    return board->exploded;
}

S_BOOL sweepBoardHasWon(sweep_board_t board){
    int x, y;
    sweep_cell_t c;
    for(y=0; y<board->height; y++) {
        for(x=0; x<board->width; x++) {
            c = board->map[y*board->width + x];
            if(S_1(c) == SWEEP_BOMB && S_20(c) != SWEEP_OPEN) {
                continue;
            } else if(S_1(c) != SWEEP_BOMB && S_20(c) == SWEEP_OPEN) {
                continue;
            } else {
                return S_FALSE;
            }
        }
    }
    return S_TRUE;
}