
#ifndef MAIN_PRIV_H
#define MAIN_PRIV_H

#ifndef SWEEP_EXPORT
# ifdef _WIN32
#  define SWEEP_EXPORT declspec(dllexport)
# else
#  define SWEEP_EXPORT
# endif
#endif

#include <stdint.h>

#include <main.h>

#define STACKCHUNKSIZE 8

struct _smStreamStack
{
    FILE *nodes;
    size_t alloc;
    size_t count;
} extern smStreamStack;

struct _smErrorStack
{
    int *nodes;
    size_t alloc;
    size_t count;
} smErrorStack;

typedef struct
{
    const char *str;
    smSeverity severity;
} smErrStrStruct;

extern smErrStrStruct smErrStr[smErrorLast];

#endif // MAIN_PRIV_H
