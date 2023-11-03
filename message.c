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
#include <unistd.h>
#include "globaldefs.h"
#include "data.h"
#include "logging.h"
#include "utility.h"

extern int extract_kv_pair(const char *source, const char *regexString, char *ret_str, int match_num, int group_num, char *multiBuf, int *hitCount);
extern void initCommandRefs();
extern int findCmdIndex(const char *name);
extern int gSlaveId;
extern int WriteToSocket(const int sock, const char *const buffer,
				  const size_t buflen)
/* extern int getParamsCnt(const char *cmdName); */

struct CommandObject *CmdObjPtr = NULL;

const char *mid_pattern = REGEX_MID;
const char *cmd_pattern = REGEX_CMD;
const char *params_pattern = REGEX_PARAMS; /* "[^\"]+\"|[^\"\\s]+:[[:alpha:]/.]*"; "[:space:]\"[^\"]+\"|[^\"\\s]+\":\"[^\"]+\"|[^\"\\s]+\"[:space:]"; */

int runPopen(const char *command, char *retBuf, int bufSize)
{

    size_t bytes_read = 0;
    FILE *pp;

    pp = popen(command, "r");

    if (pp != NULL)
    {
        char buf[RET_STR_LEN];

        if (fgets(buf, bufSize, pp) != NULL)
        {
            puts(buf);
            /* get out string len */
            bytes_read = strlen(buf);
            sprintf(retBuf, "%s", buf);
        }

        pclose(pp);
    }
    else
    {
        sprintf(logMsg,"pOpen failed, command: %s\n", command);
        logDebug(logMsg);
    }

    return (int)bytes_read;
}

int invokeScript(struct CommandDescriptor *cmdDescPtr)
{
    /* invoke shell and run the script associated to command */

    /* if command string have ? replace with _Q */

    /* shell exec /scripts/path/COMMAND */

    size_t bytesRead = 0;

    char script_path[SM_BUF_LEN] = "";
    char strLocalCmd[CMD_NAME_LEN] = "";
    char strPID[32] = {0};

    /* retrieve exe path to locate command scripts folder

    if (access(TESTERD_PID_PATH, F_OK) != 0)
    {
        sprintf(logMsg,"PID file does not exist : %s\n", TESTERD_PID_PATH);
        log_debug(logMsg);
        return -1;
    }

    if (runPopen("cat /var/run/testerd.pid", strPID, SM_BUF_LEN) == -1)
    {
        sprintf(logMsg,"cannot read /var/log/testerd.pid\n");
        log_debug(logMsg);
        return -1;
    }
    else
    {
        sprintf(logMsg,"tester.pid path : %s\n", strPID);
        log_debug(logMsg);
    }
 */

#ifdef __MACH__
    strcpy(script_path, "/Users/a1234/Documents/testerd/scripts/"); /* for improvement, should fetch from config file */
#else
#if defined(sun) || defined(__sun)
#if defined(__SVR4) || defined(__svr4__)
    /* Solaris */
    sprintf(script_path, "%s/scripts/", PROD_HOME_DIR);
#else
    /* SunOS */
    sprintf(script_path, "%s/scripts/", PROD_HOME_DIR);
#endif
#endif

#endif

    /* convert ? to _Q */

    if (strchr(CmdObjPtr->strCMD, '?') != NULL)
    {
        strncpy(strLocalCmd, CmdObjPtr->strCMD, strlen(CmdObjPtr->strCMD) - 1);
        strcat(strLocalCmd, "_Q");
    }
    else
    {
        strcpy(strLocalCmd, CmdObjPtr->strCMD);
    }

    sprintf(logMsg,"\nscript path: %s, command: %s\n", script_path, strLocalCmd);
    logDebug(logMsg);

    /* strcat(script_path, strLocalCmd);
    strcat(script_path, " "); */

    /* append the script name and add space prior to params*/
    sprintf(script_path, "%s%s ", script_path, strLocalCmd);

    /* params - concatenate param tokens separated by [tab] character
    for (int i = 0; i < cmdDescPtr->paramsCount; i++)
    {
        sprintf(logMsg,"\nCmdObjPtr->strParamTokens: %s\n", CmdObjPtr->strParamTokens);
        log_debug(logMsg);
        strcat(script_path, CmdObjPtr->strParamTokens);
        if ((i + 1) < cmdDescPtr->paramsCount)
        {
            strcat(script_path, "\t");
        }
    }*/

    sprintf(logMsg,"\nstrParamTokens: [%s]\n", CmdObjPtr->strParamTokens);
    logDebug(logMsg);
    /* if param separator if present, enclose the string with "" before sending to script */
    if (strchr(CmdObjPtr->strParamTokens, '\t') != NULL)
    {
        sprintf(logMsg,"\nHas tab separator\n");
        logDebug(logMsg);
        sprintf(script_path, "%s\"%s\"", script_path, CmdObjPtr->strParamTokens);
    }
    else /* just append the params */
    {
        sprintf(logMsg,"\nNo tab separator\n");
        logDebug(logMsg);
        strcat(script_path, CmdObjPtr->strParamTokens);
    }
    

    sprintf(logMsg,"\nscript path: %s\n", script_path);
    logDebug(logMsg);

    bytesRead = runPopen(script_path, CmdObjPtr->strReplyMsg, SM_BUF_LEN);

    sprintf(logMsg,"\nbytesRead: %lu\n", bytesRead);
    logDebug(logMsg);

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

int copyValueFromToken(char *strSrc, char *rcvBuf)
{

    char tmp[MSG_TOKEN_LEN];
    char *segment;

    sprintf(logMsg,"strSrc: %s\n", strSrc);
    logDebug(logMsg);
    
    segment = strtok(strSrc, ":");

    while (segment != NULL)
    {
        strcpy(rcvBuf, segment);
        sprintf(logMsg,"rcvBuf: %s\n", segment);
        logDebug(logMsg);
        segment = strtok(NULL, ":");
    }

    return strlen(rcvBuf);
}

void initCmdObjPtr()
{
    CmdObjPtr = (struct CommandObject *)malloc(sizeof(struct CommandObject));
    if (CmdObjPtr)
    {
        strcpy(CmdObjPtr->strMID, "");
        strcpy(CmdObjPtr->strCMD, "");
        strcpy(CmdObjPtr->strReplyMsg, "");
        strcpy(CmdObjPtr->strParamTokens, "");
    }
}

void cleanUpCmdInstPtr()
{
    if (CmdObjPtr == NULL)
        return;

    /* if (CmdObjPtr->strParamTokens != NULL)
         free(CmdObjPtr->strParamTokens); */

    free(CmdObjPtr);
}

void initParamTokens(int paramsCnt)
{
    /*
    sprintf(logMsg,"paramsCnt: %d", paramsCnt);
    log_debug(logMsg);
    if (paramsCnt > 0)
    {
        CmdObjPtr->strParamTokens = malloc(paramsCnt * (MSG_TOKEN_LEN + sizeof(char *)));
        strcpy(CmdObjPtr->strParamTokens, "");
    }
    else
    {
        CmdObjPtr->strParamTokens = NULL;
    }*/
}

void cleanUpParamTokens()
{
    /*  if (CmdObjPtr->strParamTokens != NULL)
     {
         free(CmdObjPtr->strParamTokens);
     } */
}

int ProcessMessage(char *message)
{
    int retVal = -1, cmdDescIdx = -1, hitCount;
    int offset = 0, offsetMID = 0, offsetCMD = 0;
    char strCommon[MSG_TOKEN_LEN];
    char strToken[MSG_TOKEN_LEN];
    char strAck[MSG_TOKEN_LEN];
    char multiBuf[LG_BUF_LEN];

    sprintf(logMsg,"\n===============================================\n");
    logDebug(logMsg);

    initCmdObjPtr();

    /* 1. extract MID */
    offset += extract_kv_pair(message + offset, mid_pattern, strToken, 0, 0, NULL, &hitCount);
    offsetMID = offset;
    copyValueFromToken(strToken, CmdObjPtr->strMID);

    /* if MID is determined, send acknowledgment */
    sprintf( strAck,"%s ANSWER:ACK", CmdObjPtr->strMID);
    WriteToSocket( gSlaveId, CmdObjPtr->strMID, strlen(CmdObjPtr->strMID));
    
    sprintf(logMsg,"str_MID: %s, offset: %d\n", CmdObjPtr->strMID, offset);
    logDebug(logMsg);

    /* 2. extract CMD */
    offset += extract_kv_pair(message + offset, cmd_pattern, strToken, 0, 0, NULL, &hitCount);
    offsetCMD = offset;
    copyValueFromToken(strToken, CmdObjPtr->strCMD);
    sprintf(logMsg,"str_CMD: %s\n", CmdObjPtr->strCMD);
    logDebug(logMsg);

    /* if there is another command, cut the process short and send error message */
    if (hitCount > 1)
    {
        sprintf(logMsg,"\nerror! multiple commands in one message. retVal== %d\n", retVal);
        logDebug(logMsg);

        message[offsetCMD + 1] = '\0'; /* end of command name plus 1 == space char */
        strcat(message, "ERROR:\"Multiple commands in one message.\"");
        return -1;
    }

    /* if unknown command, cut the process short and send error message */
    cmdDescIdx = findCmdIndex(CmdObjPtr->strCMD);
    if (cmdDescIdx == -1)
    {
        sprintf(logMsg,"\nerror! unknown command.\n");
        logDebug(logMsg);

        message[offsetCMD + 1] = '\0'; /* end of command name plus 1 == space char */
        strcat(message, "ERROR:\"Unknown command.\"");
        return -1;
    }

    /*
     3. verify if trailing params are valid accd to CMD params regex
         -> iterate CMD params pat to see if a pattern matches
     4. if valid params, parse key-value pairs
     */


    strcpy(multiBuf,"");

    extract_kv_pair(message + offset, params_pattern, strCommon, 0, 0, multiBuf, &hitCount);

    /* copy tokens to strTokens */
    strcpy(CmdObjPtr->strParamTokens, trim(multiBuf));

    sprintf(logMsg,"\nmultiBuf: [%s]\n", multiBuf);
    logDebug(logMsg);

    /* int paramsCnt = cmdDescList[cmdDescIdx].paramsCount; */

    /*
     5. invoke CMD script, pass key value pairs
        parse command name from kv pair
    */

    retVal = invokeScript(&cmdDescList[cmdDescIdx]);
    /* strcpy(CmdInstPtr->strReplyMsg, strToken); */

    /*
      building reply message string
      1. check for " char replace with <quote>, newline with <newline> and missing value = <null>
    */

    /* build reply string */
    /* truncate orig buffer upto end on command KV token and a space */
    message[offsetCMD + 1] = '\0';
    strcat(message, CmdObjPtr->strReplyMsg);
    /* sprintf(replyBuf, "MID:%s CMD:%s %s", CmdObjPtr->strMID, CmdObjPtr->strCMD, CmdObjPtr->strReplyMsg);
    cleanUpParamTokens(); */
    cleanUpCmdInstPtr();
    /* return reply string size */
    return retVal;
}
