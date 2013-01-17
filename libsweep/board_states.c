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

sbState sbGetState(sbBoard board)
{
    return board->_state;
}

int sbSpecState(sbBoard board, sbState state)
{
    return board->_state&state;
}

void sbSetState(sbBoard board, sbState state, int enable)
{
    if(enable)
        board->_state -= board->_state&state;
    else
        board->_state |= state;
}
