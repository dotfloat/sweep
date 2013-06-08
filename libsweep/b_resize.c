
#include <stdlib.h>

#include <sweep.h>
#include "b_private.h"

sbBoard_t sbResize(sbBoard_t board, uint16_t width, uint16_t height){
    if(width<sbMinWidth() || width>sbMaxWidth() || height<sbMinHeight() || height>sbMaxHeight())
    {
        /* Push error about incorrect width/height */
        return 0;
    }

    board->map = realloc(board->map, sizeof(sbCell_t)*width*height);
    board->width = width;
    board->height = height;
    sbReset(board);

    return board;
}