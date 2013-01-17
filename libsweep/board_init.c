/**
 *  This file is part of Sweep.
 *
 *  Sweep is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  Sweep is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *  
 *  You should have received a copy of the GNU General Public License
 *  along with Sweep.  If not, see <http://www.gnu.org/licenses/>.
 */

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
