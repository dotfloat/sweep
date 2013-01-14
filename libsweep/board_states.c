
#include "board_priv.h"

sbState sbGetState(sbBoard board)
{
    return board->_state;
}

int sbSpecState(sbBoard board, sbState state)
{
    return board->_state&state;
}

void sbSetState(sbBoard board, sbState state, int enable)
{
    if(enable)
        board->_state -= board->_state&state;
    else
        board->_state |= state;
}
