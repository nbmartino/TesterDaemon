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

extern int extract_kv_pair(const char *source, const char *regexString, char *ret_str, int match_num, int group_num, char *multiBuf);
extern void initCommandRefs();
extern int findCmdIndex(const char *name);
// extern int getParamsCnt(const char *cmdName);

struct CommandObject *CmdObjPtr = NULL;

const char *mid_pattern = REGEX_MID;
const char *cmd_pattern = REGEX_CMD;
const char *params_pattern = REGEX_PARAMS; //"[^\"]+\"|[^\"\\s]+:[[:alpha:]/.]*"; //"[:space:]\"[^\"]+\"|[^\"\\s]+\":\"[^\"]+\"|[^\"\\s]+\"[:space:]";

int runPopen(const char *command, char *retBuf, int bufSize)
{

    size_t bytes_read = 0;
    FILE *pp;

    pp = popen(command, "r");

    if (pp != NULL)
    {
        char buf[bufSize];

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
        log_debug("pOpen failed, command: %s\n", command);
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
        log_debug("PID file does not exist : %s\n", TESTERD_PID_PATH);
        return -1;
    }

    if (runPopen("cat /var/run/testerd.pid", strPID, SM_BUF_LEN) == -1)
    {
        log_debug("cannot read /var/log/testerd.pid\n");
        return -1;
    }
    else
    {
        log_debug("tester.pid path : %s\n", strPID);
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

    log_debug("\nscript path: %s, command: %s\n", script_path, strLocalCmd);

    // strcat(script_path, strLocalCmd);
    // strcat(script_path, " ");

    /* append the script name and add space prior to params*/
    sprintf(script_path, "%s%s ", script_path, strLocalCmd);

    /* params - concatenate param tokens separated by [tab] character
    for (int i = 0; i < cmdDescPtr->paramsCount; i++)
    {
        log_debug("\nCmdObjPtr->strParamTokens: %s\n", CmdObjPtr->strParamTokens);
        strcat(script_path, CmdObjPtr->strParamTokens);
        if ((i + 1) < cmdDescPtr->paramsCount)
        {
            strcat(script_path, "\t");
        }
    }*/

    log_debug("\nstrParamTokens: [%s]\n", CmdObjPtr->strParamTokens);

    /* if param separator if present, enclose the string with "" before sending to script */
    if (strchr(CmdObjPtr->strParamTokens, '\t') != NULL)
    {
        log_debug("\nHas tab seperator\n");
        char tmpBuf[LG_BUF_LEN] = "";

        sprintf(tmpBuf, "%s\"%s\"", script_path, CmdObjPtr->strParamTokens);
        strcpy(script_path, trim(tmpBuf));
    }
    else /* just append the params */
    {
        log_debug("\nNo tab seperator\n");
        strcat(script_path, CmdObjPtr->strParamTokens);
    }
    // 

    log_debug("\nscript path: %s\n", script_path);

    bytesRead = runPopen(script_path, CmdObjPtr->strReplyMsg, SM_BUF_LEN);

    log_debug("\nbytesRead: %d\n", bytesRead);

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
    log_debug("strSrc: %s\n", strSrc);
    char *segment = strtok(strSrc, ":");

    while (segment != NULL)
    {
        strcpy(rcvBuf, segment);
        log_debug("rcvBuf: %s\n", segment);
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

    // if (CmdObjPtr->strParamTokens != NULL)
    //     free(CmdObjPtr->strParamTokens);

    free(CmdObjPtr);
}

void initParamTokens(int paramsCnt)
{
    /*
    log_debug("paramsCnt: %d", paramsCnt);
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

int ProcessMessage(const char *message, char *replyBuf)
{
    int retVal = -1, offset = 0, cmdDescIdx = -1;

    char strCommon[MSG_TOKEN_LEN];

    char strToken[MSG_TOKEN_LEN];

    initCmdObjPtr();

    /* 1. extract MID */
    offset += extract_kv_pair(message + offset, mid_pattern, strToken, 0, 0, NULL);
    copyValueFromToken(strToken, CmdObjPtr->strMID);
    log_debug("str_MID: %s, offset: %d\n", CmdObjPtr->strMID, offset);

    /* 2. extract CMD */
    offset += extract_kv_pair(message + offset, cmd_pattern, strToken, 0, 0, NULL);
    copyValueFromToken(strToken, CmdObjPtr->strCMD);
    log_debug("str_CMD: %s\n", CmdObjPtr->strCMD);

    /* 2.1 check if single instance of CMD only, otherwise raise error */

    /*
     3. verify if trailing params are valid accd to CMD params regex
         -> iterate CMD params pat to see if a pattern matches
     4. if valid params, parse key-value pairs
     */

   
    char multiBuf[LG_BUF_LEN] = "";
    extract_kv_pair(message + offset, params_pattern, strCommon, 0, 0, multiBuf);

    

    /* copy tokens to strTokens */
    strcpy(CmdObjPtr->strParamTokens, trim(multiBuf));

    log_debug("\nmultiBuf: [%s]\n", multiBuf);

    cmdDescIdx = findCmdIndex(CmdObjPtr->strCMD);

    int paramsCnt = cmdDescList[cmdDescIdx].paramsCount;

    //   Initialize params tokens array first
    // initParamTokens(paramsCnt);
    /*  if ( 0 /*paramsCnt == 0)
     {
         if (CmdObjPtr->strParamTokens != NULL)
         {
             free(CmdObjPtr->strParamTokens);
             CmdObjPtr->strParamTokens = NULL; // MEMORY LEAK!!
         }
     }
     else
     { */
    // sprintf(multiBuf, "\"%s\"", multiBuf);
    // strcpy(CmdObjPtr->strParamTokens, multiBuf, strlen(multiBuf));
    // strcpy(CmdObjPtr->strParamTokens, multiBuf);
    /*
strcat(CmdObjPtr->strParamTokens, "\"");
for (int i = 0; i < paramsCnt; i++)
{
    strcat(CmdObjPtr->strParamTokens, strCommon);
    if ((i + 1) < paramsCnt)
    {
        strcat(CmdObjPtr->strParamTokens, "\t");
    }
}
strcat(CmdObjPtr->strParamTokens, "\"");
*/
    //}

    // extract_kv_pair("\"paTH\":/usr/local/pgm.fl nAmE:\"Prog Name\" LOT:GAO12345.1 DEVICE:0HIST001\n", "(\"[^\"\\s\\/\\]*\"|[^\\/\\\"\\s:]+):(\"[^\":]+\"|[A-Za-z0-9\\/.]*)", strCommon, 0, 0);

    // log_debug("str_common: %s\n", strCommon);

    // extract_kv_pair(" LOT:GAO12345.1 DEVICE:0HIST001", "(\"[^\"\\s\\/\\]*\"|[^\\/\\\"]*)?:(\"[^\"]*\"|[^\"]*)?", str_common, 0);
    // extract_kv_pair("\"paTH\":/usr/local/pgm.fl LOT:GAO12345.1    deviCE:0HIST001", "(\\?(\\?=\".*\")(\"[A-Za-z\\s]*\")|([A-Za-z]*)):(\"[^\"]*\"|[A-Za-z0-9\\/.]*)", strCommon, 0, 0);

    // log_debug("str_common: %s\n", strCommon);

    /*
     5. invoke CMD script, pass key value pairs
        parse command name from kv pair
    */

    if (cmdDescIdx != -1)
    {
        retVal = invokeScript(&cmdDescList[cmdDescIdx]);
        // strcpy(CmdInstPtr->strReplyMsg, strToken);
    }
    else
    {
        log_debug("\nCommand index: %d\n", cmdDescIdx);
    }

    /*
      building reply message string
      1. check for " char replace with <quote>, newline with <newline> and missing value = <null>
    */

    /* build reply string */
    sprintf(replyBuf, "MID:%s CMD:%s %s", CmdObjPtr->strMID, CmdObjPtr->strCMD, CmdObjPtr->strReplyMsg);
    // cleanUpParamTokens();
    cleanUpCmdInstPtr();
    /* return reply string size */
    return retVal;
}
