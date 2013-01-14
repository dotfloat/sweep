
#ifndef SWEEP_H
#define SWEEP_H

#ifdef _WIN32
# define SWEEP_EXPORT __declspec(dllimport)
#else
# define SWEEP_EXPORT extern
#endif

#include <stdint.h>

#include "version.h"
//#include "game.h"
#include "board.h"
#include "main.h"

#endif // SWEEP_H
