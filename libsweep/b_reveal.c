
#include <stdlib.h>

#include <sweep.h>
#include "b_private.h"

typedef struct {
    uint16_t x;
    uint16_t y;
} sbPx;

typedef struct {
    sweep_board_t board;
    sbPx *stack;
    int stackN;
    sbPx p;
} reveal_t;

#define CHUNKSIZE 32
    
inline int __pushStack(sbPx **stack, int *size, sbPx x){
    (*size)++;
    if((*size)%CHUNKSIZE==0) {
        (*stack) = realloc(*stack, sizeof(sbPx)*(*size));
    }
    (*stack)[(*size)-1] = x;
    return 1;
}

inline sbPx __popStack(sbPx **stack, int *size){
    return (*stack)[--(*size)];
}

int __reveal(int mx, int my, reveal_t *R){    
    int a = (R->p.y-my) * R->board->width + R->p.x-mx;
    
    if(!(R->p.x>=mx && R->p.y>=my &&
        (R->p.x-mx)<R->board->width && (R->p.y-my)<R->board->height)) {
        return S_FALSE;
    }
    
    if(S_20(R->board->map[a])==SWEEP_CLOSED) {
        R->board->map[a] = SWEEP_OPEN | S_1(R->board->map[a]);
        if(S_1(R->board->map[a]) == SWEEP_EMPTY) {
            sbPx q = {R->p.x-mx, R->p.y-my};
            if(!__pushStack(&R->stack, &R->stackN, q)) {
                free(R->stack);
                return S_FALSE;
            }
        } else if(S_1(R->board->map[a]) == SWEEP_BOMB) {
            R->board->map[a] = SWEEP_EXPLODE;
            R->board->exploded = S_TRUE;
        }
    }
    return S_TRUE;
}

int sweepBoardReveal(sweep_board_t board, uint16_t x, uint16_t y){
    if(x>=board->width||y>=board->height) {
        /* Out of bounds */
        return 0;
    }

    board->map[y*board->width+x] = SWEEP_OPEN | S_1(board->map[y*board->width+x]);

    if(S_1(board->map[y*board->width+x]) == SWEEP_BOMB) {
        board->map[y*board->width+x] = SWEEP_EXPLODE;
        board->exploded = S_TRUE;
        return S_TRUE;
    } else if(S_1(board->map[y*board->width+x]) != SWEEP_EMPTY) {
        return S_TRUE;
    }
    
    reveal_t R;
    
    R.board = board;
    R.stack = malloc(sizeof(sbPx)*CHUNKSIZE);
    R.stack->x = x;
    R.stack->y = y;
    R.p;
    R.stackN = 1;
    
    int a;

    while(R.stackN)
    {
        R.p = __popStack(&(R.stack), &(R.stackN));
        
        __reveal(1, 1, &R);
        __reveal(1, -1, &R);
        __reveal(-1, 1, &R);
        __reveal(-1, -1, &R);
        
        __reveal(1, 0, &R);
        __reveal(0, 1, &R);
        __reveal(-1, 0, &R);
        __reveal(0, -1, &R);
    }

    free(R.stack);

    return 1;
}

int sweepBoardRevealAround(sweep_board_t board, uint16_t x, uint16_t y)
{
    if(x>=board->width||y>=board->height)
    {
        /* out of bounds */
        return 0;
    }
    
    sweep_cell_t c = sweepBoardCellRaw(board, x, y);
    if(S_20(c) != SWEEP_OPEN) {
        return 0;
    }
    if(S_1(c) >= SWEEP_BOMB) {
        return 0;
    }
    
    if(sweepBoardCountNeighbors(board, x, y) == S_1(c)) {
#define X(Sx, Sy, Px, Py) sweepBoardReveal(board, Px, Py);
        SWEEP_XMACRO_local
#undef X
    }

    return 1;
}

int sweepBoardRevealBombs(sweep_board_t board)
{
    uint32_t i;
    sweep_cell_t c;
    for(i=0; i<board->width*board->height; i++)
    {
        c = board->map[i];
        if(S_20(c) == SWEEP_MARK || S_20(c) == SWEEP_FLAG) {
            if(S_1(c) == SWEEP_BOMB) {
                board->map[i] = SWEEP_FLAG_TRUE;
            } else {
                board->map[i] = SWEEP_FLAG_FALSE;
            }
        } else if(S_1(c) == SWEEP_BOMB) {
            board->map[i] = SWEEP_FLAG_NONE;
        }
    }

    return 1;
}

int sweepBoardRevealAll(sweep_board_t board)
{
    uint32_t i;
    sweep_cell_t c;
    for(i=0; i<board->width*board->height; i++)
    {
        c = board->map[i];
        if(S_20(c) == SWEEP_MARK || S_20(c) == SWEEP_FLAG) {
            if(S_1(c) == SWEEP_BOMB) {
                board->map[i] = SWEEP_FLAG_TRUE;
            } else {
                board->map[i] = SWEEP_FLAG_FALSE;
            }
        } else if(S_1(c) == SWEEP_BOMB) {
            board->map[i] = SWEEP_FLAG_NONE;
        } else {
            board->map[i] = SWEEP_OPEN | S_1(board->map[i]);
        }
    }
    return 1;
}