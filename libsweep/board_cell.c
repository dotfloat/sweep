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

#include "board_priv.h"

sbCell sbGetCellRaw(sbBoard board, uint16_t x, uint16_t y)
{
    return board->_map[y*board->_width+x];
}

sbLinear sbGetCellVisible(sbBoard board, uint16_t x, uint16_t y)
{
    sbCell c = board->_map[y*board->_width+x];
    if((c&0xf0)==sbCOpen) return (sbLinear) c&0xf;
    return (sbLinear) ((c&0xf0)>>4)+sbCFirstNybble-1;
}

sbCell sbGetCellFlags(sbBoard board, uint16_t x, uint16_t y)
{
    return board->_map[y*board->_width+x]&0xf0;
}

sbCell *sbGetDataRaw(sbBoard board)
{
    return board->_map;
}

sbLinear *sbGetDataVisible(sbBoard board)
{
    return (void *) 0;
}

sbCell *sbGetDataFlags(sbBoard board)
{
    return (void *) 0;
}

void sbSetCellRaw(sbBoard board, sbCell cell, uint16_t x, uint16_t y)
{
    board->_map[y*board->_width+x] = cell;
}

void sbToggleFlag(sbBoard board, uint16_t x, uint16_t y)
{
    sbCell *c = &board->_map[y*board->_width+x];
    if(((*c)&0xf0)==sbCClosed)
        *c = sbCFlag | ((*c)&0xf);
    else if(((*c)&0xf0)==sbCFlag && (board->_state&sbStMark))
        *c = sbCMark | ((*c)&0xf);
    else *c = sbCClosed | ((*c)&0xf);
}

#define COUNTNEIGHBOURS(mx, my) if(x>=mx&&y>=my&&(x-mx)<board->_width&&(y-my)<board->_height) {\
        c = board->_map[(y-my)*board->_width+x-mx]; if((c&0xf0)==sbCOpen||(c&0xf0)==sbCFlag||(c&0xf0)==sbCMark) n++; }

int sbCountNeighbors(sbBoard board, uint16_t x, uint16_t y)
{
    int n = 0;
    sbCell c;

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
