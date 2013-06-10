
#include <sweep.h>

struct __sbBoard_t {
    uint16_t width;
    uint16_t height;
    uint32_t bombs;
    uint32_t seed;

    sbCell_t *map;
    
    S_BOOL exploded;
    S_BOOL mark;
};