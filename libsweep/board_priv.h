
#ifndef SWEEP_BOARD_PRIV_H
#define SWEEP_BOARD_PRIV_H

#ifndef SWEEP_EXPORT
# ifdef _WIN32
#  define SWEEP_EXPORT declspec(dllexport)
# else
#  define SWEEP_EXPORT
# endif
#endif

#include <stdint.h>

#include <board.h>
#include <main.h>

#define SWEEP_MINDENSITY 0.13
#define SWEEP_MAXDENSITY 0.63

struct _sbBoard
{
    uint16_t _width;
    uint16_t _height;
    uint32_t _bombs;
    uint32_t _seed;

    sbCell *_map;
    sbState _state;
};

#endif // SWEEP_BOARD_PRIV_H
