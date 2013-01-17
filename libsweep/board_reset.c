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
