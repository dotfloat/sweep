
#include <stdlib.h>

#include <sweep.h>
#include "b_private.h"

typedef struct {
    uint16_t x;
    uint16_t y;
} sbPx;

typedef struct {
    sbBoard_t board;
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
    
    if(S_20(R->board->map[a])==SB_CLOSED) {
        R->board->map[a] = SB_OPEN | S_1(R->board->map[a]);
            printf("%d\n", S_1(R->board->map[a]));
        if(S_1(R->board->map[a]) == SB_EMPTY) {
            sbPx q = {R->p.x-mx, R->p.y-my};
            if(!__pushStack(&R->stack, &R->stackN, q)) {
                free(R->stack);
                return S_FALSE;
            }
        } else if(S_1(R->board->map[a]) == SB_BOMB) {
            R->board->map[a] = SB_EXPLODE;
            R->board->exploded = S_TRUE;
        }
    }
    return S_TRUE;
}

int sbReveal(sbBoard_t board, uint16_t x, uint16_t y){
    if(x>=board->width||y>=board->height) {
        /* Out of bounds */
        return 0;
    }

    board->map[y*board->width+x] = SB_OPEN | S_1(board->map[y*board->width+x]);

    if(S_1(board->map[y*board->width+x]) == SB_BOMB) {
        board->map[y*board->width+x] = SB_EXPLODE;
        board->exploded = S_TRUE;
        return S_TRUE;
    } else if(S_1(board->map[y*board->width+x]) != SB_EMPTY) {
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

#define REVEALAROUND(mx, my) if(x>=mx&&y>=my&&(x-mx)<board->width&&(y-my)<board->height) sbReveal(board, x-mx, y-my);

int sbRevealAround(sbBoard_t board, uint16_t x, uint16_t y)
{
    if(x>=board->width||y>=board->height)
    {
        /* out of bounds */
        return 0;
    }

    REVEALAROUND(1, 1)
    REVEALAROUND(1, -1)
    REVEALAROUND(-1, 1)
    REVEALAROUND(-1, -1)

    REVEALAROUND(1, 0)
    REVEALAROUND(0, 1)
    REVEALAROUND(-1, 0)
    REVEALAROUND(0, -1)

    return 1;
}

int sbRevealAroundStrict(sbBoard_t board, uint16_t x, uint16_t y)
{
    int n = sbCountNeighbors(board, x, y);
    char c = sbGetCellVisible(board, x, y);
    if(S_20(c) != SB_OPEN)
    {
        /* Open */
        return 0;
    }

    if(n == c)
        return sbRevealAround(board, x, y);
    /* n != c */
    return 0;
}

int sbRevealBombs(sbBoard_t board)
{
    uint32_t i;
    sbCell_t c;
    for(i=0; i<board->width*board->height; i++)
    {
        c = board->map[i];
        if(S_20(c) == SB_MARK || S_20(c) == SB_FLAG) {
            if(S_1(c) == SB_BOMB) {
                board->map[i] = SB_FLAG_TRUE;
            } else {
                board->map[i] = SB_FLAG_FALSE;
            }
        } else if(S_1(c) == SB_BOMB) {
            board->map[i] = SB_FLAG_NONE;
        }
    }

    return 1;
}

int sbRevealAll(sbBoard_t board)
{
    uint32_t i;
    sbCell_t c;
    for(i=0; i<board->width*board->height; i++)
    {
        c = board->map[i];
        if(S_20(c) == SB_MARK || S_20(c) == SB_FLAG) {
            if(S_1(c) == SB_BOMB) {
                board->map[i] = SB_FLAG_TRUE;
            } else {
                board->map[i] = SB_FLAG_FALSE;
            }
        } else if(S_1(c) == SB_BOMB) {
            board->map[i] = SB_FLAG_NONE;
        } else {
            board->map[i] = SB_OPEN | S_1(board->map[i]);
        }
    }
    return 1;
}