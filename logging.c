#include <string.h>
#include <stdio.h>
#include "logging.h"

void logDebug(const char *msg)
{
    char cmd[LOGS_MSG_LEN];

#ifdef DEBUG_MODE
    strcpy(cmd,"echo $(date '+%Y%m%d_%H-%M-%S') \"");
    strcat(cmd, msg);
    strcat(cmd, "\" >> $HOME/testerd.log");
    system(cmd);
#endif
}

void logError(const char *msg)
{
    char cmd[LOGS_MSG_LEN];

#ifdef DEBUG_MODE
    strcpy(cmd,"echo date '+%Y%m%d%H%M%S' \"");
    strcat(cmd, msg);
    strcat(cmd, "\" >> $HOME/testerd.log");
    /* printf("\n%s\n", cmd); */
    system(cmd);
#endif
}
