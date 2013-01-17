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

#ifndef SWEEP_BOARD_H
#define SWEEP_BOARD_H

struct _sbBoard;
typedef struct _sbBoard * sbBoard;

#include "board_enum.h"

/* (de)initialise */
SWEEP_EXPORT sbBoard     sbCreate(uint16_t width, uint16_t height);
SWEEP_EXPORT sbBoard     sbCopy(sbBoard board);
SWEEP_EXPORT void        sbFree(sbBoard board);

/* reset */
SWEEP_EXPORT int         sbResize(sbBoard board, uint16_t width, uint16_t height);
SWEEP_EXPORT int         sbReset(sbBoard board);

/* populate */
SWEEP_EXPORT int        sbPopulate(sbBoard board, uint32_t bombs);
SWEEP_EXPORT int        sbPopulateSafe(sbBoard board, uint32_t bombs, uint16_t x, uint16_t y);
SWEEP_EXPORT int        sbPopulateFromSeed(sbBoard board, uint32_t bombs, uint32_t seed);
SWEEP_EXPORT int        sbPopulateSafeFromSeed(sbBoard board, uint32_t bombs, uint32_t seed, uint16_t x, uint16_t y);

/* reveal */
SWEEP_EXPORT int         sbReveal(sbBoard board, uint16_t x, uint16_t y);
SWEEP_EXPORT int         sbRevealAround(sbBoard board, uint16_t x, uint16_t y);
SWEEP_EXPORT int         sbRevealAroundStrict(sbBoard board, uint16_t x, uint16_t y);
SWEEP_EXPORT int         sbRevealBombs(sbBoard board);
SWEEP_EXPORT int         sbRevealAll(sbBoard board);

/* cell data */
SWEEP_EXPORT sbCell      sbGetCellRaw(sbBoard board, uint16_t x, uint16_t y);
SWEEP_EXPORT sbLinear    sbGetCellVisible(sbBoard board, uint16_t x, uint16_t y);
SWEEP_EXPORT sbCell      sbGetCellFlags(sbBoard board, uint16_t x, uint16_t y);
SWEEP_EXPORT sbCell *    sbGetDataRaw(sbBoard board);
SWEEP_EXPORT sbLinear *  sbGetDataVisible(sbBoard board);
SWEEP_EXPORT sbCell *    sbGetDataFlags(sbBoard board);
SWEEP_EXPORT void        sbSetCellRaw(sbBoard board, sbCell cell, uint16_t x, uint16_t y);
SWEEP_EXPORT void        sbToggleFlag(sbBoard board, uint16_t x, uint16_t y);
SWEEP_EXPORT int         sbCountNeighbors(sbBoard board, uint16_t x, uint16_t y);

/* states */
SWEEP_EXPORT sbState     sbGetState(sbBoard board);
SWEEP_EXPORT int         sbSpecState(sbBoard board, sbState stlsate);
SWEEP_EXPORT void        sbSetState(sbBoard board, sbState state, int enable);

/* limits */
SWEEP_EXPORT uint32_t    sbMinBombs(sbBoard board);
SWEEP_EXPORT uint32_t    sbMaxBombs(sbBoard board);
SWEEP_EXPORT uint32_t    sbMinBombsXY(uint16_t x, uint16_t y);
SWEEP_EXPORT uint32_t    sbMaxBombsXY(uint16_t x, uint16_t y);
SWEEP_EXPORT uint16_t    sbMinWidth(void);
SWEEP_EXPORT uint16_t    sbMaxWidth(void);
SWEEP_EXPORT uint16_t    sbMinHeight(void);
SWEEP_EXPORT uint16_t    sbMaxHeight(void);

#endif // SWEEP_BOARD_H
