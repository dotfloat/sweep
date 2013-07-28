
#include <time.h>

#include <sweep.h>
#include "b_private.h"

int __populate(sweep_board_t board, uint32_t bombs, uint32_t seed, char safe, uint16_t x, uint16_t y);

int sweepBoardPopulate(sweep_board_t board, uint32_t bombs){
    return __populate(board, bombs, time(0), 0, 0, 0);
}

int sweepBoardPopulateSafe(sweep_board_t board, uint32_t bombs, uint16_t x, uint16_t y){
    return __populate(board, bombs, time(0), 1, x, y);
}

int sweepBoardPopulateSeed(sweep_board_t board, uint32_t bombs, uint32_t seed){
    return __populate(board, bombs, seed, 0, 0, 0);
}

int sweepBoardPopulateSafeSeed(sweep_board_t board, uint32_t bombs, uint32_t seed, uint16_t x, uint16_t y){
    return __populate(board, bombs, seed, 1, x, y);
}

int __populate(sweep_board_t board, uint32_t bombs, uint32_t seed, char safe, uint16_t X, uint16_t Y){
    srand(seed);
    if(bombs < sweepMinBombs(board) || bombs > sweepMaxBombs(board)) {
        printf("%d\n", sweepMinBombs(board));
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
        board->map[y*board->width+x] = SWEEP_BOMB | SWEEP_CLOSED;
    }

    // gen numbers
    for(y=0; y<board->height; y++) {
        for(x=0; x<board->width; x++) {
            if((board->map[y*board->width+x]&0xf)!=SWEEP_BOMB) continue;

            #define X(Sx, Sy, Px, Py) board->map[ Py*Sx + Px ]++;
                SWEEP_XMACRO_local
            #undef X
        }
    }
    board->bombs = bombs;
    board->seed = seed;

    return S_TRUE;
}