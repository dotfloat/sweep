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

#ifndef MAIN_ENUM_H
#define MAIN_ENUM_H

typedef enum
{
    smErrOK         = 0x00,
    smErrMalloc     = 0x01,
    smErrRealloc    = 0x02,

    smErrBoardSize  = 0x03,
    smErrBoardBombs = 0x04,
    smErrBoardOutOfBounds = 0x05,
    smErrBoardRevealAroundClosed = 0x06,
    smErrBoardRevealAroundNotEnough = 0x07,

    smErrorLast,
} smError;

typedef enum
{
    ERR_INFO,
    ERR_WARN,
    ERR_FATAL,
} smSeverity;

#endif // MAIN_ENUM_H
