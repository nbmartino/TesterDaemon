#include "globaldefs.h"

struct CommandReference
{
    int index;
    int paramsCount;
    char name[CMD_NAME_LEN];
    char **paramsRegex;
};

struct CommandInstance
{
    char strMID[MSG_TOKEN_LEN];
    char strCMD[MSG_TOKEN_LEN];
    char **strParamTokens;

};

struct CommandReference cmdRefList[50];

