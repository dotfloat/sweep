
#include <stdlib.h>
#include <memory.h>

#include <sweep.h>
#include "b_private.h"

sweep_board_t sweepBoardInit(uint16_t width, uint16_t height){
    sweep_board_t board = malloc(sizeof(struct __sweep_board_t));
    board->map = NULL;
    if(!(board = sweepBoardResize(board, width, height)))
    {
        free(board);
        return NULL;
    }

    return board;
}

int sweepBoardReset(sweep_board_t board){
    memset(board->map, SWEEP_EMPTY|SWEEP_CLOSED, sizeof(sweep_cell_t)*board->width*board->height);
    board->bombs = 0;
    board->seed = 0;
    
    board->exploded = S_FALSE;
    board->mark = S_FALSE;
    
    return 0;
}

sweep_board_t sweepBoardCopy(sweep_board_t board){
    sweep_board_t copy = malloc(sizeof(struct __sweep_board_t));
    memcpy(copy, board, sizeof(struct __sweep_board_t));

    copy->map = malloc(sizeof(sweep_cell_t)*board->width*board->height);
    memcpy(copy->map, board->map, sizeof(sweep_cell_t)*board->width*board->height);

    return copy;
}

void sweepBoardDestroy(sweep_board_t board){
    if(!board) return;
    free(board->map);
    free(board);
}
