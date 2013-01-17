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
#include <time.h>

#include "board_priv.h"

int _sbPopulate(sbBoard board, uint32_t bombs, uint32_t seed, char safe, uint16_t x, uint16_t y);

int sbPopulate(sbBoard board, uint32_t bombs)
{
    return _sbPopulate(board, bombs, time(NULL), 0, 0, 0);
}

int sbPopulateSafe(sbBoard board, uint32_t bombs, uint16_t x, uint16_t y)
{
    return _sbPopulate(board, bombs, time(NULL), 1, x, y);
}

int sbPopulateFromSeed(sbBoard board, uint32_t bombs, uint32_t seed)
{
    return _sbPopulate(board, bombs, seed, 0, 0, 0);
}

int sbPopulateSafeFromSeed(sbBoard board, uint32_t bombs, uint32_t seed, uint16_t x, uint16_t y)
{
    return _sbPopulate(board, bombs, seed, 1, x, y);
}

int _sbPopulate(sbBoard board, uint32_t bombs, uint32_t seed, char safe, uint16_t X, uint16_t Y)
{
    srand(seed);
    if(bombs < sbMinBombs(board) || bombs > sbMaxBombs(board))
    {
        smPushError(smErrBoardBombs);
        return 0;
    }
    int x, y, i;

    // shuffle
    for(i=0; i<bombs; i++)
    {
        do
        {
            x = rand() % board->_width;
            y = rand() % board->_height;
        } while(safe&&x>=X-1&&x<=X+1&&y>=Y-1&&y<=Y+1);

        board->_map[y*board->_width+x] = sbCBomb | sbCClosed;
    }

    // gen numbers
    for(y=0; y<board->_height; y++)
        for(x=0; x<board->_width; x++)
        {
            #define BOMBINC(mx, my) \
                if(x>=mx&&y>=my&&(x-mx)<board->_width&&(y-my)<board->_height&&(board->_map[(y-my)*board->_width+x-mx]&0xf)!=sbCBomb) \
                board->_map[(y-my)*board->_width+x-mx]++;

            if((board->_map[y*board->_width+x]&0xf)!=sbCBomb) continue;

            BOMBINC(1, 1)
            BOMBINC(1, -1)
            BOMBINC(-1, 1)
            BOMBINC(-1, -1)

            BOMBINC(1, 0)
            BOMBINC(0, 1)
            BOMBINC(-1, 0)
            BOMBINC(0, -1)
        }

    board->_bombs = bombs;
    board->_seed = seed;

    return 1;
}
