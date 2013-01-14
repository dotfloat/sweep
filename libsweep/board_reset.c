
#include <stdlib.h>
#include <memory.h>

#include "board_priv.h"

int sbResize(sbBoard board, uint16_t width, uint16_t height)
{
    if(width<sbMinWidth() || width>sbMaxWidth() || height<sbMinHeight() || height>sbMaxHeight())
    {
        smPushError(smErrBoardSize);
        return 0;
    }

    board->_map = realloc(board->_map, sizeof(sbCell)*width*height);
    if(!board->_map)
    {
        smPushError(smErrRealloc);
        return 0;
    }
    board->_width = width;
    board->_height = height;

    return sbReset(board);
}

int sbReset(sbBoard board)
{
    memset(board->_map, sbCEmpty|sbCClosed, sizeof(sbCell)*board->_width*board->_height);
    board->_bombs = 0;
    board->_seed = 0;
    board->_state = sbStNone;

    return 1;
}
