#include "logging.h"

#define SM_BUF_LEN 1024
#define LG_BUF_LEN 4096
#define MSG_TOKEN_LEN 1024
#define CMD_NAME_LEN 64
#define PARAMS_REGEX_LEN 128
#define RET_STR_LEN 1024

#define TESTERD_PID_PATH "/var/run/testerd.pid"
#define PROD_HOME_DIR "/usr/prod/testerd"
#define PARAM_SEPARATOR "\t"

#define REGEX_MID "^MID:[0-9]*[\\s]*"
#define REGEX_CMD "[[:space:]]*CMD:[A-Z]*[?]*"
/* #define REGEX_PARAMS "(\"[^\"\\s\\/\\]*\"|[^\\/\\\"\\s:]+):(\"[^\":]+\"|[A-Za-z0-9\\/.]*)"*/
#define REGEX_PARAMS "(\"[^\"\\s\\/\\]*\"|[A-Za-z0-9\\/.]*):(\"[^\":]+\"|[A-Za-z0-9\\/.,_]*)"
