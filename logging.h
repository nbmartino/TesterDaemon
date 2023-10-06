#include <stdio.h>

#define DEBUG_MODE

#ifdef DEBUG_MODE
#define log_debug(...) ( printf("[%s] ", __func__), printf(__VA_ARGS__) )
#else
#define log_debug(...)
#endif