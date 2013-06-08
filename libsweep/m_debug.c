
#include <stdio.h>
#include <stdlib.h>

#include <sweep.h>

extern sgGame_t game;

const char linear[] = ".12345678*#f?e+-x";

void sDebugDumpBoard(FILE *dest){
    sbCell_t *map = sbAllocMap(sgGetBoard(game));
    sbGetDataRaw(sgGetBoard(game), map);
    
    int x, y;
    size_t s;
    for(y=0; y<sgGetHeight(game); y++) {
        for(x=0; x<sgGetWidth(game); x++) {
            s = y*sgGetHeight(game) + x;
            putchar(linear[S_1(map[s])]);
        }
        putchar('\n');
    }
    free(map);
}

void sDebugDumpBoardVisible(FILE *dest){
    sbCell_t *map = sbAllocMap(sgGetBoard(game));
    sbGetDataVisible(sgGetBoard(game), map);
    
    int x, y;
    size_t s;
    for(y=0; y<sgGetHeight(game); y++) {
        for(x=0; x<sgGetWidth(game); x++) {
            s = y*sgGetHeight(game) + x;
            putchar(linear[map[s]]);
        }
        putchar('\n');
    }
    free(map);
}