
#include <stdio.h>
#include <string.h>
#include <regex.h>
#include "logging.h"
#include "globaldefs.h"

int extract_kv_pair(const char *source, const char *regexString, char *ret_str, int match_num, int group_num, char *multiBuf, int *hitCount);