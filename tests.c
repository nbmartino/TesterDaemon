
#include <assert.h>
#include <stdio.h>
#include "data.h"

extern void initCommandRefs();
extern void cleanUpCommandRefs();
extern int ProcessMessage(const char *message, char *replyBuf);
extern struct CommandObject *CmdObjPtr;

int main(int argc, char *argv[])
{
    char pat[] = "/^MID:\\w+\\s+CMD:\\w+\\s+\\b[A-Z]{2,}\\b:[\\w\\s]+(?:\\s+\\b[A-Z]{2,}\\b:[\\w\\s]+)*\\\\n|$/gm";
    char data[] = {"MiD:123 CMD:PrGn paTH:/usr/local/pgm.fl nAmE:\"Prog Name\" \n"};
    char replyMsg[LG_BUF_LEN];
    char key[64] = {0};
    char val[64] = {0};
    int retVal;

    initCommandRefs();

    /* Tests */

    /* ACCSLEVEL */
    //retVal = ProcessMessage("MID:1 CMD:ACCSLEVEL LEVEL:OPERATOR\n", replyMsg);
    //printf("After invoking command, reply string: %s\n", replyMsg);

    /* ACCSLEVEL_Q */
    //retVal = ProcessMessage("MID:1 CMD:ACCSLEVEL?\n", replyMsg);
    //printf("After invoking command, reply string: %s\n", replyMsg);

    /* PRGN */
    retVal = ProcessMessage("MID:1 CMD:PRGN PATH:/home/src/TP23976 NAME:DCYTTT34.dll\n", replyMsg);
    printf("After invoking command, reply string: %s\n", replyMsg);

return 0;
   

    /* PRGN_Q */
    retVal = ProcessMessage("MID:1 CMD:PRGN?\n", replyMsg);
    printf("After invoking command, reply string: %s\n", replyMsg);

    /* LOT */
    retVal = ProcessMessage("MID:1 CMD:LOT LOT:GM89463.1A\n", replyMsg);
    printf("After invoking command, reply string: %s\n", replyMsg);

    /* LOT_Q */
    retVal = ProcessMessage("MID:1 CMD:LOT?\n", replyMsg);
    printf("After invoking command, reply string: %s\n", replyMsg);

    /* DEVICE */
    retVal = ProcessMessage("MID:1 CMD:DEVICE DEVICE:WT6MC3307400N\n", replyMsg);
    printf("After invoking command, reply string: %s\n", replyMsg);

    /* DEVICE_Q */
    retVal = ProcessMessage("MID:1 CMD:DEVICE?\n", replyMsg);
    printf("After invoking command, reply string: %s\n", replyMsg);

    /* TESTMODE */
    retVal = ProcessMessage("MID:1 CMD:TESTMODE MODE:QA\n", replyMsg);
    printf("After invoking command, reply string: %s\n", replyMsg);

    /* TESTMODE_Q */
    retVal = ProcessMessage("MID:1 CMD: TESTMODE?\n", replyMsg);
    printf("After invoking command, reply string: %s\n", replyMsg);

    /* PCSITES */
    retVal = ProcessMessage("MID:1 CMD:PCSITES PCSITES:X000Y000,X000Y001,X000Y002\n", replyMsg);
    printf("After invoking command, reply string: %s\n", replyMsg);

    /* PCSITES_Q */
    retVal = ProcessMessage("MID:1 CMD:PCSITES?\n", replyMsg);
    printf("After invoking command, reply string: %s\n", replyMsg);

    /* PBCARD */
    retVal = ProcessMessage("MID:1 CMD:PBCARD PBCARD:PC_01546\n", replyMsg);
    printf("After invoking command, reply string: %s\n", replyMsg);

    /* PBCARD_Q */
    retVal = ProcessMessage("MID:1 CMD:PBCARD?\n", replyMsg);
    printf("After invoking command, reply string: %s\n", replyMsg);

    /* LDBRD */
    // retVal = ProcessMessage("", replyMsg);
    // printf("After invoking command, reply string: %s\n", replyMsg);

    /* DLNAME */
    retVal = ProcessMessage("MID:1 CMD:DLNAME PATH:\"/home/app/log\" NAME:\"ETS300_2014_01_29\"\n", replyMsg);
    printf("After invoking command, reply string: %s\n", replyMsg);

    /* DLOGI */
    retVal = ProcessMessage("MID:1 CMD:DLOGI INTERVAL:5\n", replyMsg);
    printf("After invoking command, reply string: %s\n", replyMsg);

    /* DLOGI_Q */
    retVal = ProcessMessage("MID:1 CMD:DLOGI?\n", replyMsg);
    printf("After invoking command, reply string: %s\n", replyMsg);

    /* DLSTART */
    retVal = ProcessMessage("MID:1 CMD:DLSTART\n", replyMsg);
    printf("After invoking command, reply string: %s\n", replyMsg);

    /* WFR */
    retVal = ProcessMessage("MID:1 CMD:WFR WAFER:01\n", replyMsg);
    printf("After invoking command, reply string: %s\n", replyMsg);

    /* WFR_Q */
    retVal = ProcessMessage("MID:1 CMD:WFR?\n", replyMsg);
    printf("After invoking command, reply string: %s\n", replyMsg);

    /* SOT */
    retVal = ProcessMessage("MID:1 CMD:SOT X:041 Y:158 S:011 MODULE:ABC_1 MODULEX:0 MODULEY:700", replyMsg);
    printf("After invoking command, reply string: %s\n", replyMsg);

    /* EOW */
    retVal = ProcessMessage("MID:1 CMD:EOW\n", replyMsg);
    printf("After invoking command, reply string: %s\n", replyMsg);

    /* DLEND */
    retVal = ProcessMessage("MID:1 CMD:DLEND\n", replyMsg);
    printf("After invoking command, reply string: %s\n", replyMsg);

    /* EOL */
    retVal = ProcessMessage("MID:1 CMD:EOL\n", replyMsg);
    printf("After invoking command, reply string: %s\n", replyMsg);

    /* SCRIBE */
    retVal = ProcessMessage("MID:1 CMD:SCRIBE SCRIBE:\"GM28912-02-1A EC\"\n", replyMsg);
    printf("After invoking command, reply string: %s\n", replyMsg);

    /* SCRIBE_Q */
    retVal = ProcessMessage("MID:1 CMD:SCRIBE?\n", replyMsg);
    printf("After invoking command, reply string: %s\n", replyMsg);

    /* "MID:1 CMD:TESTERLOCK LOCK:TRUE\n" */
    // retVal  = ProcessMessage("MID:1 CMD:TESTERLOCK LOCK:TRUE\n", replyMsg);
    // printf("After invoking command, reply string: %s\n", replyMsg);

    /*
    Test for these:
     BIN_YIELD_LIMIT:1 95 2 60 ANOTHER_LIST: a b c
    ERROR_MSG:”something is wrong”
    ”ERROR MSG”:”something is wrong”
    “C:\Test/test\program\path/testProgram.ext”
    */

    /* cleanUpCommandRefs(); */
    return 0;
}
