
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include "data.h"

extern void initCommandRefs();
extern void cleanUpCommandRefs();
extern int ProcessMessage(char *message);
extern struct CommandObject *CmdObjPtr;

int main(int argc, char *argv[])
{
    char pat[] = "/^MID:\\w+\\s+CMD:\\w+\\s+\\b[A-Z]{2,}\\b:[\\w\\s]+(?:\\s+\\b[A-Z]{2,}\\b:[\\w\\s]+)*\\\\n|$/gm";
    char data[] = {"MiD:123 CMD:PrGn paTH:/usr/local/pgm.fl nAmE:\"Prog Name\" \n"};
    char replyMsg[LG_BUF_LEN];
    char msgBuf[LG_BUF_LEN];
    char key[64] = {0};
    char val[64] = {0};
    int retVal;

    initCommandRefs();

    /* Tests */

    /* ACCSLEVEL */
    strcpy(msgBuf,"MID:1 CMD:ACCSLEVEL LEVEL:OPERATOR\n");
    retVal = ProcessMessage(msgBuf);
    printf("Response message: %s\n", msgBuf);

    /* ACCSLEVEL_Q */
    strcpy(msgBuf,"MID:1 CMD:ACCSLEVEL?\n");
    retVal = ProcessMessage(msgBuf);
    printf("Response message: %s\n", msgBuf);

    /* PRGN */
    strcpy(msgBuf, "MID:1 CMD:PRGN PATH:/home/src/TP23976 NAME:DCYTTT34.dll\n");
    retVal = ProcessMessage(msgBuf);
    printf("Response message: %s\n", msgBuf);

    /* PRGN_Q */
    strcpy(msgBuf,"MID:1 CMD:PRGN?\n");
    retVal = ProcessMessage(msgBuf);
    printf("Response message: %s\n", msgBuf);

    /* LOT */
    strcpy(msgBuf,"MID:1 CMD:LOT LOT:GM89463.1A\n");
    retVal = ProcessMessage(msgBuf);
    printf("Response message: %s\n", msgBuf);

    /* LOT_Q */
    strcpy(msgBuf,"MID:1 CMD:LOT?\n");
    retVal = ProcessMessage(msgBuf);
    printf("Response message: %s\n", msgBuf);

    /* DEVICE */
    strcpy(msgBuf,"MID:1 CMD:DEVICE DEVICE:WT6MC3307400N\n");
    retVal = ProcessMessage(msgBuf);
    printf("Response message: %s\n", msgBuf);

    /* DEVICE_Q */
    strcpy(msgBuf,"MID:1 CMD:DEVICE?\n");
    retVal = ProcessMessage(msgBuf);
    printf("Response message: %s\n", msgBuf);

    /* TESTMODE */
    strcpy(msgBuf, "MID:1 CMD:TESTMODE MODE:QA\n");
    retVal = ProcessMessage(msgBuf);
    printf("Response message: %s\n", msgBuf);

    /* TESTMODE_Q */
    strcpy(msgBuf,"MID:1 CMD:TESTMODE?\n");
    retVal = ProcessMessage(msgBuf);
    printf("Response message: %s\n", msgBuf);

    /* PCSITES */
    strcpy(msgBuf,"MID:1 CMD:PCSITES PCSITES:X000Y000,X000Y001,X000Y002\n");
    retVal = ProcessMessage(msgBuf);
    printf("Response message: %s\n", msgBuf);

    /* PCSITES_Q */
    strcpy(msgBuf,"MID:1 CMD:PCSITES?\n");
    retVal = ProcessMessage(msgBuf);
    printf("Response message: %s\n", msgBuf);

    /* PBCARD */
    strcpy(msgBuf,"MID:1 CMD:PBCARD PBCARD:PC_01546\n");
    retVal = ProcessMessage(msgBuf);
    printf("Response message: %s\n", msgBuf);

    /* PBCARD_Q */
    strcpy(msgBuf,"MID:1 CMD:PBCARD?\n");
    retVal = ProcessMessage(msgBuf);
    printf("Response message: %s\n", msgBuf);

    /* LDBRD */
    strcpy(msgBuf,"MID:1 CMD:LDBRD LOADBOARD:LB98765AB\n");
    retVal = ProcessMessage(msgBuf);
    printf("Response message: %s\n", msgBuf);

    /* LDBRD_Q */
    strcpy(msgBuf,"MID:1 CMD:LDBRD?\n");
    retVal = ProcessMessage(msgBuf);
    printf("Response message: %s\n", msgBuf);
return 0;
    /* DLNAME */
    strcpy(msgBuf,"MID:1 CMD:DLNAME PATH:\"/home/app/log\" NAME:\"ETS300_2014_01_29\"\n");
    retVal = ProcessMessage(msgBuf);
    printf("Response message: %s\n", msgBuf);

    /* DLOGI */
    strcpy(msgBuf,"MID:1 CMD:DLOGI INTERVAL:5\n");
    retVal = ProcessMessage(msgBuf);
    printf("Response message: %s\n", msgBuf);

    /* DLOGI_Q */
    strcpy(msgBuf,"MID:1 CMD:DLOGI?\n");
    retVal = ProcessMessage(msgBuf);
    printf("Response message: %s\n", msgBuf);

    /* DLSTART */
    strcpy(msgBuf,"MID:1 CMD:DLSTART\n");
    retVal = ProcessMessage(msgBuf);
    printf("Response message: %s\n", msgBuf);

    /* WFR */
    strcpy(msgBuf,"MID:1 CMD:WFR WAFER:01\n");
    retVal = ProcessMessage(msgBuf);
    printf("Response message: %s\n", msgBuf);

    /* WFR_Q */
    strcpy(msgBuf,"MID:1 CMD:WFR?\n");
    retVal = ProcessMessage(msgBuf);
    printf("Response message: %s\n", msgBuf);

    /* SOT */
    strcpy(msgBuf,"MID:1 CMD:SOT X:041 Y:158 S:011 MODULE:ABC_1 MODULEX:0 MODULEY:700");
    retVal = ProcessMessage(msgBuf);
    printf("Response message: %s\n", msgBuf);

    /* EOW */
    strcpy(msgBuf,"MID:1 CMD:EOW\n");
    retVal = ProcessMessage(msgBuf);
    printf("Response message: %s\n", msgBuf);

    /* DLEND */
    strcpy(msgBuf,"MID:1 CMD:DLEND\n");
    retVal = ProcessMessage(msgBuf);
    printf("Response message: %s\n", msgBuf);

    /* EOL */
    strcpy(msgBuf,"MID:1 CMD:EOL\n");
    retVal = ProcessMessage(msgBuf);
    printf("Response message: %s\n", msgBuf);

    /* SCRIBE */
    strcpy(msgBuf,"MID:1 CMD:SCRIBE SCRIBE:\"GM28912-02-1A EC\"\n");
    retVal = ProcessMessage(msgBuf);
    printf("Response message: %s\n", msgBuf);

    /* SCRIBE_Q */
    strcpy(msgBuf,"MID:1 CMD:SCRIBE?\n");
    retVal = ProcessMessage(msgBuf);
    printf("Response message: %s\n", msgBuf);

    /* "MID:1 CMD:TESTERLOCK LOCK:TRUE\n" */
    /* retVal  = ProcessMessage("MID:1 CMD:TESTERLOCK LOCK:TRUE\n", msgBuf);
     printf("Response message: %s\n", msgBuf);

    
    Test for these:
     BIN_YIELD_LIMIT:1 95 2 60 ANOTHER_LIST: a b c
    ERROR_MSG:”something is wrong”
    ”ERROR MSG”:”something is wrong”
    “C:\Test/test\program\path/testProgram.ext”
    */

    /* cleanUpCommandRefs(); */
    return 0;
}
