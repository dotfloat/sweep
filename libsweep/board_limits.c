
#include "board_priv.h"

uint32_t sbMinBombs(sbBoard board)
{
    return (double)SWEEP_MINDENSITY*board->_width*board->_height;
}

uint32_t sbMaxBombs(sbBoard board)
{
    return (double)SWEEP_MAXDENSITY*board->_width*board->_height;
}

uint32_t sbMinBombsXY(uint16_t x, uint16_t y)
{
    return (double)SWEEP_MINDENSITY*x*y;
}

uint32_t sbMaxBombsXY(uint16_t x, uint16_t y)
{
    return (double)SWEEP_MAXDENSITY*x*y;
}

uint16_t sbMinWidth(void)
{
    return 9;
}

uint16_t sbMaxWidth(void)
{
    return 16384;
}

uint16_t sbMinHeight(void)
{
    return 9;
}

uint16_t sbMaxHeight(void)
{
    return 12288;
}
