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

#include "main_priv.h"

smErrStrStruct smErrStr[smErrorLast] = {
/* smErrOK */         { "Success", ERR_INFO },
/* smErrMalloc */     { "Malloc failed", ERR_FATAL },
/* smErrRealloc */    { "Realloc failed", ERR_FATAL },
/* smErrBoardSize */  { "Incorrect board size", ERR_WARN },
/* smErrBoardBombs */ { "Incorrect number of bombs", ERR_WARN },
/* smErrBoardOutOfBounds */ { "Out of board bounds", ERR_WARN },
/* smErrBoardRevealAroundClosed */ { "Trying to reveal around a closed cell", ERR_WARN },
/* smErrBoardRevealAroundNotEnough */ { "The number of neighbours around cell is incorrect", ERR_WARN },
};
