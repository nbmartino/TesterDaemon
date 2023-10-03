#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "data.h"

int gCmdTotalNum = -1;
struct CommandReference *cmdRefsPtr;


void initializeCmdRef(struct CommandReference *inputCmd, int inputIndex, char *inputName, int inputParamsCount) /*, char **params_regex_in)*/
{
    // printf("\ninitializeCmdRef inputIndex:%d inputName: %s\n", inputIndex, inputName);
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
        if (strcasecmp(cmdRefList[ctr].name, name) == 0)
        {
            return ctr;
        }
    }
    return -1;
}

void initCommandRefs()
{

    int paramsCount;
    
    /* TESTERLOCK */

    paramsCount = 1;
    cmdRefsPtr = &cmdRefList[++gCmdTotalNum];
    initializeCmdRef(cmdRefsPtr, gCmdTotalNum, "TESTERLOCK", paramsCount);
    strcpy(cmdRefsPtr->paramsRegex[0], "LOCK:(TRUE|FALSE)");

    /* ACCSLEVEL */
    paramsCount = 0;
    cmdRefsPtr = &cmdRefList[++gCmdTotalNum];
    initializeCmdRef(cmdRefsPtr, gCmdTotalNum, "ACCSLEVEL", paramsCount);

    /* OPER */
    paramsCount = 0;
    cmdRefsPtr = &cmdRefList[++gCmdTotalNum];
    initializeCmdRef(cmdRefsPtr, gCmdTotalNum, "OPER", paramsCount);

    /* PRGN */
    paramsCount = 0;
    cmdRefsPtr = &cmdRefList[++gCmdTotalNum];
    initializeCmdRef(cmdRefsPtr, gCmdTotalNum, "PRGN", paramsCount);

    /* LOT */
    paramsCount = 0;
    cmdRefsPtr = &cmdRefList[++gCmdTotalNum];
    initializeCmdRef(cmdRefsPtr, gCmdTotalNum, "LOT", paramsCount);

    /* DEVICE */ paramsCount = 0;
    cmdRefsPtr = &cmdRefList[++gCmdTotalNum];
    initializeCmdRef(cmdRefsPtr, gCmdTotalNum, "DEVICE", paramsCount);

    /* TESTMODE */
    paramsCount = 0;
    cmdRefsPtr = &cmdRefList[++gCmdTotalNum];
    initializeCmdRef(cmdRefsPtr, gCmdTotalNum, "TESTMODE", paramsCount);

    /* PCSITES */
    paramsCount = 0;
    cmdRefsPtr = &cmdRefList[++gCmdTotalNum];
    initializeCmdRef(cmdRefsPtr, gCmdTotalNum, "PCSITES", paramsCount);

    /* PBCARD */
    paramsCount = 0;
    cmdRefsPtr = &cmdRefList[++gCmdTotalNum];
    initializeCmdRef(cmdRefsPtr, gCmdTotalNum, "PBCARD", paramsCount);

    /* LDBRD */
    paramsCount = 0;
    cmdRefsPtr = &cmdRefList[++gCmdTotalNum];
    initializeCmdRef(cmdRefsPtr, gCmdTotalNum, "LDBRD", paramsCount);

    /* DLNAME */
    paramsCount = 0;
    cmdRefsPtr = &cmdRefList[++gCmdTotalNum];
    initializeCmdRef(cmdRefsPtr, gCmdTotalNum, "DLNAME", paramsCount);

    /* DLOG */
    paramsCount = 0;
    cmdRefsPtr = &cmdRefList[++gCmdTotalNum];
    initializeCmdRef(cmdRefsPtr, gCmdTotalNum, "DLOG", paramsCount);

    /* DLSTART */
    paramsCount = 0;
    cmdRefsPtr = &cmdRefList[++gCmdTotalNum];
    initializeCmdRef(cmdRefsPtr, gCmdTotalNum, "DLSTART", paramsCount);

    /* WFR */
    paramsCount = 0;
    cmdRefsPtr = &cmdRefList[++gCmdTotalNum];
    initializeCmdRef(cmdRefsPtr, gCmdTotalNum, "WFR", paramsCount);

    /* SCRIBE */
    paramsCount = 0;
    cmdRefsPtr = &cmdRefList[++gCmdTotalNum];
    initializeCmdRef(cmdRefsPtr, gCmdTotalNum, "SCRIBE", paramsCount);

    /* SOT */
    paramsCount = 0;
    cmdRefsPtr = &cmdRefList[++gCmdTotalNum];
    initializeCmdRef(cmdRefsPtr, gCmdTotalNum, "SOT", paramsCount);

    /* EOW */
    paramsCount = 0;
    cmdRefsPtr = &cmdRefList[++gCmdTotalNum];
    initializeCmdRef(cmdRefsPtr, gCmdTotalNum, "EOW", paramsCount);

    /* DLEND */
    paramsCount = 0;
    cmdRefsPtr = &cmdRefList[++gCmdTotalNum];
    initializeCmdRef(cmdRefsPtr, gCmdTotalNum, "DLEND", paramsCount);

    /* DLGEN */
    paramsCount = 0;
    cmdRefsPtr = &cmdRefList[++gCmdTotalNum];
    initializeCmdRef(cmdRefsPtr, gCmdTotalNum, "DLGEN", paramsCount);

    /* EOL */
    paramsCount = 0;
    cmdRefsPtr = &cmdRefList[++gCmdTotalNum];
    initializeCmdRef(cmdRefsPtr, gCmdTotalNum, "EOL", paramsCount);
}