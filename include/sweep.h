/**
 *  This file is part of Sweep.
 *
 *  Sweep is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  Sweep is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *  
 *  You should have received a copy of the GNU General Public License
 *  along with Sweep.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef SWEEP_H
#define SWEEP_H

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __LIBSWEEP__
 #ifdef _WIN32
  #define SWEEP_EXPORT __declspec(dllimport)
 #else
  #define SWEEP_EXPORT extern
 #endif
#else
 #ifdef _WIN32
  #define SWEEP_EXPORT __declspec(dllimport)
 #else
  #define SWEEP_EXPORT
 #endif
#endif

#include <stdio.h>
#include <stdint.h>

/* version stuff */
#define SWEEP_VER_MAJOR	0
#define SWEEP_VER_MINOR	0
#define SWEEP_VER_REV	0

/* some basic macros */
#define S_1(c)          (c&0xf)         /* get first nybble from 'c'  [S_1(0x42)==0x2] */
#define S_2(c)          ((c&0xf0)>>4)   /* get second nybble from 'c' [S_2(0x42)==0x4] */
#define S_20(c)         (c&0xf0)        /* same as S_2(c) but without the bitshift */
#define S_BOOL          int
#define S_FALSE         0
#define S_TRUE          1

#define SWEEP_XMACRO_CELL(Sx, Sy, Px, Py, Mx, My) \
    if(Px>=Mx && Py>=My && (Px-Mx)<Sx && (Py-My)<Sy) { X(Sx, Sy, (Px-Mx), (Py-My)) }
        
#define SWEEP_XMACRO(Sx, Sy, Px, Py) \
    SWEEP_XMACRO_CELL(Sx, Sy, Px, Py,  1,  0)\
    SWEEP_XMACRO_CELL(Sx, Sy, Px, Py,  0,  1)\
    SWEEP_XMACRO_CELL(Sx, Sy, Px, Py, -1,  0)\
    SWEEP_XMACRO_CELL(Sx, Sy, Px, Py,  0, -1)\
    SWEEP_XMACRO_CELL(Sx, Sy, Px, Py,  1,  1)\
    SWEEP_XMACRO_CELL(Sx, Sy, Px, Py,  1, -1)\
    SWEEP_XMACRO_CELL(Sx, Sy, Px, Py, -1,  1)\
    SWEEP_XMACRO_CELL(Sx, Sy, Px, Py, -1, -1)\

#define SWEEP_XMACRO_B(B, Px, Py) \
    SWEEP_XMACRO(B->width, B->height, Px, Py)

#define SWEEP_XMACRO_local \
    SWEEP_XMACRO(board->width, board->height, x, y)

/* enums */
typedef enum {
    /* cell data */
    SWEEP_EMPTY         = 0x00,
    SWEEP_1             = 0x01,
    SWEEP_2             = 0x02,
    SWEEP_3             = 0x03,
    SWEEP_4             = 0x04,
    SWEEP_5             = 0x05,
    SWEEP_6             = 0x06,
    SWEEP_7             = 0x07,
    SWEEP_8             = 0x08,
    SWEEP_BOMB          = 0x09,

    /* linear */
    SWEEP_L_CLOSED      = 0x0a,
    SWEEP_L_FLAG        = 0x0b,
    SWEEP_L_MARK        = 0x0c,
    SWEEP_L_EXPLODE     = 0x0d,
    SWEEP_L_FLAG_TRUE   = 0x0e,
    SWEEP_L_FLAG_FALSE  = 0x0f,
    SWEEP_L_FLAG_NONE   = 0x10,

    /* cell flag */
    SWEEP_OPEN          = 0x00, /* cell is open (and isn't a bomb) */
    SWEEP_CLOSED        = 0x10, /* cell is closed (default) */
    SWEEP_FLAG          = 0x20, /* flag is placed on closed cell */
    SWEEP_MARK          = 0x30, /* mark is placed on closed cell */
    SWEEP_EXPLODE       = 0x40, /* a bomb is revealed */
    SWEEP_FLAG_TRUE     = 0x50, /* cell was correctly flagged (bomb underneath) */
    SWEEP_FLAG_FALSE    = 0x60, /* cell was incorrectly flagged (no bomb underneath) */
    SWEEP_FLAG_NONE     = 0x70, /* cell was a bomb but no flag */
} sweep_cell_t;

typedef enum {
    S_ACTION,
    S_RENDER,
    S_QUIT,
    S_WON,
    S_LOST,
} sState_t;

/* typedefs */
struct __sweep_board_t;
typedef struct __sweep_board_t * sweep_board_t;

typedef sweep_cell_t sweep_linear_t;

/* (de)initialise */
SWEEP_EXPORT sweep_board_t      sweepBoardInit          ( uint16_t width, uint16_t height );
SWEEP_EXPORT sweep_board_t      sweepBoardCopy          ( sweep_board_t board );
SWEEP_EXPORT void               sweepBoardDestroy       ( sweep_board_t board );

/* reset */
SWEEP_EXPORT sweep_board_t      sweepBoardResize        ( sweep_board_t board, uint16_t width, uint16_t height );
SWEEP_EXPORT int                sweepBoardReset         ( sweep_board_t board );

/* populate */
SWEEP_EXPORT int                sweepBoardPopulate           ( sweep_board_t board, uint32_t bombs );
SWEEP_EXPORT int                sweepBoardPopulateSafe       ( sweep_board_t board, uint32_t bombs, uint16_t x, uint16_t y );
SWEEP_EXPORT int                sweepBoardPopulateSeed       ( sweep_board_t board, uint32_t bombs, uint32_t seed );
SWEEP_EXPORT int                sweepBoardPopulateSafeSeed   ( sweep_board_t board, uint32_t bombs, uint32_t seed, uint16_t x, uint16_t y );

/* reveal */
SWEEP_EXPORT int                sweepBoardReveal        ( sweep_board_t board, uint16_t x, uint16_t y );
SWEEP_EXPORT int                sweepBoardRevealAround  ( sweep_board_t board, uint16_t x, uint16_t y );
SWEEP_EXPORT int                sweepBoardRevealBombs   ( sweep_board_t board );
SWEEP_EXPORT int                sweepBoardRevealAll     ( sweep_board_t board );

/* cell data */
SWEEP_EXPORT uint16_t           sweepBoardWidth         ( sweep_board_t board );
SWEEP_EXPORT uint16_t           sweepBoardHeight        ( sweep_board_t board );
SWEEP_EXPORT sweep_cell_t *	sweepBoardAllocMap      ( sweep_board_t board );
SWEEP_EXPORT sweep_cell_t       sweepBoardCellRaw       ( sweep_board_t board, uint16_t x, uint16_t y );
SWEEP_EXPORT sweep_cell_t       sweepBoardCellVisible   ( sweep_board_t board, uint16_t x, uint16_t y );
SWEEP_EXPORT int	        sweepBoardDataRaw       ( sweep_board_t board, sweep_cell_t *cells );
SWEEP_EXPORT int                sweepBoardDataVisible   ( sweep_board_t board, sweep_linear_t *map );
SWEEP_EXPORT void               sweepBoardSetCellRaw    ( sweep_board_t board, sweep_cell_t cell, uint16_t x, uint16_t y );
SWEEP_EXPORT void               sweepBoardToggleFlag    ( sweep_board_t board, uint16_t x, uint16_t y );
SWEEP_EXPORT int                sweepBoardCountNeighbors( sweep_board_t board, uint16_t x, uint16_t y );
SWEEP_EXPORT S_BOOL 	        sweepBoardSanityCheck   ( sweep_board_t board );

/* limits */
SWEEP_EXPORT uint32_t           sweepMinBombs           ( sweep_board_t board );
SWEEP_EXPORT uint32_t           sweepMaxBombs           ( sweep_board_t board );
SWEEP_EXPORT uint32_t           sweepMinBombsXY         ( uint16_t x, uint16_t y );
SWEEP_EXPORT uint32_t           sweepMaxBombsXY         ( uint16_t x, uint16_t y );
SWEEP_EXPORT uint16_t           sweepMinWidth           ( void );
SWEEP_EXPORT uint16_t           sweepMaxWidth           ( void );
SWEEP_EXPORT uint16_t           sweepMinHeight          ( void );
SWEEP_EXPORT uint16_t           sweepMaxHeight          ( void );

SWEEP_EXPORT S_BOOL             sweepBoardHasWon             ( sweep_board_t board );
SWEEP_EXPORT S_BOOL             sweepBoardHasExploded        ( sweep_board_t board );

/* game */
typedef enum {
    SG_EASY,
    SG_NORMAL,
    SG_HARD,
    SG_DIFF_LAST,
    
} sweep_diff_t;

struct __sweep_t;
typedef struct __sweep_t *sweep_t;

SWEEP_EXPORT sweep_t            sweepInitGame           ( void );
SWEEP_EXPORT void               sweepDestroyGame        ( sweep_t game );

SWEEP_EXPORT int                sweepNewGame            ( sweep_t game, sweep_diff_t difficulty );

SWEEP_EXPORT uint16_t           sweepGetWidth           ( sweep_t game );
SWEEP_EXPORT uint16_t           sweepGetHeight          ( sweep_t game );
SWEEP_EXPORT sweep_board_t      sweepGetBoard           ( sweep_t game );
SWEEP_EXPORT int                sweepToggleFlag         ( sweep_t game, int x, int y );

typedef void (*sgCallback_t)(void);
SWEEP_EXPORT void        sgSetCBExplode(sgCallback_t callback);

/* main */
SWEEP_EXPORT const char * sFindUserConfig(const char *file, S_BOOL create);

SWEEP_EXPORT int                sweepCmdlineParse      ( int *argc, char **argv );
SWEEP_EXPORT S_BOOL             sweepCmdlineExists     ( const char *key );
SWEEP_EXPORT S_BOOL             sweepCmdlineArgs       ( const char *key, int *num_args, const char ***args );

SWEEP_EXPORT int                sweepCmdlineArgIntD    ( const char *key, int i, int def );
SWEEP_EXPORT float              sweepCmdlineArgFloatD  ( const char *key, int i, float def );
SWEEP_EXPORT char               sweepCmdlineArgCharD   ( const char *key, int i, char def );
SWEEP_EXPORT const char*        sweepCmdlineArgStringD ( const char *key, int i, const char *def );

#define sweepCmdlineArgInt(key, i)          sweepCmdlineArgIntD(key, i, 0)
#define sweepCmdlineArgFloat(key, i)        sweepCmdlineArgIntD(key, i, 0.0f)
#define sweepCmdlineArgChar(key, i)         sweepCmdlineArgIntD(key, i, '\0')
#define sweepCmdlineArgString(key, i)       sweepCmdlineArgIntD(key, i, "")

SWEEP_EXPORT void               sweepDebugDump          ( sweep_t game, FILE *dest );
SWEEP_EXPORT void               sweepDebugDumpBoard     ( sweep_board_t game, FILE *dest );

#ifdef __cplusplus
}
#endif

#endif // SWEEP_H
