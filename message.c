/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, Java, PHP, Ruby, Perl,
C#, OCaml, VB, Swift, Pascal, Fortran, Haskell, Objective-C, Assembly, HTML, CSS, JS, SQLite, Prolog.
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <stdlib.h>
#include <regex.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>


extern int extract_kv_pair(const char *source, const char *regexString, char *ret_str, int matched_segs);
extern void init_commands();
/*
 * Match string against the extended regular expression in
 * pattern, treating errors as no match.
 *
 * return 1 for match, 0 for no match
 */

int match(char *str, char *pattern)
{

    int status;
    regex_t re;
    regmatch_t matches[4];
    printf("%s", pattern);
    if (status = regcomp(&re, pattern, 0) != 0)
    {
        printf("reg compile error! status: %d\n", status);
        // return(0);      /* report error */
    }
    printf("after compile\n");
    int iter = 0;
    do
    {
        iter++;
        printf("iter: %d\n %s \n", iter, str);
        // status = regexec(&re, str, (size_t) 4, matches, 0);
        status = regexec(&re, "MID:123 CMD:START MODE:DEBUG FOO:bar baz", 0, NULL, 0);
        printf("status: %d", status);
        /* Print key-value pair */
        char *key = &str[matches[1].rm_so];
        char *value = &str[matches[1].rm_eo];
        printf("\niter: %d %s=%s\n", iter, key, value);
        for (size_t m = 0; m < 4; m++)
        {
            printf("\nm: %zu s:%lld,e:%lld\n", m, matches[m].rm_so, matches[m].rm_eo);
        }

    } while (status == 0);

    regfree(&re);

    if (status != 0)
    {

        return (0); /* report error */
    }
    return 0;
}
int find_key_value(char *line, char *key, char *value)
{
    char tmp_str[64] = {"default"};
    sscanf(line, "\\s+CMD:\\w+", tmp_str);
    printf("tmp_str: %s", tmp_str);

    return -1;
}

int find_any_key_value(const char *str, char *key, char *value)
{
    char junk[256];
    const char *search = str;
    while (*search != '\0')
    {
        printf("search = %s\n", search);
        int offset;
        if (sscanf(search, " %31[a-zA-Z_0-9]=%63s%n", key, value, &offset) != EOF /*2*/)
        {
            printf("KV %s=%s", key, value);
            // return(search + offset - str);
        }
        int rc;
        if ((rc = sscanf(search, "%255s%n", junk, &offset)) != 1)
            return EOF;
        search += offset;
    }

    return EOF;
}

int tokenize(char *src_str, char **tokens)
{
    const char s[2] = " ";
    char *token;
    int idx = 0;
    /* get the first token */
    token = strtok(src_str, s);
    printf("token: %s\n", token);
    strcpy(tokens[idx++], token);
    // sscanf(token, "%s", tokens[idx]);
    /* walk through other tokens */
    while (token != NULL)
    {
        token = strtok(NULL, s);
        if (token != NULL)
        {
            printf("token: %s\n", token);
            strcpy(tokens[idx++], token);
            // sscanf(token, "%s", tokens[idx]);
        }
    }

    return 0;
}

int find_by_pat(const char *src, char *pat)
{

    int status, offset, start, end;
    regex_t re;
    size_t n_match;
    regmatch_t matches[2];
    char str_match[256] = {0};

    // const char *data ="MID:123 CMD:START MODE:DEBUG FOO:bar baz";

    printf("\n%s\n", pat);
    // find message id
    if (status = regcomp(&re, pat, REG_EXTENDED | REG_ICASE) != 0)
    {
        printf("reg compile error! status: %d\n", status);
    }
    status = regexec(&re, src, sizeof(matches) / sizeof(matches[0]),
                     (regmatch_t *)&matches, 0);

    printf("\nStatus: %d\n", status);

    if (status == 0)
    {
        start = matches[0].rm_so;
        end = matches[0].rm_eo;
        printf("start: %lld end: %lld\n", start, end);
        // Extract it
        char *val = strndup(src + matches[0].rm_so,
                            matches[0].rm_eo - matches[0].rm_so);
        // strncpy(str_match, src + start, end - start);
        printf("str_match: %s\n", val);
    }
    else
    {
        printf("NO MATCH");
    }
    regfree(&re);
}


#define CMD_NAME_LEN2 64

struct Command2
{
    char name[CMD_NAME_LEN2];
    char **params_pat;
    // params_pat[0] = "regex..";
    // params_pat[1] = "regex2.."
};


void crawl_kvs(const char *src)
{
    const char *PAT_MID = "^[A-Z]*:[:digit:]*[[:space:]]*";
    const char *PAT_CMD = "[[:space:]]*CMD:[:upper:]*[?]*";
    const char *PAT_PARAMS = "";
    // find message id
    find_by_pat("MID:123 CMD:START MODE:DEBUG", "^MID:[:digit:]*[[:space:]]*");
    find_by_pat("MID:123 CMD:START? MODE:DEBUG", "[[:space:]]*CMD:[:upper:]*[?]*");
    find_by_pat("MID:123 CMD:START? MODE:DEBUG FOO:BAR", "[[:space:]]*MODE|FOO:[:upper:]*");

    struct Command2 TESTERLOCK;
    strcpy(TESTERLOCK.name, "TESTERLOCK");

    // find_by_pat( "hello42world", "hello([0-9]*)world");

    // find command
    find_by_pat(src, "CMD:\\w+\\s+");
}

void regex_match_test2()
{
    regex_t re;
    regmatch_t matches[10];

    int i = regcomp(&re, "hello([0-9]*)world", REG_EXTENDED);
    assert(i == 0);

    const char *data = "hello42world";
    i = regexec(&re, data,
                sizeof(matches) / sizeof(matches[0]),
                (regmatch_t *)&matches, 0);
    assert(i == 0);

    /* First element [0] is always the entire match */
    assert(matches[0].rm_so == 0);
    assert(matches[0].rm_eo == 12);

    /* Second element [1] is the first matched group (should match the '42') */
    assert(matches[1].rm_so == 5);
    assert(matches[1].rm_eo == 7);

    /* Extract it */
    char *val = strndup(data + matches[1].rm_so,
                        matches[1].rm_eo - matches[1].rm_so);
    assert(strcmp(val, "42") == 0);
    free(val);

    regfree(&re);
}

int extract_key_val(const char *src, const char *pat, char *ret_str, int matched_segs)
{

    int status, offset, start, end;
    regex_t re;
    size_t n_match;
    regmatch_t matches[2];
    char str_match[256] = {0};

    char str_tmp [1024];

    strcpy(str_tmp, src);

    // const char *data ="MID:123 CMD:START MODE:DEBUG FOO:bar baz";

    printf("\nextract_key_val: pat -  %s\n", pat);
    // find message id
    if (status = regcomp(&re, pat, REG_EXTENDED | REG_ICASE) != 0)
    {
        printf("reg compile error! status: %d\n", status);
    }
    
    offset = 0;
    int len_str = strlen(str_tmp);
    bool skip = false;

    while (offset < len_str && !skip)
    {
        printf("src: %s", str_tmp+offset);
        status = regexec(&re, src+offset, sizeof(matches) / sizeof(matches[0]),
                         (regmatch_t *)&matches, 0);

        printf("\nStatus: %d\n", status);

        if (status == 0)
        {
            for(int i = 0; i < matched_segs; i++){
            start = matches[i].rm_so;
            end = matches[i].rm_eo;
            printf("start: %d end: %d\n", start, end);
            // Extract it
            char *val = strndup(str_tmp + matches[i].rm_so,
                                matches[i].rm_eo - matches[i].rm_so);
            strcat(ret_str, val);

            offset = end;
            printf("val: %s\n", val);
            }
        }
        else
        {
            printf("NO MATCH");
            return skip = true;
        }
        regfree(&re);
    }
    return 0;
}

const char *mid_pattern = "^MID:[0-9]*[[:space:]]*";
const char *cmd_pattern = "[[:space:]]*CMD:[A-Z]*[?]*";
const char *params_pattern = "[^\"]+\"|[^\"\\s]+:[[:alpha:]/.]*"; //"[:space:]\"[^\"]+\"|[^\"\\s]+\":\"[^\"]+\"|[^\"\\s]+\"[:space:]";

int ProcessMessage(const char *message)
{
    int retval = 0;
    char str_MID[64] = "";
    char str_CMD[64] = "";
    char str_common[64] = "";

    init_commands();

    /*
    1. extract MID
    */

    //extract_key_val(message, mid_pattern, str_MID, 1);
    extract_kv_pair(message, mid_pattern, str_MID, 1);
    printf("str_MID: %s\n", str_MID);

    /*
    2. extract CMD
    2.1 check if single instance of CMD only, otherwise raise error
    */
    extract_kv_pair(message, cmd_pattern, str_CMD, 1);
    printf("str_CMD: %s\n", str_CMD);
   /*
    3. verify if trailing params are valid accd to CMD params regex
        -> iterate CMD params pat to see if a pattern matches
    4. if valid params, parse key-value pairs
    */
    extract_kv_pair("\"paTH\":/usr/local/pgm.fl nAmE:\"Prog Name\" LOT:GAO12345.1 DEVICE:0HIST001\n", "(\"[^\"\\s\\/\\]*\"|[^\\/\\\"\\s:]+):(\"[^\":]+\"|[A-Za-z0-9\\/.]*)", str_common, 0);
    //extract_kv_pair("\"paTH\":/usr/local/pgm.fl nAmE:\"Prog Name\"", "(\\?(\\?=\".*)(\"[A-Za-z\\s]*\")|([A-Za-z]*)):(\"[^\"]*\"|[A-Za-z0-9\\/.]*)", str_common, 0);
    //extract_kv_pair(" LOT:GAO12345.1 DEVICE:0HIST001", "(\"[^\"\\s\\/\\]*\"|[^\\/\\\"\\s]*):(\"[^\"]*\"|[A-Za-z0-9\\/.]*)", str_common, 0);

    printf("str_common: %s\n", str_common);
   

   //extract_kv_pair(" LOT:GAO12345.1 DEVICE:0HIST001", "(\"[^\"\\s\\/\\]*\"|[^\\/\\\"]*)?:(\"[^\"]*\"|[^\"]*)?", str_common, 0);
   extract_kv_pair("\"paTH\":/usr/local/pgm.fl LOT:GAO12345.1    deviCE:0HIST001", "(\\?(\\?=\".*\")(\"[A-Za-z\\s]*\")|([A-Za-z]*)):(\"[^\"]*\"|[A-Za-z0-9\\/.]*)", str_common, 0);
   //extract_kv_pair(" LOT:GAO12345.1 DEVICE:0HIST001", "(\\?:.*\\?\\b(broadway|acme)\\b)\\?.*", str_common, 0);
   //(?(?=")("[A-Za-z\s]*")|([A-Za-z]*)):(("[A-Za-z\s]*")|([A-Za-z0-9\/.]*))?
   //extract_kv_pair("LOT:GAO12345.1 DEVICE:0HIST001", "((\"[^\"\\s\\/\\]*\")|([^\"\\s\\/\\]*))?:(\"[^\"]*\"|[^\"]*)", str_common, 0);
    printf("str_common: %s\n", str_common);
   
   /* 
   BIN_YIELD_LIMIT:1 95 2 60 ANOTHER_LIST: a b c
   ERROR_MSG:”something is wrong”
   ”ERROR MSG”:”something is wrong”
   “C:\Test/test\program\path/testProgram.ext”
   */
   /*


    5. invoke CMD script, pass key value pairs

    building replay message string
    1. check for " char replace with <quote>, newline with <newline> and missing value = <null>
    */
}
int main()
{
    char pat[] = "/^MID:\\w+\\s+CMD:\\w+\\s+\\b[A-Z]{2,}\\b:[\\w\\s]+(?:\\s+\\b[A-Z]{2,}\\b:[\\w\\s]+)*\\\\n|$/gm";
    char data[] = {"MiD:123 CMD:PrGn paTH:/usr/local/pgm.fl nAmE:\"Prog Name\" \n"};
    char key[64] = {0};
    char val[64] = {0};

    
    ProcessMessage(data);

    // regex_match_test2();
    // crawl_kvs(str);
    /*
    // char (*tokens) [256] = malloc (10* size)
    char **tokens;

    tokens = malloc(10 * sizeof(char *));
    for (int i = 0; i < 10; i++)
        tokens[i] = malloc((256) * sizeof(char));
    // for (int i = 0; i < 10; i++)
    //     tokens[i] = "";
    tokenize(ex_str, tokens);

    for (int i = 0; i < 10; i++)
        printf("%d - %s\n", i, tokens[i]);
    free(tokens);
    find_any_key_value(ex_str, key, val);
    find_key_value("MID:123 CMD:START MODE:DEBUG FOO:bar baz", "", "");

    // check message format
    // parse message
    // call script associated to command
    int result = match("MID:123 CMD:START MODE:DEBUG FOO:bar baz", "/^MID:\\w+\\s+CMD:\\w+\\s+\\b[A-Z]{2,}\\b:[\\w\\s]+(?:\\s+\\b[A-Z]{2,}\\b:[\\w\\s]+)*\\\\n|$/gm");
    printf("result == %d", result);
    */
    return 0;
}
