
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
    
    fputc(' ', dest);
    for(x=0; x<sgGetWidth(game); x++) {
        fputc('-', dest);
    }
    fputc('\n', dest);
    
    for(y=0; y<sgGetHeight(game); y++) {
        fputc('|', dest);
        for(x=0; x<sgGetWidth(game); x++) {
            s = y*sgGetHeight(game) + x;
            fputc(linear[S_1(map[s])], dest);
        }
        fputc('|', dest);
        fputc('\n', dest);
    }
    
    fputc(' ', dest);
    for(x=0; x<sgGetWidth(game); x++) {
        fputc('-', dest);
    }
    fputc('\n', dest);
    
    free(map);
}

void sDebugDumpBoardVisible(FILE *dest){
    sbCell_t *map = sbAllocMap(sgGetBoard(game));
    sbGetDataVisible(sgGetBoard(game), map);
    
    int x, y;
    size_t s;
    
    fputc(' ', dest);
    for(x=0; x<sgGetWidth(game); x++) {
        fputc('-', dest);
    }
    fputc('\n', dest);
    
    for(y=0; y<sgGetHeight(game); y++) {
        fputc('|', dest);
        for(x=0; x<sgGetWidth(game); x++) {
            s = y*sgGetHeight(game) + x;
            fputc(linear[map[s]], dest);
        }
        fputc('|', dest);
        fputc('\n', dest);
    }
    
    fputc(' ', dest);
    for(x=0; x<sgGetWidth(game); x++) {
        fputc('-', dest);
    }
    fputc('\n', dest);
    
    free(map);
}