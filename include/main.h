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

#ifndef SWEEP_MAIN_H
#define SWEEP_MAIN_H

#include "main_enum.h"

#include <stdio.h>

/* (de)initialise */
SWEEP_EXPORT int        _smInit(int major, int minor);
SWEEP_EXPORT void       smQuit(void);

/* error handling */
SWEEP_EXPORT int        smGetLastErrorID(void);
SWEEP_EXPORT const char*smGetLastError(void);
SWEEP_EXPORT int        smPopErrorID(void);
SWEEP_EXPORT const char*smPopError(void);
SWEEP_EXPORT void       smPushError(int err);
SWEEP_EXPORT const char*smGetErrorByID(int err);

/* stream */
SWEEP_EXPORT int        smStreamPrint(const char *str);
SWEEP_EXPORT int        smStreamAdd(FILE *file);
SWEEP_EXPORT int        smStreamRemove(FILE *file);
SWEEP_EXPORT int        smStreamFlush(void);

#define smInit() _smInit(SWEEP_VERMAJOR, SWEEP_VERMINOR)

#endif // SWEEP_MAIN_H
