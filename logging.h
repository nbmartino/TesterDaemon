#include <stdio.h>

#define DEBUG_MODE

#ifdef DEBUG_MODE
#define debug_log(...) ( printf("[%s] ", __func__), printf(__VA_ARGS__) )
#else
#define debug_log(...)
#endif