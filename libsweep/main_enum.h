
#ifndef MAIN_ENUM_H
#define MAIN_ENUM_H

typedef enum
{
    smErrOK         = 0x00,
    smErrMalloc     = 0x01,
    smErrRealloc    = 0x02,

    smErrBoardSize  = 0x03,
    smErrBoardBombs = 0x04,
    smErrBoardOutOfBounds = 0x05,
    smErrBoardRevealAroundClosed = 0x06,
    smErrBoardRevealAroundNotEnough = 0x07,

    smErrorLast,
} smError;

typedef enum
{
    ERR_INFO,
    ERR_WARN,
    ERR_FATAL,
} smSeverity;

#endif // MAIN_ENUM_H
