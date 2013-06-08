
#include <memory.h>
#include <stdlib.h>

#include <sweep.h>
#include "b_private.h"

uint16_t sbGetWidth(sbBoard_t board){
    return board->width;
}

uint16_t sbGetHeight(sbBoard_t board){
    return board->height;
}

sbLinear_t sbCellLinearize(sbCell_t c){
        if(S_20(c) == SB_OPEN) return S_1(c);
        return SB_L_CLOSED + S_2(c) - 1;
}

sbCell_t *sbAllocMap(sbBoard_t board){
    return malloc(sizeof(sbCell_t) * board->width * board->height);
}

sbCell_t sbGetCellRaw(sbBoard_t board, uint16_t x, uint16_t y){
    return board->map[y*board->width+x];
}

sbLinear_t sbGetCellVisible(sbBoard_t board, uint16_t x, uint16_t y){
    sbCell_t c = board->map[y*board->width+x];
    return sbCellLinearize(c);
}

sbCell_t sbGetCellFlags(sbBoard_t board, uint16_t x, uint16_t y){
    return S_20(board->map[y*board->width+x]);
}

int sbGetDataRaw(sbBoard_t board, sbCell_t *map){
    memcpy(map, board->map, sizeof(sbCell_t) * board->width * board->height);
    return S_TRUE;
}

int sbGetDataVisible(sbBoard_t board, sbLinear_t *map){
    int x, y;
    sbCell_t c;
    size_t s;
    for(y=0; y<board->height; y++) {
        for(x=0; x<board->width; x++) {
            s = y*board->width+x;
            c = board->map[s];
            map[s] = sbCellLinearize(c);
        }
    }
    
    return 0;
}

int sbGetDataFlags(sbBoard_t board, sbCell_t *map){
    int x, y;
    sbCell_t c;
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

void sbSetCellRaw(sbBoard_t board, sbCell_t cell, uint16_t x, uint16_t y){
    board->map[y*board->width+x] = cell;
}

/* need to fix mark stuff */
/*void sbToggleFlag(sbBoard_t board, uint16_t x, uint16_t y)
{
    sbCell_t *c = &board->_map[y*board->_width+x];
    if(((*c)&0xf0)==sbCClosed)
        *c = sbCFlag | ((*c)&0xf);
    else if(((*c)&0xf0)==sbCFlag && (board->state&sbStMark))
        *c = SB_MARK | ((*c)&0xf);
    else *c = SB_CLOSED | ((*c)&0xf);
}*/

#define COUNTNEIGHBOURS(mx, my) if(x>=mx&&y>=my&&(x-mx)<board->width&&(y-my)<board->height) {\
        c = board->map[(y-my)*board->width+x-mx]; if(S_20(c)==SB_OPEN||S_20(c)==SB_FLAG||S_20(c)==SB_MARK) n++; }

int sbCountNeighbors(sbBoard_t board, uint16_t x, uint16_t y){
    int n = 0;
    sbCell_t c;

    COUNTNEIGHBOURS(1, 1)
    COUNTNEIGHBOURS(1, -1)
    COUNTNEIGHBOURS(-1, 1)
    COUNTNEIGHBOURS(-1, -1)

    COUNTNEIGHBOURS(1, 0)
    COUNTNEIGHBOURS(0, 1)
    COUNTNEIGHBOURS(-1, 0)
    COUNTNEIGHBOURS(0, -1)

    return n;
}