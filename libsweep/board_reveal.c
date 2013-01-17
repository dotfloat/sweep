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

#include "board_priv.h"

typedef struct
{
    uint16_t x;
    uint16_t y;
} sbPx;

#define CHUNKSIZE 32

#define REVEAL(mx, my) a=(p.y-my)*board->_width-p.x-mx;if(p.x>=mx&&p.y>=my&&(p.x-mx)<board->_width&&(p.y-my)<board->_height&&\
    (board->_map[a]&0xf0)==sbCClosed) { board->_map[a] = sbCOpen | (board->_map[a]&0xf); if((board->_map[a]&0xf) == sbCEmpty)\
    { sbPx q = {p.x-mx, p.y-my}; if(!pushStack(&stack, &stackN, q)){free(stack); return 0;} } }

inline int pushStack(sbPx **stack, int *size, sbPx x)
{
    (*size)++;
    if((*size)%CHUNKSIZE==0)
    {
        (*stack) = realloc(*stack, sizeof(sbPx)*(*size));
        if(!(*stack))
        {
            smPushError(smErrRealloc);
            return 0;
        }
    }
    (*stack)[(*size)-1] = x;
    return 1;
}

inline sbPx popStack(sbPx **stack, int *size)
{
    return (*stack)[--(*size)];
}

int sbReveal(sbBoard board, uint16_t x, uint16_t y)
{
    if(x>=board->_width||y>=board->_height)
    {
        smPushError(smErrBoardOutOfBounds);
        return 0;
    }

    board->_map[y*board->_width+x] = sbCOpen | (board->_map[y*board->_width+x]&0xf);

    if((board->_map[y*board->_width+x]&0xf) != sbCEmpty)
        return 1;

    sbPx *stack = malloc(sizeof(sbPx)*CHUNKSIZE);
    sbPx p;
    int a, stackN = 1;
    stack->x = x;
    stack->y = y;

    while(stackN)
    {
        p = popStack(&stack, &stackN);

        REVEAL(1, 1)
        REVEAL(1, -1)
        REVEAL(-1, 1)
        REVEAL(-1, -1)

        REVEAL(1, 0)
        REVEAL(0, 1)
        REVEAL(-1, 0)
        REVEAL(0, -1)
    }

    free(stack);

    return 1;
}

#define REVEALAROUND(mx, my) if(x>=mx&&y>=my&&(x-mx)<board->_width&&(y-my)<board->_height) sbReveal(board, x-mx, y-my);

int sbRevealAround(sbBoard board, uint16_t x, uint16_t y)
{
    if(x>=board->_width||y>=board->_height)
    {
        smPushError(smErrBoardOutOfBounds);
        return 0;
    }

    REVEALAROUND(1, 1)
    REVEALAROUND(1, -1)
    REVEALAROUND(-1, 1)
    REVEALAROUND(-1, -1)

    REVEALAROUND(1, 0)
    REVEALAROUND(0, 1)
    REVEALAROUND(-1, 0)
    REVEALAROUND(0, -1)

    return 1;
}

int sbRevealAroundStrict(sbBoard board, uint16_t x, uint16_t y)
{
    int n = sbCountNeighbors(board, x, y);
    char c = sbGetCellVisible(board, x, y);
    if(c&0xf0)
    {
        smPushError(smErrBoardRevealAroundClosed);
        return 0;
    }

    if(n == c)
        return sbRevealAround(board, x, y);
    smPushError(smErrBoardRevealAroundNotEnough);
    return 0;
}

int sbRevealBombs(sbBoard board)
{
    uint32_t i;
    for(i=0; i<board->_width*board->_height; i++)
    {
        switch(board->_map[i]&0xf0)
        {
            case sbCMark:
            case sbCFlag:
                if((board->_map[i]&0xf)==sbCBomb)
                    board->_map[i] = sbCOpen | sbCCorrect;
                else board->_map[i] = sbCOpen | sbCIncorrect;
                break;
            default:
                break;
        }
    }

    return 1;
}

int sbRevealAll(sbBoard board)
{
    uint32_t i;
    for(i=0; i<board->_width*board->_height; i++)
    {
        switch(board->_map[i]&0xf0)
        {
            case sbCMark:
            case sbCFlag:
                if((board->_map[i]&0xf)==sbCBomb)
                    board->_map[i] = sbCOpen | sbCCorrect;
                else board->_map[i] = sbCOpen | sbCIncorrect;
                break;
            default:
                board->_map[i] = sbCOpen | (board->_map[i]&0xf);
                break;
        }
    }
    return 1;
}
