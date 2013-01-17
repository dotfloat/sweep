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

#ifndef SWEEP_BOARD_PRIV_H
#define SWEEP_BOARD_PRIV_H

#ifndef SWEEP_EXPORT
# ifdef _WIN32
#  define SWEEP_EXPORT declspec(dllexport)
# else
#  define SWEEP_EXPORT
# endif
#endif

#include <stdint.h>

#include <board.h>
#include <main.h>

#define SWEEP_MINDENSITY 0.13
#define SWEEP_MAXDENSITY 0.63

struct _sbBoard
{
    uint16_t _width;
    uint16_t _height;
    uint32_t _bombs;
    uint32_t _seed;

    sbCell *_map;
    sbState _state;
};

#endif // SWEEP_BOARD_PRIV_H
