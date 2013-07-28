
#ifndef SWEEP_GAME_H
#define SWEEP_GAME_H

#include <sweep.h>

struct __sweep_t{
    sweep_board_t       board;
    sweep_diff_t        difficulty;
    S_BOOL              playing;
    S_BOOL              populated;
};

extern sgCallback_t CB_exploded;
extern sgCallback_t CB_acted;
extern sgCallback_t CB_won;

#endif // SWEEP_GAME_H
