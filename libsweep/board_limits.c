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

uint32_t sbMinBombs(sbBoard board)
{
    return (double)SWEEP_MINDENSITY*board->_width*board->_height;
}

uint32_t sbMaxBombs(sbBoard board)
{
    return (double)SWEEP_MAXDENSITY*board->_width*board->_height;
}

uint32_t sbMinBombsXY(uint16_t x, uint16_t y)
{
    return (double)SWEEP_MINDENSITY*x*y;
}

uint32_t sbMaxBombsXY(uint16_t x, uint16_t y)
{
    return (double)SWEEP_MAXDENSITY*x*y;
}

uint16_t sbMinWidth(void)
{
    return 9;
}

uint16_t sbMaxWidth(void)
{
    return 16384;
}

uint16_t sbMinHeight(void)
{
    return 9;
}

uint16_t sbMaxHeight(void)
{
    return 12288;
}
