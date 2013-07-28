
#include <sweep.h>

struct __sweep_board_t {
    uint16_t width;
    uint16_t height;
    uint32_t bombs;
    uint32_t seed;

    sweep_cell_t *map;
    
    S_BOOL exploded;
    S_BOOL mark;
};