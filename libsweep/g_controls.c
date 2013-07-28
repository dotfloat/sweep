
#include "g_private.h"

int sweepReveal(sweep_t g, int x, int y){
    if(!g->playing) {
        return 0;
    }
    
    if(!g->populated) {
        sweepBoardPopulateSafe(g->board, 10, x, y);
        g->populated = S_TRUE;
    }
    
    sweep_cell_t c = sweepBoardCellRaw(g->board, x, y);
    if(S_20(c) == SWEEP_FLAG || S_20(c) == SWEEP_MARK) {
        return S_FALSE;
    }
    
    int r = sweepBoardReveal(g->board, x, y);
    
    if(sweepBoardHasExploded(g->board)) {
        sweepBoardRevealBombs(g->board);
        g->playing = S_FALSE;
        CB_exploded();
        return r;
    }
    
    if(sweepBoardHasWon(g->board)) {
        sweepBoardRevealBombs(g->board);
        g->playing = S_FALSE;
        CB_won();
        return r;
    }
    
    CB_acted();
    
    return r;
}

int sgToggleFlag(sweep_t g, int x, int y){
    sweepBoardToggleFlag(g->board, x, y);
    
    CB_acted();
}