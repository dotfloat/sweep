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

#include <stdint.h>

/* version stuff */
#define SWEEP_VER_MAJOR	0
#define SWEEP_VER_MINOR	0
#define SWEEP_VER_REV	0

/* some basic macros */
#define S_1(c) 		(c&0xf)			/* get first nybble from 'c'  [S_1(0x42)==0x2] */
#define S_2(c) 		((c&0xf0)>8)	/* get second nybble from 'c' [S_2(0x42)==0x4] */
#define S_20(c)		(c&0xf0)		/* same as S_2(c) but without the bitshift */
#define S_BOOL int
#define S_FALSE 0
#define S_TRUE 1

/* enums */
typedef enum {
	/* cell data */
	SB_EMPTY		= 0x00,
	SB_1			= 0x01,
	SB_2			= 0x02,
	SB_3			= 0x03,
	SB_4			= 0x04,
	SB_5			= 0x05,
	SB_6			= 0x06,
	SB_7			= 0x07,
	SB_8			= 0x08,
	SB_BOMB			= 0x09,

	/* linear */
	SB_L_CLOSED		= 0x0a,
	SB_L_FLAG		= 0x0b,
	SB_L_MARK		= 0x0c,
	SB_L_EXPLODE	= 0x0d,
	SB_L_FLAG_TRUE	= 0x0e,
	SB_L_FLAG_FALSE	= 0x0f,
	SB_L_FLAG_NONE	= 0x10,

	/* cell flag */
	SB_OPEN			= 0x00,		/* cell is open (and isn't a bomb) */
	SB_CLOSED		= 0x10,		/* cell is closed (default) */
	SB_FLAG			= 0x20,		/* flag is placed on closed cell */
	SB_MARK			= 0x30,		/* mark is placed on closed cell */
	SB_EXPLODE		= 0x40,		/* a bomb is revealed */
	SB_FLAG_TRUE	= 0x50,		/* cell was correctly flagged (bomb underneath) */
	SB_FLAG_FALSE	= 0x60,		/* cell was incorrectly flagged (no bomb underneath) */
	SB_FLAG_NONE	= 0x70,		/* cell was a bomb but no flag */
} sbCell_t;

struct __sMenuHint_t;

struct __sMenuHint_t{
	struct {
		const char *enGB;
	} lang;
	const char **title;
	const char *action;
	struct __sMenuHint_t **children;
	struct __sMenuHint_t *parent;
};

/* typedefs */
struct 									__sbBoard_t;
typedef struct __sbBoard_t * 			sbBoard_t;
typedef const struct __sbBoard_t *		sbCBoard_t;

typedef sbCell_t sbLinear_t;
typedef struct __sMenuHint_t sMenuHint_t;
/* (de)initialise */
SWEEP_EXPORT sbBoard_t   sbCreate(uint16_t width, uint16_t height);
SWEEP_EXPORT sbBoard_t   sbCopy(sbBoard_t board);
SWEEP_EXPORT void        sbFree(sbBoard_t board);

/* reset */
SWEEP_EXPORT int         sbResize(sbBoard_t board, uint16_t width, uint16_t height);
SWEEP_EXPORT int         sbReset(sbBoard_t board);

/* populate */
SWEEP_EXPORT int         sbPopulate(sbBoard_t board, uint32_t bombs);
SWEEP_EXPORT int         sbPopulateSafe(sbBoard_t board, uint32_t bombs, uint16_t x, uint16_t y);
SWEEP_EXPORT int         sbPopulateFromSeed(sbBoard_t board, uint32_t bombs, uint32_t seed);
SWEEP_EXPORT int         sbPopulateSafeFromSeed(sbBoard_t board, uint32_t bombs, uint32_t seed, uint16_t x, uint16_t y);

/* reveal */
SWEEP_EXPORT int         sbReveal(sbBoard_t board, uint16_t x, uint16_t y);
SWEEP_EXPORT int         sbRevealAround(sbBoard_t board, uint16_t x, uint16_t y);
SWEEP_EXPORT int         sbRevealAroundStrict(sbBoard_t board, uint16_t x, uint16_t y);
SWEEP_EXPORT int         sbRevealBombs(sbBoard_t board);
SWEEP_EXPORT int         sbRevealAll(sbBoard_t board);

/* cell data */
SWEEP_EXPORT sbCell_t *	 sbCreateDataArray(sbBoard_t board);
SWEEP_EXPORT sbCell_t    sbGetCellRaw(sbCBoard_t board, uint16_t x, uint16_t y);
SWEEP_EXPORT sbCell_t    sbGetCellVisible(sbCBoard_t board, uint16_t x, uint16_t y);
SWEEP_EXPORT void	     sbGetDataRaw(sbBoard_t board, sbCell_t *cells);
SWEEP_EXPORT sbLinear_t *sbGetDataVisible(sbBoard_t board);
SWEEP_EXPORT void        sbSetCellRaw(sbBoard_t board, sbCell_t cell, uint16_t x, uint16_t y);
SWEEP_EXPORT void        sbToggleFlag(sbBoard_t board, uint16_t x, uint16_t y);
SWEEP_EXPORT int         sbCountNeighbors(sbBoard_t board, uint16_t x, uint16_t y);
SWEEP_EXPORT S_BOOL 	 sbSanityCheck(sbBoard_t board);

/* limits */
SWEEP_EXPORT uint32_t    sbMinBombs(sbBoard_t board);
SWEEP_EXPORT uint32_t    sbMaxBombs(sbBoard_t board);
SWEEP_EXPORT uint32_t    sbMinBombsXY(uint16_t x, uint16_t y);
SWEEP_EXPORT uint32_t    sbMaxBombsXY(uint16_t x, uint16_t y);
SWEEP_EXPORT uint16_t    sbMinWidth(void);
SWEEP_EXPORT uint16_t    sbMaxWidth(void);
SWEEP_EXPORT uint16_t    sbMinHeight(void);
SWEEP_EXPORT uint16_t    sbMaxHeight(void);

/* inlines */ /* [[[ un-inline this ]]]
inline S_BOOL sbSanityCheckTile(sbCell_t c) {
	if(S_1(c) > SB_BOMB || S_20(c) > SB_FLAG_NONE) return S_FALSE;
	if(S_1(c) != SB_BOMB && S_20(c) >= SB_OPEN && S_20(c) <= SB_MARK) return S_TRUE;
	if(S_1(c) == SB_BOMB && S_20(c) != SB_OPEN) return S_TRUE;
	return S_FALSE;
}

inline sbLinear_t sbCellLinearize(sbCell_t c) {
	if(S_20(c) == SB_OPEN) return S_1(c);
	return SB_L_CLOSED + S_2(c) - 1;
}*/

/* main */
#define sInit(argc, argv) __sInit(argc, argv, SWEEP_VER_MAJOR, SWEEP_VER_MINOR, SWEEP_VER_REV)
SWEEP_EXPORT int __sInit(int *argc, char **argv, short maj, short min, short rev);
SWEEP_EXPORT void sQuit(void);

SWEEP_EXPORT const sMenuHint_t * sMenuHint(void);

SWEEP_EXPORT const char * sFindUserConfig(const char *file, S_BOOL create);

SWEEP_EXPORT int sCmdlineParse(int *argc, char **argv);
SWEEP_EXPORT S_BOOL sCmdlineExists(const char *key);
SWEEP_EXPORT S_BOOL sCmdlineArgs(const char *key, int *num_args, const char ***args);
SWEEP_EXPORT int sCmdlineArgIntD(const char *key, int i, int def);
SWEEP_EXPORT float sCmdlineArgFloatD(const char *key, int i, float def);
SWEEP_EXPORT char sCmdlineArgCharD(const char *key, int i, char def);
SWEEP_EXPORT const char* sCmdlineArgStringD(const char *key, int i, const char *def);

#define sCmdlineArgInt(key, i) sCmdlineArgIntD(key, i, 0)
#define sCmdlineArgFloat(key, i) sCmdlineArgIntD(key, i, 0.0f)
#define sCmdlineArgChar(key, i) sCmdlineArgIntD(key, i, '\0')
#define sCmdlineArgString(key, i) sCmdlineArgIntD(key, i, "")

#ifdef __cplusplus
}
#endif

#endif // SWEEP_H
