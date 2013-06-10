
#include <stdlib.h>
#include <memory.h>

#include <sweep.h>
#include "b_private.h"

sbBoard_t sbInit(uint16_t width, uint16_t height){
    sbBoard_t board = malloc(sizeof(struct __sbBoard_t));
    board->map = NULL;
    if(!(board = sbResize(board, width, height)))
    {
        sbDestroy(board);
        return NULL;
    }

    return board;
}

int sbReset(sbBoard_t board){
    memset(board->map, SB_EMPTY|SB_CLOSED, sizeof(sbCell_t)*board->width*board->height);
    board->bombs = 0;
    board->seed = 0;
    
    board->exploded = S_FALSE;
    board->mark = S_FALSE;
    
    return 0;
}

sbBoard_t sbCopy(sbBoard_t board){
    sbBoard_t copy = malloc(sizeof(struct __sbBoard_t));
    memcpy(copy, board, sizeof(struct __sbBoard_t));

    copy->map = malloc(sizeof(sbCell_t)*board->width*board->height);
    memcpy(copy->map, board->map, sizeof(sbCell_t)*board->width*board->height);

    return copy;
}

void sbDestroy(sbBoard_t board){
    if(!board) return;
    free(board->map);
    free(board);
}
