
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

sweep_t sweepInitGame(void){
    sweep_t g = malloc(sizeof(struct __sweep_t));
    memset(g, 0, sizeof(struct __sweep_t));
    return g;
}

int sweepNewGame(sweep_t game, sweep_diff_t difficulty){
    if(difficulty >= SG_DIFF_LAST) {
        game->difficulty = SG_EASY;
    } else {
        game->difficulty = difficulty;
    }
    game->playing = S_TRUE;
    
    struct __sgDiff_t *diff = &sgDiffs[game->difficulty];
    
    sweepBoardDestroy(game->board);
    if(!(game->board = sweepBoardInit(diff->width, diff->height))) {
        /* Push error */
    }
    
    sweepBoardPopulate(game->board, diff->bombs);
    return 0;
}

void sweepDestroyGame(sweep_t g){
    if(!g) return;
    if(g->board) (g->board);
    if(g) free(g);
}