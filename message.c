/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, Java, PHP, Ruby, Perl,
C#, OCaml, VB, Swift, Pascal, Fortran, Haskell, Objective-C, Assembly, HTML, CSS, JS, SQLite, Prolog.
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <stdlib.h>
#include <regex.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>
#include "globaldefs.h"
#include "data.h"
#include "logging.h"

extern int extract_kv_pair(const char *source, const char *regexString, char *ret_str, int match_num, int group_num);
extern void initCommandRefs();
extern int findCmdIndex(const char *name);
extern int getParamsCnt(const char *cmdName);

struct CommandObject *CmdObjPtr;

const char *mid_pattern = "^MID:[0-9]*[\\s]*";
const char *cmd_pattern = "[[:space:]]*CMD:[A-Z]*[?]*";
const char *params_pattern = "[^\"]+\"|[^\"\\s]+:[[:alpha:]/.]*"; //"[:space:]\"[^\"]+\"|[^\"\\s]+\":\"[^\"]+\"|[^\"\\s]+\"[:space:]";

int runPopen(const char *command, char *retBuf)
{
   
    size_t bytes_read = 0;
    FILE *pp;

    pp = popen(command, "r");

    if (pp != NULL)
    {
        char buf[60];

        if (fgets(buf, 60, pp) != NULL)
        {
            puts(buf);
            /* get out string len */
            bytes_read = strlen(buf);
            sprintf(retBuf, "%s", buf);
        }

        pclose(pp);
    }

    return (int)bytes_read;
}

int invokeCommand(struct CommandDescriptor *cmdDescPtr)
{
    /* invoke shell and run the script associated to command */

    /* if command string have ? replace with _Q */

    /* shell exec /scripts/path/COMMAND */

    size_t bytesRead = 0;
    FILE *pp;

    char script_path[MSG_TOKEN_LEN] = "/Users/a1234/Documents/testerd/scripts/"; /* temp hack; should fetch from config file */
    char strLocalCmd[CMD_NAME_LEN];
   
    /* convert ? to _Q */
    char *qPtr;
    if( strchr(CmdObjPtr->strCMD, '?') != NULL)
    {
        strncpy( strLocalCmd, CmdObjPtr->strCMD,strlen(CmdObjPtr->strCMD)-1);
        strcat( strLocalCmd, "_Q");
    }

    debug_log("\ncommand: %s script path: %s\n", strLocalCmd, script_path);

    strcat(script_path, strLocalCmd);
    strcat(script_path, " ");
    
    /* params - concatenate param tokens separated by [tab] character */
    for (int i = 0; i < 1; i++)
    {
        strcat(script_path, CmdObjPtr->strParamTokens);
        if ((i + 1) < cmdDescPtr->paramsCount)
        {
            strcat(script_path, "\t");
        }
    }

    debug_log("\nscript path: %s\n", script_path);

     bytesRead = runPopen(script_path, CmdObjPtr->strReplyMsg);

   /*  pp = popen(script_path, "r");

    if (pp != NULL)
    {
        char buf[60];

        if (fgets(buf, 60, pp) != NULL)
        {
            puts(buf);

            bytes_read = strlen(buf);
            sprintf(CmdObjPtr->strReplyMsg, "%s", buf);
        }

        pclose(pp);
    } */

    return (int)bytesRead;
}

int copyValueFromToken(const char *strSrc, char *rcvBuf)
{

    char tmp[MSG_TOKEN_LEN];
    debug_log("strSrc: %s\n", strSrc);
    char *segment = strtok(strSrc, ":");

    while (segment != NULL)
    {
        strcpy(rcvBuf, segment);
        debug_log("rcvBuf: %s\n", segment);
        segment = strtok(NULL, ":");
    }

    return strlen(rcvBuf);
}

void initCmdObjPtr()
{
    CmdObjPtr = (struct CommandObject *)malloc(sizeof(struct CommandObject));
}

void cleanUpCmdInstPtr()
{
    if (CmdObjPtr == NULL)
        return;

    if (CmdObjPtr->strParamTokens != NULL)
        free(CmdObjPtr->strParamTokens);

    free(CmdObjPtr);
}

void initParamTokens(int paramsCnt)
{

    CmdObjPtr->strParamTokens = malloc(paramsCnt * (MSG_TOKEN_LEN + sizeof(char *)));
    strcpy(CmdObjPtr->strParamTokens, "");
}

int ProcessMessage(const char *message)
{
    int retVal = -1, offset = 0, index = -1;

    char strCommon[MSG_TOKEN_LEN];

    char strToken[MSG_TOKEN_LEN];

    initCmdObjPtr();

    /* 1. extract MID */
    offset += extract_kv_pair(message + offset, mid_pattern, strToken, 0, 0);
    copyValueFromToken(strToken, CmdObjPtr->strMID);
    debug_log("str_MID: %s, offset: %d\n", CmdObjPtr->strMID, offset);

    /* 2. extract CMD */
    offset += extract_kv_pair(message + offset, cmd_pattern, strToken, 0, 0);
    copyValueFromToken(strToken, CmdObjPtr->strCMD);
    debug_log("str_CMD: %s\n", CmdObjPtr->strCMD);

    /* 2.1 check if single instance of CMD only, otherwise raise error */

    /*
     3. verify if trailing params are valid accd to CMD params regex
         -> iterate CMD params pat to see if a pattern matches
     4. if valid params, parse key-value pairs
     */

    extract_kv_pair(message + offset, "(\"[^\"\\s\\/\\]*\"|[^\\/\\\"\\s:]+):(\"[^\":]+\"|[A-Za-z0-9\\/.]*)", strCommon, 0, 0);
    debug_log(" param token: %s\n", strCommon);
    // int paramsCnt = getParamsCnt(CmdInstPtr->strCMD);
    //   Initialize params tokens array first

    initParamTokens(2); // temp hack

    strcat(CmdObjPtr->strParamTokens, "\"");
    for (int i = 0; i < 2; i++)
    {
        strcat(CmdObjPtr->strParamTokens, strCommon);
        if ((i + 1) < 2)
        {
            strcat(CmdObjPtr->strParamTokens, "\t");
        }
    }

    strcat(CmdObjPtr->strParamTokens, "\"");
    extract_kv_pair("\"paTH\":/usr/local/pgm.fl nAmE:\"Prog Name\" LOT:GAO12345.1 DEVICE:0HIST001\n", "(\"[^\"\\s\\/\\]*\"|[^\\/\\\"\\s:]+):(\"[^\":]+\"|[A-Za-z0-9\\/.]*)", strCommon, 0, 0);

    debug_log("str_common: %s\n", strCommon);

    // extract_kv_pair(" LOT:GAO12345.1 DEVICE:0HIST001", "(\"[^\"\\s\\/\\]*\"|[^\\/\\\"]*)?:(\"[^\"]*\"|[^\"]*)?", str_common, 0);
    extract_kv_pair("\"paTH\":/usr/local/pgm.fl LOT:GAO12345.1    deviCE:0HIST001", "(\\?(\\?=\".*\")(\"[A-Za-z\\s]*\")|([A-Za-z]*)):(\"[^\"]*\"|[A-Za-z0-9\\/.]*)", strCommon, 0, 0);

    debug_log("str_common: %s\n", strCommon);

    /*
     5. invoke CMD script, pass key value pairs
        parse command name from kv pair
    */

    index = findCmdIndex(CmdObjPtr->strCMD);
    if (index != -1)
    {
        retVal = invokeCommand(CmdObjPtr);
        // strcpy(CmdInstPtr->strReplyMsg, strToken);
    }
    else
    {
        debug_log("\nCommand index: %d\n", index);
    }

    /*
      building reply message string
      1. check for " char replace with <quote>, newline with <newline> and missing value = <null>
    */

    /* build reply string */
    /* return reply string size */

    cleanUpCmdInstPtr();

    return retVal;
}
