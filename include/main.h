
#ifndef SWEEP_MAIN_H
#define SWEEP_MAIN_H

#include "main_enum.h"

#include <stdio.h>

/* (de)initialise */
SWEEP_EXPORT int        _smInit(int major, int minor);
SWEEP_EXPORT void       smQuit(void);

/* error handling */
SWEEP_EXPORT int        smGetLastErrorID(void);
SWEEP_EXPORT const char*smGetLastError(void);
SWEEP_EXPORT int        smPopErrorID(void);
SWEEP_EXPORT const char*smPopError(void);
SWEEP_EXPORT void       smPushError(int err);
SWEEP_EXPORT const char*smGetErrorByID(int err);

/* stream */
SWEEP_EXPORT int        smStreamPrint(const char *str);
SWEEP_EXPORT int        smStreamAdd(FILE *file);
SWEEP_EXPORT int        smStreamRemove(FILE *file);
SWEEP_EXPORT int        smStreamFlush(void);

#define smInit() _smInit(SWEEP_VERMAJOR, SWEEP_VERMINOR)

#endif // SWEEP_MAIN_H
