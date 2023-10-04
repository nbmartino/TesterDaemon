#include "globaldefs.h"

struct CommandDescriptor
{
    int index;
    int paramsCount;
    char name[CMD_NAME_LEN];
    char **paramsRegex;
};

struct CommandObject
{
    char strMID[MSG_TOKEN_LEN];
    char strCMD[MSG_TOKEN_LEN];
    char strReplyMsg[SM_BUF_LEN];
    char **strParamTokens;

};

struct CommandDescriptor cmdDescList[50];

