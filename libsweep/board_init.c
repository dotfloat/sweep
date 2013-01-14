
#include <stdlib.h>
#include <memory.h>

#include "board_priv.h"

sbBoard sbCreate(uint16_t width, uint16_t height)
{
    sbBoard board = malloc(sizeof(struct _sbBoard));
    if(!board)
    {
        smPushError(smErrMalloc);
        return NULL;
    }
    board->_map = NULL;
    if(!sbResize(board, width, height))
    {
        sbFree(board);
        return NULL;
    }

    return board;
}

sbBoard sbCopy(sbBoard board)
{
    sbBoard copy = malloc(sizeof(struct _sbBoard));
    if(!board)
    {
        smPushError(smErrMalloc);
        return NULL;
    }
    memcpy(copy, board, sizeof(struct _sbBoard));

    copy->_map = malloc(sizeof(sbCell)*board->_width*board->_height);
    if(!copy->_map)
    {
        smPushError(smErrMalloc);
        return NULL;
    }
    memcpy(copy->_map, board->_map, sizeof(sbCell)*board->_width*board->_height);

    return copy;
}

void sbFree(sbBoard board)
{
    free(board->_map);
    free(board);
}
