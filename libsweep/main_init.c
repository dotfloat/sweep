
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
