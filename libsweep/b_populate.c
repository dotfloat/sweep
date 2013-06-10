
#include <time.h>

#include <sweep.h>
#include "b_private.h"

int __sbPopulate(sbBoard_t board, uint32_t bombs, uint32_t seed, char safe, uint16_t x, uint16_t y);

int sbPopulate(sbBoard_t board, uint32_t bombs){
    return __sbPopulate(board, bombs, time(0), 0, 0, 0);
}

int sbPopulateSafe(sbBoard_t board, uint32_t bombs, uint16_t x, uint16_t y){
    return __sbPopulate(board, bombs, time(0), 1, x, y);
}

int sbPopulateFromSeed(sbBoard_t board, uint32_t bombs, uint32_t seed){
    return __sbPopulate(board, bombs, seed, 0, 0, 0);
}

int sbPopulateSafeFromSeed(sbBoard_t board, uint32_t bombs, uint32_t seed, uint16_t x, uint16_t y){
    return __sbPopulate(board, bombs, seed, 1, x, y);
}

int __sbPopulate(sbBoard_t board, uint32_t bombs, uint32_t seed, char safe, uint16_t X, uint16_t Y){
    srand(seed);
    if(bombs < sbMinBombs(board) || bombs > sbMaxBombs(board)) {
        printf("%d\n", sbMinBombs(board));
        /* push error about incorrect amount of bombs */
        return 0;
    }
    int x, y, i;
    
    // clear the minefield without removing flags
    for(y=0; y<board->height; y++) {
        for(x=0; x<board->width; x++) {
            board->map[y*board->width+x] = S_20(board->map[y*board->width+x]);
        }
    }
    
    // shuffle
    for(i=0; i<bombs; i++) {
        do {
            x = rand() % board->width;
            y = rand() % board->height;
        } while(safe&&x>=X-1&&x<=X+1&&y>=Y-1&&y<=Y+1);
        board->map[y*board->width+x] = SB_BOMB | SB_CLOSED;
    }

    // gen numbers
    for(y=0; y<board->height; y++) {
        for(x=0; x<board->width; x++) {
            #define BOMBINC(mx, my) \
                if(x>=mx&&y>=my&&(x-mx)<board->width&&(y-my)<board->height&&(board->map[(y-my)*board->width+x-mx]&0xf)!=SB_BOMB) \
                board->map[(y-my)*board->width+x-mx]++;

            if((board->map[y*board->width+x]&0xf)!=SB_BOMB) continue;

            BOMBINC(1, 1)
            BOMBINC(1, -1)
            BOMBINC(-1, 1)
            BOMBINC(-1, -1)

            BOMBINC(1, 0)
            BOMBINC(0, 1)
            BOMBINC(-1, 0)
            BOMBINC(0, -1)
        }
    }
    board->bombs = bombs;
    board->seed = seed;

    return S_TRUE;
}