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

#ifndef MAIN_PRIV_H
#define MAIN_PRIV_H

#ifndef SWEEP_EXPORT
# ifdef _WIN32
#  define SWEEP_EXPORT declspec(dllexport)
# else
#  define SWEEP_EXPORT
# endif
#endif

#include <stdint.h>

#include <main.h>

#define STACKCHUNKSIZE 8

struct _smStreamStack
{
    FILE *nodes;
    size_t alloc;
    size_t count;
} extern smStreamStack;

struct _smErrorStack
{
    int *nodes;
    size_t alloc;
    size_t count;
} smErrorStack;

typedef struct
{
    const char *str;
    smSeverity severity;
} smErrStrStruct;

extern smErrStrStruct smErrStr[smErrorLast];

#endif // MAIN_PRIV_H
