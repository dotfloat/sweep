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

#ifndef SWEEP_H
#define SWEEP_H

#ifdef _WIN32
# define SWEEP_EXPORT __declspec(dllimport)
#else
# define SWEEP_EXPORT extern
#endif

#include <stdint.h>

#include "version.h"
//#include "game.h"
#include "board.h"
#include "main.h"

#endif // SWEEP_H
