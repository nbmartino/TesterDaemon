#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "data.h"
#include "logging.h"

int gCmdTotalNum = -1;

struct CommandDescriptor *cmdDescPtr;

void initializeCmdDesc(struct CommandDescriptor *inputCmd, int inputIndex, char *inputName, int inputParamsCount) /*, char **params_regex_in)*/
{
    log_debug("\ninputIndex:%d inputName: %s\n", inputIndex, inputName);
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
        for (int i = 0; i < inputParamsCount; i++)
        {
            inputCmd->paramsRegex[i] = malloc((PARAMS_REGEX_LEN + 1) * sizeof(char));
        }
    }
}

int findCmdIndex(const char *name)
{
    log_debug("\n command name: %s", name);
    for (int ctr = 0; ctr < gCmdTotalNum; ctr++)
    {
        /*  log_debug("\nindex: %d, command name: %s", ctr, cmdDescList[ctr].name); */
        if (strcasecmp(cmdDescList[ctr].name, name) == 0)
        {
            log_debug("\nfound! index: %d, command name: %s", ctr, cmdDescList[ctr].name);
            return ctr;
        }

    }
    log_debug("\nindex not found, command name: %s\n", name);
    return -1;
}

/* int getParamsCnt(const char *cmdName)
{
    log_debug("\ncmdName: %s\n");
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
    for (int idx = 0; idx < gCmdTotalNum; idx++)
    {
        if (cmdDescList[idx].paramsRegex != NULL)
            free(cmdDescList[idx].paramsRegex);
    }
}