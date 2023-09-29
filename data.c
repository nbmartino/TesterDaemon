#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define CMD_NAME_LEN 32
#define PARAMS_REGEX_LEN 64
int g_cmd_total_num = -1;

struct command
{
    int index;
    int params_count;
    char name[CMD_NAME_LEN];
    char **params_regex;
};

struct command cmd_list[50];

void initialize_cmd_instance(struct command *cmd_in, int index_in, char *name_in, int params_count_in) /*, char **params_regex_in)*/
{
    cmd_in->index = index_in;
    strcpy(cmd_in->name, name_in);
    cmd_in->params_count = params_count_in;
    cmd_in->params_regex = malloc(params_count_in * sizeof(char));

    for (int i = 0; i < params_count_in; i++)
    {
        cmd_in->params_regex[i] = malloc((PARAMS_REGEX_LEN + 1) * sizeof(char));
    }
}

int find_cmd_index(const char *name)
{
    int ctr = 0;
    while (ctr++ < g_cmd_total_num)
    {
        printf("\n command name: %s", cmd_list[ctr].name);
        if (strcmp(cmd_list[ctr].name, name) == 0)
        {
            for (int i = 0; i < cmd_list[ctr].params_count; i++)
            {
                printf("\nparam %d: %s", i, cmd_list[ctr].params_regex[i]);
            }
            return ctr;
        }
        
    }
    return -1;
}

void init_commands()
{

    int params_cnt;
    struct command *cmd_ptr;

    /* TESTERLOCK */

    params_cnt = 1;
    cmd_ptr = &cmd_list[++g_cmd_total_num];
    initialize_cmd_instance(cmd_ptr, g_cmd_total_num, "TESTERLOCK", params_cnt);
    //strcpy(cmd_ptr->params_regex[0], "LOCK");

    /* ACCSLEVEL */
    params_cnt = 0;
    cmd_ptr = &cmd_list[++g_cmd_total_num];
    initialize_cmd_instance(cmd_ptr, g_cmd_total_num, "ACCSLEVEL", params_cnt);

    /* OPER */
    params_cnt = 0;
    cmd_ptr = &cmd_list[++g_cmd_total_num];
    initialize_cmd_instance(cmd_ptr, g_cmd_total_num, "OPER", params_cnt);
    
    /* PRGN */
    params_cnt = 0;
    cmd_ptr = &cmd_list[++g_cmd_total_num];
    initialize_cmd_instance(cmd_ptr, g_cmd_total_num, "PRGN", params_cnt);

    /* LOT */
    params_cnt = 0;
    cmd_ptr = &cmd_list[++g_cmd_total_num];
    initialize_cmd_instance(cmd_ptr, g_cmd_total_num, "LOT", params_cnt);

    /* DEVICE */params_cnt = 0;
    cmd_ptr = &cmd_list[++g_cmd_total_num];
    initialize_cmd_instance(cmd_ptr, g_cmd_total_num, "DEVICE", params_cnt);

    /* TESTMODE */
    params_cnt = 0;
    cmd_ptr = &cmd_list[++g_cmd_total_num];
    initialize_cmd_instance(cmd_ptr, g_cmd_total_num, "TESTMODE", params_cnt);
    
    /* PCSITES */
    params_cnt = 0;
    cmd_ptr = &cmd_list[++g_cmd_total_num];
    initialize_cmd_instance(cmd_ptr, g_cmd_total_num, "PCSITES", params_cnt);
    
    /* PBCARD */
    params_cnt = 0;
    cmd_ptr = &cmd_list[++g_cmd_total_num];
    initialize_cmd_instance(cmd_ptr, g_cmd_total_num, "PBCARD", params_cnt);
    
    /* LDBRD */
    params_cnt = 0;
    cmd_ptr = &cmd_list[++g_cmd_total_num];
    initialize_cmd_instance(cmd_ptr, g_cmd_total_num, "LDBRD", params_cnt);

    /* DLNAME */
    params_cnt = 0;
    cmd_ptr = &cmd_list[++g_cmd_total_num];
    initialize_cmd_instance(cmd_ptr, g_cmd_total_num, "DLNAME", params_cnt);

    /* DLOG */
    params_cnt = 0;
    cmd_ptr = &cmd_list[++g_cmd_total_num];
    initialize_cmd_instance(cmd_ptr, g_cmd_total_num, "DLOG", params_cnt);
    
    /* DLSTART */
    params_cnt = 0;
    cmd_ptr = &cmd_list[++g_cmd_total_num];
    initialize_cmd_instance(cmd_ptr, g_cmd_total_num, "DLSTART", params_cnt);

    /* WFR */
    params_cnt = 0;
    cmd_ptr = &cmd_list[++g_cmd_total_num];
    initialize_cmd_instance(cmd_ptr, g_cmd_total_num, "WFR", params_cnt);

    /* SCRIBE */
    params_cnt = 0;
    cmd_ptr = &cmd_list[++g_cmd_total_num];
    initialize_cmd_instance(cmd_ptr, g_cmd_total_num, "SCRIBE", params_cnt);

    /* SOT */
    params_cnt = 0;
    cmd_ptr = &cmd_list[++g_cmd_total_num];
    initialize_cmd_instance(cmd_ptr, g_cmd_total_num, "SOT", params_cnt);
    
    /* EOW */
    params_cnt = 0;
    cmd_ptr = &cmd_list[++g_cmd_total_num];
    initialize_cmd_instance(cmd_ptr, g_cmd_total_num, "EOW", params_cnt);

    /* DLEND */
    params_cnt = 0;
    cmd_ptr = &cmd_list[++g_cmd_total_num];
    initialize_cmd_instance(cmd_ptr, g_cmd_total_num, "DLEND", params_cnt);

    /* DLGEN */
    params_cnt = 0;
    cmd_ptr = &cmd_list[++g_cmd_total_num];
    initialize_cmd_instance(cmd_ptr, g_cmd_total_num, "DLGEN", params_cnt);

    /* EOL */
    params_cnt = 0;
    cmd_ptr = &cmd_list[++g_cmd_total_num];
    initialize_cmd_instance(cmd_ptr, g_cmd_total_num, "EOL", params_cnt);

}