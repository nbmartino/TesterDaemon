#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define CMD_NAME_LEN 32
#define PARAMS_REGEX_LEN 64
int gCmdTotalNum = -1;

struct command
{
    int index;
    int paramsCount;
    char name[CMD_NAME_LEN];
    char **paramsRegex;
};

struct command cmdList[50];

void initialize_cmd_instance(struct command *inputCmd, int inputIndex, char *inputName, int inputParamsCount) /*, char **params_regex_in)*/
{
    inputCmd->index = inputIndex;
    strcpy(inputCmd->name, inputName);
    inputCmd->paramsCount = inputParamsCount;
    inputCmd->paramsRegex = malloc(inputParamsCount * sizeof(char));

    for (int i = 0; i < inputParamsCount; i++)
    {
        inputCmd->paramsRegex[i] = malloc((PARAMS_REGEX_LEN + 1) * sizeof(char));
    }
}

int find_cmd_index(const char *name)
{
    int ctr = 0;
    while (ctr++ < gCmdTotalNum)
    {
        printf("\n command name: %s", cmdList[ctr].name);
        if (strcmp(cmdList[ctr].name, name) == 0)
        {
            for (int i = 0; i < cmdList[ctr].paramsCount; i++)
            {
                printf("\nparam %d: %s", i, cmdList[ctr].paramsRegex[i]);
            }
            return ctr;
        }
        
    }
    return -1;
}

void init_commands()
{

    int paramsCount;
    struct command *cmdPtr;

    /* TESTERLOCK */

    paramsCount = 1;
    cmdPtr = &cmdList[++gCmdTotalNum];
    initialize_cmd_instance(cmdPtr, gCmdTotalNum, "TESTERLOCK", paramsCount);
    strcpy(cmdPtr->paramsRegex[0], "LOCK:(TRUE|FALSE)");

    /* ACCSLEVEL */
    paramsCount = 0;
    cmdPtr = &cmdList[++gCmdTotalNum];
    initialize_cmd_instance(cmdPtr, gCmdTotalNum, "ACCSLEVEL", paramsCount);

    /* OPER */
    paramsCount = 0;
    cmdPtr = &cmdList[++gCmdTotalNum];
    initialize_cmd_instance(cmdPtr, gCmdTotalNum, "OPER", paramsCount);
    
    /* PRGN */
    paramsCount = 0;
    cmdPtr = &cmdList[++gCmdTotalNum];
    initialize_cmd_instance(cmdPtr, gCmdTotalNum, "PRGN", paramsCount);

    /* LOT */
    paramsCount = 0;
    cmdPtr = &cmdList[++gCmdTotalNum];
    initialize_cmd_instance(cmdPtr, gCmdTotalNum, "LOT", paramsCount);

    /* DEVICE */paramsCount = 0;
    cmdPtr = &cmdList[++gCmdTotalNum];
    initialize_cmd_instance(cmdPtr, gCmdTotalNum, "DEVICE", paramsCount);

    /* TESTMODE */
    paramsCount = 0;
    cmdPtr = &cmdList[++gCmdTotalNum];
    initialize_cmd_instance(cmdPtr, gCmdTotalNum, "TESTMODE", paramsCount);
    
    /* PCSITES */
    paramsCount = 0;
    cmdPtr = &cmdList[++gCmdTotalNum];
    initialize_cmd_instance(cmdPtr, gCmdTotalNum, "PCSITES", paramsCount);
    
    /* PBCARD */
    paramsCount = 0;
    cmdPtr = &cmdList[++gCmdTotalNum];
    initialize_cmd_instance(cmdPtr, gCmdTotalNum, "PBCARD", paramsCount);
    
    /* LDBRD */
    paramsCount = 0;
    cmdPtr = &cmdList[++gCmdTotalNum];
    initialize_cmd_instance(cmdPtr, gCmdTotalNum, "LDBRD", paramsCount);

    /* DLNAME */
    paramsCount = 0;
    cmdPtr = &cmdList[++gCmdTotalNum];
    initialize_cmd_instance(cmdPtr, gCmdTotalNum, "DLNAME", paramsCount);

    /* DLOG */
    paramsCount = 0;
    cmdPtr = &cmdList[++gCmdTotalNum];
    initialize_cmd_instance(cmdPtr, gCmdTotalNum, "DLOG", paramsCount);
    
    /* DLSTART */
    paramsCount = 0;
    cmdPtr = &cmdList[++gCmdTotalNum];
    initialize_cmd_instance(cmdPtr, gCmdTotalNum, "DLSTART", paramsCount);

    /* WFR */
    paramsCount = 0;
    cmdPtr = &cmdList[++gCmdTotalNum];
    initialize_cmd_instance(cmdPtr, gCmdTotalNum, "WFR", paramsCount);

    /* SCRIBE */
    paramsCount = 0;
    cmdPtr = &cmdList[++gCmdTotalNum];
    initialize_cmd_instance(cmdPtr, gCmdTotalNum, "SCRIBE", paramsCount);

    /* SOT */
    paramsCount = 0;
    cmdPtr = &cmdList[++gCmdTotalNum];
    initialize_cmd_instance(cmdPtr, gCmdTotalNum, "SOT", paramsCount);
    
    /* EOW */
    paramsCount = 0;
    cmdPtr = &cmdList[++gCmdTotalNum];
    initialize_cmd_instance(cmdPtr, gCmdTotalNum, "EOW", paramsCount);

    /* DLEND */
    paramsCount = 0;
    cmdPtr = &cmdList[++gCmdTotalNum];
    initialize_cmd_instance(cmdPtr, gCmdTotalNum, "DLEND", paramsCount);

    /* DLGEN */
    paramsCount = 0;
    cmdPtr = &cmdList[++gCmdTotalNum];
    initialize_cmd_instance(cmdPtr, gCmdTotalNum, "DLGEN", paramsCount);

    /* EOL */
    paramsCount = 0;
    cmdPtr = &cmdList[++gCmdTotalNum];
    initialize_cmd_instance(cmdPtr, gCmdTotalNum, "EOL", paramsCount);

}