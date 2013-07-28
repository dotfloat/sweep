
#include "b_private.h"

#define MIN_DENSITY (float)0.10
#define MAX_DENSITY (float)0.63

uint32_t sweepMinBombs(sweep_board_t board){
    return MIN_DENSITY*board->width*board->height;
}

uint32_t sweepMaxBombs(sweep_board_t board){
    return MAX_DENSITY*board->width*board->height;
}

uint32_t sweepMinBombsXY(uint16_t x, uint16_t y){
    return MIN_DENSITY*x*y;
}

uint32_t sweepMaxBombsXY(uint16_t x, uint16_t y){
    return MAX_DENSITY*x*y;
}

uint16_t sweepMinWidth(void){
    return 9;
}

uint16_t sweepMaxWidth(void){
    return 16384;
}

uint16_t sweepMinHeight(void){
    return 9;
}

uint16_t sweepMaxHeight(void){
    return 12288;
}