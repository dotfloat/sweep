
#include "main_priv.h"

smErrStrStruct smErrStr[smErrorLast] = {
/* smErrOK */         { "Success", ERR_INFO },
/* smErrMalloc */     { "Malloc failed", ERR_FATAL },
/* smErrRealloc */    { "Realloc failed", ERR_FATAL },
/* smErrBoardSize */  { "Incorrect board size", ERR_WARN },
/* smErrBoardBombs */ { "Incorrect number of bombs", ERR_WARN },
/* smErrBoardOutOfBounds */ { "Out of board bounds", ERR_WARN },
/* smErrBoardRevealAroundClosed */ { "Trying to reveal around a closed cell", ERR_WARN },
/* smErrBoardRevealAroundNotEnough */ { "The number of neighbours around cell is incorrect", ERR_WARN },
};
