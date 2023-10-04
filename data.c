#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "data.h"
#include "logging.h"

int gCmdTotalNum = -1;

struct CommandDescriptor *cmdDescPtr;

void initializeCmdDesc(struct CommandDescriptor *inputCmd, int inputIndex, char *inputName, int inputParamsCount) /*, char **params_regex_in)*/
{
    debug_log("\ninputIndex:%d inputName: %s\n", inputIndex, inputName);
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
    // debug_log("\n command name: %s", name);
    for (int ctr = 0; ctr < gCmdTotalNum; ctr++)
    {
        debug_log("\nindex: %d, command name: %s", ctr, cmdDescList[ctr].name);
        if (strcasecmp(cmdDescList[ctr].name, name) == 0)
        {
            return ctr;
        }
    }
    return -1;
}

int getParamsCnt(const char *cmdName)
{
    debug_log("\ncmdName: %s\n");
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

void initCommandRefs()
{

    int paramsCount;

    /* TESTERLOCK */
    paramsCount = 2;
    cmdDescPtr = &cmdDescList[++gCmdTotalNum];
    initializeCmdDesc(cmdDescPtr, gCmdTotalNum, "TESTERLOCK", paramsCount);
    strcpy(cmdDescPtr->paramsRegex[0], "LOCK:FALSE");
    strcpy(cmdDescPtr->paramsRegex[1], "LOCK:TRUE)");

    /* ACCSLEVEL */
    paramsCount = 0;
    cmdDescPtr = &cmdDescList[++gCmdTotalNum];
    initializeCmdDesc(cmdDescPtr, gCmdTotalNum, "ACCSLEVEL", paramsCount);

    /* OPER */
    paramsCount = 0;
    cmdDescPtr = &cmdDescList[++gCmdTotalNum];
    initializeCmdDesc(cmdDescPtr, gCmdTotalNum, "OPER", paramsCount);

    /* PRGN */
    paramsCount = 0;
    cmdDescPtr = &cmdDescList[++gCmdTotalNum];
    initializeCmdDesc(cmdDescPtr, gCmdTotalNum, "PRGN", paramsCount);

    /* LOT */
    paramsCount = 0;
    cmdDescPtr = &cmdDescList[++gCmdTotalNum];
    initializeCmdDesc(cmdDescPtr, gCmdTotalNum, "LOT", paramsCount);

    /* DEVICE */ paramsCount = 0;
    cmdDescPtr = &cmdDescList[++gCmdTotalNum];
    initializeCmdDesc(cmdDescPtr, gCmdTotalNum, "DEVICE", paramsCount);

    /* TESTMODE */
    paramsCount = 0;
    cmdDescPtr = &cmdDescList[++gCmdTotalNum];
    initializeCmdDesc(cmdDescPtr, gCmdTotalNum, "TESTMODE", paramsCount);

    /* PCSITES */
    paramsCount = 0;
    cmdDescPtr = &cmdDescList[++gCmdTotalNum];
    initializeCmdDesc(cmdDescPtr, gCmdTotalNum, "PCSITES", paramsCount);

    /* PBCARD */
    paramsCount = 0;
    cmdDescPtr = &cmdDescList[++gCmdTotalNum];
    initializeCmdDesc(cmdDescPtr, gCmdTotalNum, "PBCARD", paramsCount);

    /* LDBRD */
    paramsCount = 0;
    cmdDescPtr = &cmdDescList[++gCmdTotalNum];
    initializeCmdDesc(cmdDescPtr, gCmdTotalNum, "LDBRD", paramsCount);

    /* DLNAME */
    paramsCount = 0;
    cmdDescPtr = &cmdDescList[++gCmdTotalNum];
    initializeCmdDesc(cmdDescPtr, gCmdTotalNum, "DLNAME", paramsCount);

    /* DLOG */
    paramsCount = 0;
    cmdDescPtr = &cmdDescList[++gCmdTotalNum];
    initializeCmdDesc(cmdDescPtr, gCmdTotalNum, "DLOG", paramsCount);

    /* DLSTART */
    paramsCount = 0;
    cmdDescPtr = &cmdDescList[++gCmdTotalNum];
    initializeCmdDesc(cmdDescPtr, gCmdTotalNum, "DLSTART", paramsCount);

    /* WFR */
    paramsCount = 0;
    cmdDescPtr = &cmdDescList[++gCmdTotalNum];
    initializeCmdDesc(cmdDescPtr, gCmdTotalNum, "WFR", paramsCount);

    /* SCRIBE */
    paramsCount = 0;
    cmdDescPtr = &cmdDescList[++gCmdTotalNum];
    initializeCmdDesc(cmdDescPtr, gCmdTotalNum, "SCRIBE", paramsCount);

    /* SOT */
    paramsCount = 0;
    cmdDescPtr = &cmdDescList[++gCmdTotalNum];
    initializeCmdDesc(cmdDescPtr, gCmdTotalNum, "SOT", paramsCount);

    /* EOW */
    paramsCount = 0;
    cmdDescPtr = &cmdDescList[++gCmdTotalNum];
    initializeCmdDesc(cmdDescPtr, gCmdTotalNum, "EOW", paramsCount);

    /* DLEND */
    paramsCount = 0;
    cmdDescPtr = &cmdDescList[++gCmdTotalNum];
    initializeCmdDesc(cmdDescPtr, gCmdTotalNum, "DLEND", paramsCount);

    /* DLGEN */
    paramsCount = 0;
    cmdDescPtr = &cmdDescList[++gCmdTotalNum];
    initializeCmdDesc(cmdDescPtr, gCmdTotalNum, "DLGEN", paramsCount);

    /* EOL */
    paramsCount = 0;
    cmdDescPtr = &cmdDescList[++gCmdTotalNum];
    initializeCmdDesc(cmdDescPtr, gCmdTotalNum, "EOL", paramsCount);
}

void cleanUpCommandRefs()
{
    for (int idx = 0; idx < gCmdTotalNum; idx++)
    {
        if (cmdDescList[idx].paramsRegex != NULL)
            free(cmdDescList[idx].paramsRegex)            
    }
}