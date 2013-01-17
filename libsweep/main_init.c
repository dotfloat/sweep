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
#include <memory.h>

#include "main_priv.h"
#include "version.h"

struct _smStreamStack smStreamStack;
struct _smErrorStack smErrorStack;

int _smInit(int major, int minor)
{
    if(major != SWEEP_VERMAJOR || minor != SWEEP_VERMINOR)
        return 0;

    memset(&smStreamStack, 0, sizeof(smStreamStack));
    memset(&smErrorStack, 0, sizeof(smErrorStack));

    return 1;
}

void smQuit(void)
{
    free(smStreamStack.nodes);
    free(smErrorStack.nodes);
}
