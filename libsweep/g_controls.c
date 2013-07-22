
#include "g_private.h"

int sgReveal(sgGame_t g, int x, int y){
    if(!g->playing) {
        return 0;
    }
    
    if(!g->started) {
        sbPopulateSafe(g->board, 10, x, y);
        g->started = S_TRUE;
    }
    
    sbCell_t c = sbGetCellRaw(g->board, x, y);
    if(S_20(c) == SB_FLAG || S_20(c) == SB_MARK) {
        return S_FALSE;
    }
    
    int r = sbReveal(g->board, x, y);
    
    if(sbExploded(g->board)) {
        sbRevealBombs(g->board);
        g->playing = S_FALSE;
        CB_exploded();
        return r;
    }
    
    if(sbHasWon(g->board)) {
        sbRevealBombs(g->board);
        g->playing = S_FALSE;
        CB_won();
        return r;
    }
    
    CB_acted();
    
    return r;
}

int sgToggleFlag(sgGame_t g, int x, int y){
    sbToggleFlag(g->board, x, y);
    
    CB_acted();
}