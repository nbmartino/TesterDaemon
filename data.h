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
    char strParamTokens[LG_BUF_LEN];

};

struct CommandDescriptor cmdDescList[60];

