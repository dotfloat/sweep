
#include <stdio.h>
#include <stdlib.h>
#include <sweep.h>

struct {
    const char *key;
    const char *skey;
    int num_args;
    
#define NUM_KEYS 3
} keys[NUM_KEYS] = {
    {"version",         "v", 0},
    {"exit",            0  , 0},
    {"echo",            0  , 1},
};

typedef struct {
    const char *key;
    int num_args;
    const char **args;
} __arr_t;

int __num_arr  = 0;
__arr_t *__arr = 0;

int __sPushToArray(const char *key, int num_args){
    __arr_t *arr;
    __num_arr++;
    __arr = realloc(__arr, sizeof(__arr_t) * __num_arr);
    arr = &__arr[__num_arr-1];
    arr->key = key;
    arr->num_args = num_args;
    arr->args = malloc(sizeof(const char *) * num_args);
}

int __sPushArgToArray(const char *arg, int i){
    __arr_t *arr = &__arr[__num_arr-1];
    arr->args[arr->num_args-i-1] = arg;
}

__arr_t *__sFindInArray(const char *key){
    __arr_t *arr;
    int i;
    for(i=0; i<__num_arr; i++) {
        arr = &__arr[i];
        if(!strcmp(arr->key, key)) {
            return arr;
        }
    }
    return NULL;
}

S_BOOL sCmdlineExists(const char *key){
    return __sFindInArray(key)?S_TRUE:S_FALSE;
}

S_BOOL sCmdlineArgs(const char *key, int *num_args, const char ***args){
    __arr_t *arr;
    if(!(arr = __sFindInArray(key))) return S_FALSE;
    (*num_args) = arr->num_args;
    (*args) = arr->args;
    return S_TRUE;
}

int sCmdlineArgIntD(const char *key, int i, int def){
    __arr_t *arr;
    if(!(arr = __sFindInArray(key))) return def;
    return strtol(arr->args[i], NULL, 10);
}

float sCmdlineArgFloatD(const char *key, int i, float def){
    __arr_t *arr;
    if(!(arr = __sFindInArray(key))) return def;
    return strtof(arr->args[i], NULL);
}

char sCmdlineArgCharD(const char *key, int i, char def){
    __arr_t *arr;
    if(!(arr = __sFindInArray(key))) return def;
    return arr->args[i][0];
}

const char *sCmdlineArgStringD(const char *key, int i, const char *def){
    __arr_t *arr;
    if(!(arr = __sFindInArray(key))) return def;
    return arr->args[i];
}

int sCmdlineParse(int *o_argc, char **o_argv){
    int i, j, ignore_args = 0;
    int argc = 1;
    
    for(i=1; i<(*o_argc); i++) {
        if(ignore_args) {
            ignore_args--;
            __sPushArgToArray(o_argv[i], ignore_args);
        } else if(o_argv[i][0] == '-') {
            if(o_argv[i][1] == '-') {
                for(j=0; j<NUM_KEYS; j++) {
                    if(!strcmp(o_argv[i]+2, keys[j].key)) {
                        break;
                    }
                }  
                if(j==NUM_KEYS || (*o_argc)-i-1 < keys[j].num_args) {   /* aka. o_argv[i] not in keys.key */
                    o_argv[argc++] = o_argv[i];
                } else {
                    ignore_args = keys[j].num_args;
                    __sPushToArray(keys[j].key, keys[j].num_args);
                }             
            } else {
                for(j=0; j<NUM_KEYS; j++) {
                    if(!keys[j].skey) continue;
                    if(!strcmp(o_argv[i]+1, keys[j].skey)) {
                        break;
                    }
                }  
                if(j==NUM_KEYS || (*o_argc)-i-1 < keys[j].num_args) {   /* aka. o_argv[i] not in keys.skey */
                    o_argv[argc++] = o_argv[i];
                } else {
                    ignore_args = keys[j].num_args;
                    __sPushToArray(keys[j].key, keys[j].num_args);
                }  
            }
        } else {
            o_argv[argc++] = o_argv[i];
        }
    }
    
    (*o_argc) = argc;
    
    return 0;
}