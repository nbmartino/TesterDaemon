 
#include <assert.h>
#include <stdio.h>
#include "data.h"



 extern void initCommandRefs();
 extern void cleanUpCommandRefs();
 extern int ProcessMessage(const char *message);
 extern struct CommandObject *CmdObjPtr;

int main(int argc, char *argv[])
{
    char pat[] = "/^MID:\\w+\\s+CMD:\\w+\\s+\\b[A-Z]{2,}\\b:[\\w\\s]+(?:\\s+\\b[A-Z]{2,}\\b:[\\w\\s]+)*\\\\n|$/gm";
    char data[] = {"MiD:123 CMD:PrGn paTH:/usr/local/pgm.fl nAmE:\"Prog Name\" \n"};
    char key[64] = {0};
    char val[64] = {0};
    int ret_val;


    initCommandRefs();

    /* Tests */

    /* 1. "MID:1 CMD:TESTERLOCK LOCK:TRUE\n"  */
    const char testerLock[] = "MID:1 CMD:TESTERLOCK LOCK:TRUE\n";    
    ret_val  = ProcessMessage(testerLock);
    printf("After invoking command, reply string: %s\n", CmdObjPtr->strReplyMsg);
    

    /*
    Test for these:
     BIN_YIELD_LIMIT:1 95 2 60 ANOTHER_LIST: a b c
    ERROR_MSG:”something is wrong”
    ”ERROR MSG”:”something is wrong”
    “C:\Test/test\program\path/testProgram.ext”
    */

   cleanUpCommandRefs();
    return 0;
}
