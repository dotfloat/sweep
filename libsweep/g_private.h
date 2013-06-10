
#ifndef SWEEP_GAME_H
#define SWEEP_GAME_H

#include <sweep.h>

struct __sgGame_t{
    sbBoard_t board;
    sgDiff_t difficulty;
    S_BOOL playing;
    S_BOOL started;
};

extern sgCallback_t CB_exploded;
extern sgCallback_t CB_acted;
extern sgCallback_t CB_won;

#endif // SWEEP_GAME_H
