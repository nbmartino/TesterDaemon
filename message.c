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

struct CommandInstance CmdInst;


#define CMD_NAME_LEN2 64

struct Command2
{
    char name[CMD_NAME_LEN2];
    char **params_pat;
    // params_pat[0] = "regex..";
    // params_pat[1] = "regex2.."
};

const char *mid_pattern = "^MID:[0-9]*[\\s]*";
const char *cmd_pattern = "[[:space:]]*CMD:[A-Z]*[?]*";
const char *params_pattern = "[^\"]+\"|[^\"\\s]+:[[:alpha:]/.]*"; //"[:space:]\"[^\"]+\"|[^\"\\s]+\":\"[^\"]+\"|[^\"\\s]+\"[:space:]";

int invokeCommand(const char *command, char *reply_buf)
{
    // invoke shell and run the script associated to command

    // if command string have ? replace with _Q

    // shell exec /scripts/path/COMMAND

    size_t bytes_read = 0;

    FILE *pp;

    char script_path[MSG_TOKEN_LEN] = "/Users/a1234/Documents/testerd/scripts/";

    //sscanf(script_path, "%s%s", script_path, command);

    printf("\ncommand: %s script path: %s\n", command, script_path);

    strcat(script_path, command);
    // params
    strcat(script_path, " ]from_exec");
    printf("\nscript path: %s\n", script_path);

    pp = popen(script_path, "r");
    if (pp != NULL)
    {
        char buf[60];

        if (fgets(buf, 60, pp) != NULL)
        {

            puts(buf);
            /* get out string len */
            bytes_read = strlen(buf);
            sprintf(reply_buf, "%s", buf);
        }

        pclose(pp);
    }
    return (int) bytes_read;
}

int copyValueFromToken(const char *strSrc, char *rcvBuf)
{

    char tmp[MSG_TOKEN_LEN];
    printf("strSrc: %s\n", strSrc);
    char *segment = strtok(strSrc, ":");

    while (segment != NULL)
    {
        strcpy(rcvBuf, segment);
        printf("rcvBuf: %s\n", segment);
        segment = strtok(NULL, ":");
    }

    return strlen(rcvBuf);
}

int ProcessMessage(const char *message)
{
    int retVal = -1, offset = 0, index = -1;

    char strCommon[MSG_TOKEN_LEN];

    char strToken[MSG_TOKEN_LEN];

    /*
    1. extract MID
    */

    // extract_key_val(message, mid_pattern, str_MID, 1);
    offset = extract_kv_pair(message + offset, mid_pattern, strToken, 0, 0);
    copyValueFromToken(strToken, CmdInst.strMID);
    debug_log("str_MID: %s, offset: %d\n", CmdInst.strMID, offset);
    //printf("str_MID: %s, offset: %d\n", CmdInst.strMID, offset);

    /*
    2. extract CMD
    2.1 check if single instance of CMD only, otherwise raise error
    */
    offset = extract_kv_pair(message + offset, cmd_pattern, strToken, 0, 0);
    copyValueFromToken(strToken, CmdInst.strCMD);
    printf("str_CMD: %s\n", CmdInst.strCMD);

    /*
     3. verify if trailing params are valid accd to CMD params regex
         -> iterate CMD params pat to see if a pattern matches
     4. if valid params, parse key-value pairs
     */
    extract_kv_pair("\"paTH\":/usr/local/pgm.fl nAmE:\"Prog Name\" LOT:GAO12345.1 DEVICE:0HIST001\n", "(\"[^\"\\s\\/\\]*\"|[^\\/\\\"\\s:]+):(\"[^\":]+\"|[A-Za-z0-9\\/.]*)", strCommon, 0, 0);

    printf("str_common: %s\n", strCommon);

    // extract_kv_pair(" LOT:GAO12345.1 DEVICE:0HIST001", "(\"[^\"\\s\\/\\]*\"|[^\\/\\\"]*)?:(\"[^\"]*\"|[^\"]*)?", str_common, 0);
    extract_kv_pair("\"paTH\":/usr/local/pgm.fl LOT:GAO12345.1    deviCE:0HIST001", "(\\?(\\?=\".*\")(\"[A-Za-z\\s]*\")|([A-Za-z]*)):(\"[^\"]*\"|[A-Za-z0-9\\/.]*)", strCommon, 0, 0);

    printf("str_common: %s\n", strCommon);

    /*
   
    */
    /*

     5. invoke CMD script, pass key value pairs
   
    // parse command name from kv pair
    */

    index = findCmdIndex(CmdInst.strCMD);
    if (index != -1)
    {
        retVal = invokeCommand(CmdInst.strCMD, strToken);
        strcpy(CmdInst.strReplyMsg, strToken);
    }
    else
    {
        printf("\nCommand index: %d\n", index);
    }
    /*
      building reply message string
      1. check for " char replace with <quote>, newline with <newline> and missing value = <null>
      */

    // build reply string
    // return reply string size

    return retVal;
}

