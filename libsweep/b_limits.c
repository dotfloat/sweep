
#include "b_private.h"

#define MIN_DENSITY (float)0.10
#define MAX_DENSITY (float)0.63

uint32_t sbMinBombs(sbBoard_t board){
    return MIN_DENSITY*board->width*board->height;
}

uint32_t sbMaxBombs(sbBoard_t board){
    return MAX_DENSITY*board->width*board->height;
}

uint32_t sbMinBombsXY(uint16_t x, uint16_t y){
    return MIN_DENSITY*x*y;
}

uint32_t sbMaxBombsXY(uint16_t x, uint16_t y){
    return MAX_DENSITY*x*y;
}

uint16_t sbMinWidth(void){
    return 9;
}

uint16_t sbMaxWidth(void){
    return 16384;
}

uint16_t sbMinHeight(void){
    return 9;
}

uint16_t sbMaxHeight(void){
    return 12288;
}
