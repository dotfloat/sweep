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

#include "main_priv.h"

int smGetLastErrorID(void)
{
    if(smErrorStack.count)
        return smErrorStack.nodes[smErrorStack.count-1];
    return smErrOK;
}

const char *smGetLastError(void)
{
    return smErrStr[smGetLastErrorID()].str;
}

int smPopErrorID(void)
{
    if(!smErrorStack.count)
        return smErrOK;
    smErrorStack.count--;
    int e = smErrorStack.nodes[smErrorStack.count];
    if(smErrorStack.count<smErrorStack.alloc)
    {
        smErrorStack.alloc -= STACKCHUNKSIZE;
        smErrorStack.nodes = realloc(smErrorStack.nodes, smErrorStack.alloc * sizeof(int));
    }

    return e;
}

const char *smPopError(void)
{
    return smErrStr[smPopErrorID()].str;
}

void smPushError(int err)
{
    smErrorStack.count++;
    if(smErrorStack.count>=smErrorStack.alloc)
    {
        smErrorStack.alloc += STACKCHUNKSIZE;
        smErrorStack.nodes = realloc(smErrorStack.nodes, smErrorStack.alloc * sizeof(int));
    }
    smErrorStack.nodes[smErrorStack.count-1] = err;
}

const char *smGetErrorByID(int err)
{
    return smErrStr[err].str;
}
