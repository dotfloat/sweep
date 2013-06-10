
#include <stdio.h>
#include <stdlib.h>

#include "g_private.h"

struct __sgDiff_t{
    int width;
    int height;
    int bombs;
} sgDiffs[SG_DIFF_LAST] = {
    { 10, 10, 10 },
    { 16, 10, 40 },
    { 16, 14, 99 },
};

sgGame_t sgInit(void){
    sgGame_t g = malloc(sizeof(struct __sgGame_t));
    memset(g, 0, sizeof(struct __sgGame_t));
    return g;
}

int sgStart(sgGame_t g, sgDiff_t difficulty){
    if(difficulty >= SG_DIFF_LAST) {
        g->difficulty = SG_EASY;
    } else {
        g->difficulty = difficulty;
    }
    g->playing = S_TRUE;
    
    struct __sgDiff_t *diff = &sgDiffs[g->difficulty];
    
    sbDestroy(g->board);
    if(!(g->board = sbInit(diff->width, diff->height))) {
        /* Push error */
    }
    
    sbPopulate(g->board, diff->bombs);
    
    return 0;
}

void sgDestroy(sgGame_t g){
    if(!g) return;
    if(g->board) (g->board);
    if(g) free(g);
}