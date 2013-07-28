
#include <stdlib.h>

#include <sweep.h>
#include "b_private.h"

sweep_board_t sweepBoardResize(sweep_board_t board, uint16_t width, uint16_t height){
    if(width<sweepMinWidth() || width>sweepMaxWidth() || height<sweepMinHeight() || height>sweepMaxHeight())
    {
        /* Push error about incorrect width/height */
        return 0;
    }

    board->map = realloc(board->map, sizeof(sweep_cell_t)*width*height);
    board->width = width;
    board->height = height;
    sweepBoardReset(board);

    return board;
}