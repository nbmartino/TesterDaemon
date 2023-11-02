#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "data.h"


int gCmdTotalNum = -1;

struct CommandDescriptor *cmdDescPtr;

void initializeCmdDesc(struct CommandDescriptor *inputCmd, int inputIndex, char *inputName, int inputParamsCount) /*, char **params_regex_in)*/
{
    int i;
    sprintf(logMsg, "\ninputIndex:%d inputName: %s\n", inputIndex, inputName);
    logDebug(logMsg);

    inputCmd->index = inputIndex;
    strcpy(inputCmd->name, inputName);
    inputCmd->paramsCount = inputParamsCount;
    inputCmd->paramsRegex = malloc(inputParamsCount * sizeof(char));
    if (inputParamsCount == 0)
    {
        inputCmd->paramsRegex = NULL;
    }
    else
    {
        for (i = 0; i < inputParamsCount; i++)
        {
            inputCmd->paramsRegex[i] = malloc((PARAMS_REGEX_LEN + 1) * sizeof(char));
        }
    }
}

int findCmdIndex(const char *name)
{
    int ctr;

    sprintf(logMsg, "\n command name: %s", name);
    logDebug(logMsg);
    for (ctr = 0; ctr < gCmdTotalNum; ctr++)
    {
        /*  sprintf(logMsg,"\nindex: %d, command name: %s", ctr, cmdDescList[ctr].name); */
        if (strcasecmp(cmdDescList[ctr].name, name) == 0)
        {
            sprintf(logMsg, "\nfound! index: %d, command name: %s", ctr, cmdDescList[ctr].name);
            logDebug(logMsg);
            return ctr;
        }
    }
    sprintf(logMsg, "\nindex not found, command name: %s\n", name);
    logDebug(logMsg);
    return -1;
}

/* int getParamsCnt(const char *cmdName)
{
    sprintf(logMsg,"\ncmdName: %s\n");
    log_debug(logMsg);
    int idx = findCmdIndex(cmdName);
    if (idx != -1)
    {
        return cmdDescList[idx].paramsCount;
    }
    else
    {
        return idx;
    }
}
 */
void initCommandRefs()
{

    int paramsCount;

    logDebug("initCommandRefs()");

    /* TESTERLOCK */
    paramsCount = 2;
    cmdDescPtr = &cmdDescList[++gCmdTotalNum];
    initializeCmdDesc(cmdDescPtr, gCmdTotalNum, "TESTERLOCK", paramsCount);
    strcpy(cmdDescPtr->paramsRegex[0], "LOCK:FALSE");
    strcpy(cmdDescPtr->paramsRegex[1], "LOCK:TRUE)");

    /* TESTERLOCK? */
    paramsCount = 0;
    cmdDescPtr = &cmdDescList[++gCmdTotalNum];
    initializeCmdDesc(cmdDescPtr, gCmdTotalNum, "TESTERLOCK?", paramsCount);

    /* ACCSLEVEL */
    paramsCount = 1;
    cmdDescPtr = &cmdDescList[++gCmdTotalNum];
    initializeCmdDesc(cmdDescPtr, gCmdTotalNum, "ACCSLEVEL", paramsCount);

    /* ACCSLEVEL? */
    paramsCount = 0;
    cmdDescPtr = &cmdDescList[++gCmdTotalNum];
    initializeCmdDesc(cmdDescPtr, gCmdTotalNum, "ACCSLEVEL?", paramsCount);

    /* OPER */
    paramsCount = 1;
    cmdDescPtr = &cmdDescList[++gCmdTotalNum];
    initializeCmdDesc(cmdDescPtr, gCmdTotalNum, "OPER", paramsCount);

    /* PRGN */
    paramsCount = 2;
    cmdDescPtr = &cmdDescList[++gCmdTotalNum];
    initializeCmdDesc(cmdDescPtr, gCmdTotalNum, "PRGN", paramsCount);

    /* PRGN? */
    paramsCount = 0;
    cmdDescPtr = &cmdDescList[++gCmdTotalNum];
    initializeCmdDesc(cmdDescPtr, gCmdTotalNum, "PRGN?", paramsCount);

    /* LOT */
    paramsCount = 1;
    cmdDescPtr = &cmdDescList[++gCmdTotalNum];
    initializeCmdDesc(cmdDescPtr, gCmdTotalNum, "LOT", paramsCount);

    /* LOT? */
    paramsCount = 0;
    cmdDescPtr = &cmdDescList[++gCmdTotalNum];
    initializeCmdDesc(cmdDescPtr, gCmdTotalNum, "LOT?", paramsCount);

    /* DEVICE */ paramsCount = 1;
    cmdDescPtr = &cmdDescList[++gCmdTotalNum];
    initializeCmdDesc(cmdDescPtr, gCmdTotalNum, "DEVICE", paramsCount);

    /* DEVICE? */ paramsCount = 0;
    cmdDescPtr = &cmdDescList[++gCmdTotalNum];
    initializeCmdDesc(cmdDescPtr, gCmdTotalNum, "DEVICE?", paramsCount);

    /* TESTMODE */
    paramsCount = 1;
    cmdDescPtr = &cmdDescList[++gCmdTotalNum];
    initializeCmdDesc(cmdDescPtr, gCmdTotalNum, "TESTMODE", paramsCount);

    /* TESTMODE */
    paramsCount = 1;
    cmdDescPtr = &cmdDescList[++gCmdTotalNum];
    initializeCmdDesc(cmdDescPtr, gCmdTotalNum, "TESTMODE?", paramsCount);

    /* PCSITES */
    paramsCount = 1;
    cmdDescPtr = &cmdDescList[++gCmdTotalNum];
    initializeCmdDesc(cmdDescPtr, gCmdTotalNum, "PCSITES", paramsCount);

    /* PCSITES */
    paramsCount = 0;
    cmdDescPtr = &cmdDescList[++gCmdTotalNum];
    initializeCmdDesc(cmdDescPtr, gCmdTotalNum, "PCSITES?", paramsCount);

    /* PBCARD */
    paramsCount = 1;
    cmdDescPtr = &cmdDescList[++gCmdTotalNum];
    initializeCmdDesc(cmdDescPtr, gCmdTotalNum, "PBCARD", paramsCount);

    /* PBCARD? */
    paramsCount = 0;
    cmdDescPtr = &cmdDescList[++gCmdTotalNum];
    initializeCmdDesc(cmdDescPtr, gCmdTotalNum, "PBCARD?", paramsCount);

    /* LDBRD */
    paramsCount = 1;
    cmdDescPtr = &cmdDescList[++gCmdTotalNum];
    initializeCmdDesc(cmdDescPtr, gCmdTotalNum, "LDBRD", paramsCount);

    /* LDBRD? */
    paramsCount = 0;
    cmdDescPtr = &cmdDescList[++gCmdTotalNum];
    initializeCmdDesc(cmdDescPtr, gCmdTotalNum, "LDBRD?", paramsCount);

    /* DLNAME */
    paramsCount = 2;
    cmdDescPtr = &cmdDescList[++gCmdTotalNum];
    initializeCmdDesc(cmdDescPtr, gCmdTotalNum, "DLNAME", paramsCount);

    /* DLOGI */
    paramsCount = 1;
    cmdDescPtr = &cmdDescList[++gCmdTotalNum];
    initializeCmdDesc(cmdDescPtr, gCmdTotalNum, "DLOG", paramsCount);

    /* DLOGI? */
    paramsCount = 0;
    cmdDescPtr = &cmdDescList[++gCmdTotalNum];
    initializeCmdDesc(cmdDescPtr, gCmdTotalNum, "DLOG?", paramsCount);

    /* DLSTART */
    paramsCount = 0;
    cmdDescPtr = &cmdDescList[++gCmdTotalNum];
    initializeCmdDesc(cmdDescPtr, gCmdTotalNum, "DLSTART", paramsCount);

    /* WFR */
    paramsCount = 1;
    cmdDescPtr = &cmdDescList[++gCmdTotalNum];
    initializeCmdDesc(cmdDescPtr, gCmdTotalNum, "WFR", paramsCount);

    /* WFR? */
    paramsCount = 0;
    cmdDescPtr = &cmdDescList[++gCmdTotalNum];
    initializeCmdDesc(cmdDescPtr, gCmdTotalNum, "WFR?", paramsCount);

    /* SOT */
    paramsCount = 5;
    cmdDescPtr = &cmdDescList[++gCmdTotalNum];
    initializeCmdDesc(cmdDescPtr, gCmdTotalNum, "SOT", paramsCount);

    /* EOW */
    paramsCount = 0;
    cmdDescPtr = &cmdDescList[++gCmdTotalNum];
    initializeCmdDesc(cmdDescPtr, gCmdTotalNum, "EOW", paramsCount);

    /* DLEND */
    paramsCount = 1;
    cmdDescPtr = &cmdDescList[++gCmdTotalNum];
    initializeCmdDesc(cmdDescPtr, gCmdTotalNum, "DLEND", paramsCount);

    /* DLGEN */
    paramsCount = 1;
    cmdDescPtr = &cmdDescList[++gCmdTotalNum];
    initializeCmdDesc(cmdDescPtr, gCmdTotalNum, "DLGEN", paramsCount);

    /* DLGEN? */
    paramsCount = 0;
    cmdDescPtr = &cmdDescList[++gCmdTotalNum];
    initializeCmdDesc(cmdDescPtr, gCmdTotalNum, "DLGEN?", paramsCount);

    /* EOL */
    paramsCount = 0;
    cmdDescPtr = &cmdDescList[++gCmdTotalNum];
    initializeCmdDesc(cmdDescPtr, gCmdTotalNum, "EOL", paramsCount);

    /* SCRIBE */
    paramsCount = 1;
    cmdDescPtr = &cmdDescList[++gCmdTotalNum];
    initializeCmdDesc(cmdDescPtr, gCmdTotalNum, "SCRIBE", paramsCount);

    /* SCRIBE? */
    paramsCount = 0;
    cmdDescPtr = &cmdDescList[++gCmdTotalNum];
    initializeCmdDesc(cmdDescPtr, gCmdTotalNum, "SCRIBE?", paramsCount);
}

void cleanUpCommandRefs()
{
    int idx;
    for (idx = 0; idx < gCmdTotalNum; idx++)
    {
        if (cmdDescList[idx].paramsRegex != NULL)
            free(cmdDescList[idx].paramsRegex);
    }
}
