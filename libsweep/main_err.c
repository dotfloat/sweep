
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
