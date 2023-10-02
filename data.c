#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "data.h"

int gCmdTotalNum = -1;

void initializeCmdRef(struct CommandReference *inputCmd, int inputIndex, char *inputName, int inputParamsCount) /*, char **params_regex_in)*/
{
    printf("\ninitializeCmdRef inputIndex:%d inputName: %s\n", inputIndex, inputName);
    inputCmd->index = inputIndex;
    strcpy(inputCmd->name, inputName);
    inputCmd->paramsCount = inputParamsCount;
    inputCmd->paramsRegex = malloc(inputParamsCount * sizeof(char));

    for (int i = 0; i < inputParamsCount; i++)
    {
        inputCmd->paramsRegex[i] = malloc((PARAMS_REGEX_LEN + 1) * sizeof(char));
    }
}

int findCmdIndex(const char *name)
{

    for (int ctr = 0; ctr < gCmdTotalNum; ctr++)
    {
        printf("\nindex: %d, command name: %s", ctr, cmdRefList[ctr].name);
        if (strcmp(cmdRefList[ctr].name, name) == 0)
        {
            /* for (int i = 0; i < cmdRefList[ctr].paramsCount; i++)
            {
                printf("\nparam %d: %s", i, cmdRefList[ctr].paramsRegex[i]);
            } */
            return ctr;
        }
        
    }
    return -1;
}

void init_commands()
{

    int paramsCount;
    struct CommandReference *cmdPtr;

    /* TESTERLOCK */

    paramsCount = 1;
    cmdPtr = &cmdRefList[++gCmdTotalNum];
    initializeCmdRef(cmdPtr, gCmdTotalNum, "TESTERLOCK", paramsCount);
    //strcpy(cmdPtr->paramsRegex[0], "LOCK:(TRUE|FALSE)");

    /* ACCSLEVEL */
    paramsCount = 0;
    cmdPtr = &cmdRefList[++gCmdTotalNum];
    initializeCmdRef(cmdPtr, gCmdTotalNum, "ACCSLEVEL", paramsCount);

    /* OPER */
    paramsCount = 0;
    cmdPtr = &cmdRefList[++gCmdTotalNum];
    initializeCmdRef(cmdPtr, gCmdTotalNum, "OPER", paramsCount);
    
    /* PRGN */
    paramsCount = 0;
    cmdPtr = &cmdRefList[++gCmdTotalNum];
    initializeCmdRef(cmdPtr, gCmdTotalNum, "PRGN", paramsCount);

    /* LOT */
    paramsCount = 0;
    cmdPtr = &cmdRefList[++gCmdTotalNum];
    initializeCmdRef(cmdPtr, gCmdTotalNum, "LOT", paramsCount);

    /* DEVICE */paramsCount = 0;
    cmdPtr = &cmdRefList[++gCmdTotalNum];
    initializeCmdRef(cmdPtr, gCmdTotalNum, "DEVICE", paramsCount);

    /* TESTMODE */
    paramsCount = 0;
    cmdPtr = &cmdRefList[++gCmdTotalNum];
    initializeCmdRef(cmdPtr, gCmdTotalNum, "TESTMODE", paramsCount);
    
    /* PCSITES */
    paramsCount = 0;
    cmdPtr = &cmdRefList[++gCmdTotalNum];
    initializeCmdRef(cmdPtr, gCmdTotalNum, "PCSITES", paramsCount);
    
    /* PBCARD */
    paramsCount = 0;
    cmdPtr = &cmdRefList[++gCmdTotalNum];
    initializeCmdRef(cmdPtr, gCmdTotalNum, "PBCARD", paramsCount);
    
    /* LDBRD */
    paramsCount = 0;
    cmdPtr = &cmdRefList[++gCmdTotalNum];
    initializeCmdRef(cmdPtr, gCmdTotalNum, "LDBRD", paramsCount);

    /* DLNAME */
    paramsCount = 0;
    cmdPtr = &cmdRefList[++gCmdTotalNum];
    initializeCmdRef(cmdPtr, gCmdTotalNum, "DLNAME", paramsCount);

    /* DLOG */
    paramsCount = 0;
    cmdPtr = &cmdRefList[++gCmdTotalNum];
    initializeCmdRef(cmdPtr, gCmdTotalNum, "DLOG", paramsCount);
    
    /* DLSTART */
    paramsCount = 0;
    cmdPtr = &cmdRefList[++gCmdTotalNum];
    initializeCmdRef(cmdPtr, gCmdTotalNum, "DLSTART", paramsCount);

    /* WFR */
    paramsCount = 0;
    cmdPtr = &cmdRefList[++gCmdTotalNum];
    initializeCmdRef(cmdPtr, gCmdTotalNum, "WFR", paramsCount);

    /* SCRIBE */
    paramsCount = 0;
    cmdPtr = &cmdRefList[++gCmdTotalNum];
    initializeCmdRef(cmdPtr, gCmdTotalNum, "SCRIBE", paramsCount);

    /* SOT */
    paramsCount = 0;
    cmdPtr = &cmdRefList[++gCmdTotalNum];
    initializeCmdRef(cmdPtr, gCmdTotalNum, "SOT", paramsCount);
    
    /* EOW */
    paramsCount = 0;
    cmdPtr = &cmdRefList[++gCmdTotalNum];
    initializeCmdRef(cmdPtr, gCmdTotalNum, "EOW", paramsCount);

    /* DLEND */
    paramsCount = 0;
    cmdPtr = &cmdRefList[++gCmdTotalNum];
    initializeCmdRef(cmdPtr, gCmdTotalNum, "DLEND", paramsCount);

    /* DLGEN */
    paramsCount = 0;
    cmdPtr = &cmdRefList[++gCmdTotalNum];
    initializeCmdRef(cmdPtr, gCmdTotalNum, "DLGEN", paramsCount);

    /* EOL */
    paramsCount = 0;
    cmdPtr = &cmdRefList[++gCmdTotalNum];
    initializeCmdRef(cmdPtr, gCmdTotalNum, "EOL", paramsCount);

}