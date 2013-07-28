
#include <stdio.h>
#include <stdlib.h>

#include <sweep.h>
#include "b_private.h"
#include "g_private.h"

const char linear[] = ".12345678*#f?e+-x";
const char flags[] = "ocfme!?.";
const char tiles[] = "-12345678B";

#define B(x) (x?"yes":"no")

void sweepDebugDumpBoard(sweep_board_t board, FILE *dest) {
    fprintf(dest, "sweep_board_t addr: %p\n", board);
    if(board) {
        fprintf(dest, "width: %u\n", board->width);
        fprintf(dest, "height: %u\n", board->height);
        fprintf(dest, "bombs: %u\n", board->bombs);
        fprintf(dest, "seed: %u\n", board->seed);
        fprintf(dest, "flags: \n");
        fprintf(dest, "    exploded? %s\n", B(board->exploded));
        fprintf(dest, "    marked? %s\n", B(board->mark));
    } else {
        fprintf(dest, "game->board is NULL.\n");
        fprintf(dest, "why would it ever be NULL?\n");
        
        return;
    }
    fprintf(dest, "\n");
    fprintf(dest, "dumping raw board: \n");

    unsigned x, y;
    for(y=0; y<board->height; y++) {
        for(x=0; x<board->width; x++) {
            sweep_cell_t c = board->map[y*board->width+x];
            
            if(S_2(c) > sizeof(flags)) { // Sanity check 2nd nybble
                fprintf(dest, "\nillegal flag %x at (%u, %u).\n", S_20(c), x, y);
            } else {
                fprintf(dest, "%c", flags[S_2(c)]);
            }
            
            if(S_1(c) > sizeof(tiles)) {
                fprintf(dest, "\nillegal tile %x at (%u, %u).\n", S_1(c), x, y);
            } else {
                fprintf(dest, "%c ", tiles[S_1(c)]);
            }
        }
        fprintf(dest, "\n");
    }
}

void sweepDebugDump(sweep_t game, FILE *dest) {
    fprintf(dest, "sweep_t addr: %p\n", game);
    if(game) {
        fprintf(dest, "difficulty: %d\n", game->difficulty);
        fprintf(dest, "flags: \n");
        fprintf(dest, "    playing? %s\n", B(game->playing));
        fprintf(dest, "    populated? %s\n", B(game->populated));
    } else {
        fprintf(dest, "game is NULL.\n");
        fprintf(dest, "what are you even trying to debug?\n");
    }
    fprintf(dest, "\n");
    sweepDebugDumpBoard(sweepGetBoard(game), dest);
}