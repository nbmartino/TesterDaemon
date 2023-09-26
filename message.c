/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, Java, PHP, Ruby, Perl,
C#, OCaml, VB, Swift, Pascal, Fortran, Haskell, Objective-C, Assembly, HTML, CSS, JS, SQLite, Prolog.
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <regex.h>
#include <stdio.h>
#include <string.h>

/*
* Match string against the extended regular expression in
* pattern, treating errors as no match.
*
* return 1 for match, 0 for no match
*/

int
match( char *str, char *pattern)
{
  
      int status;
      regex_t re;
      regmatch_t matches[4];
      printf("%s", pattern);
      if (status = regcomp(&re, pattern,0) != 0) {
          printf("reg compile error! status: %d\n", status);
           //return(0);      /* report error */
      }
      printf("after compile\n");
      int iter = 0;
      do{
          iter++;
          printf("iter: %d\n %s \n", iter, str);
        //status = regexec(&re, str, (size_t) 4, matches, 0);
        status = regexec(&re,"MID:123 CMD:START MODE:DEBUG FOO:bar baz", 0, NULL, 0);
        printf("status: %d", status);
        /* Print key-value pair */ 
        char *key = &str[matches[1].rm_so];
        char *value = &str[matches[1].rm_eo];
        printf("\niter: %d %s=%s\n", iter, key, value);
        for(size_t m = 0; m < 4; m++){
            printf("\nm: %zu s:%lld,e:%lld\n", m, matches[m].rm_so, matches[m].rm_eo);
        }
    
      } while (status == 0);
      
      regfree(&re);
      
      if (status != 0) {

            return(0);      /* report error */
      }
      return 0;
}
int find_key_value(char* line,char *key, char *value)
{
    char tmp_str[64] = {"default"};
    sscanf(line,"\\s+CMD:\\w+",tmp_str);
    printf("tmp_str: %s", tmp_str);
    
    return -1;
}

int tokenize(char *src_str, char **tokens)
{
   const char s[2] = " ";
   char *token;
   int idx = 0;
   /* get the first token */
   token = strtok(src_str, s);
   printf( "token: %s\n", token );
   strcpy(tokens[idx++], token);
   /* walk through other tokens */
   while( token != NULL ) {
      token = strtok(NULL, s);
      strcpy(token, tokens[idx++]);
      printf( "token: %s\n", token );
   }

    return 0;
}

int find_any_key_value(const char *str, char *key, char *value)
{
    char junk[256];
    const char *search = str;
    while (*search != '\0')
    {
        printf("search = %s\n",search);
        int offset;
        if (sscanf(search, " %31[a-zA-Z_0-9]=%63s%n", key, value, &offset) != EOF/*2*/)
        {
            printf("KV %s=%s",key, value);
            //return(search + offset - str);
        }
        int rc;
        if ((rc = sscanf(search, "%255s%n", junk, &offset)) != 1)
            return EOF;
        search += offset;
    }

    return EOF;
}

int main()
{
    char ex_str[] = {"MID:123 CMD:START MODE:DEBUG FOO:bar baz"};
    char key[64] = {0};
    char val[64] = {0};
    char (*tokens) [10] = {0};
    find_any_key_value(ex_str, key, val);
    find_key_value("MID:123 CMD:START MODE:DEBUG FOO:bar baz","","");
    

    // check message format
    // parse message
    // call script associated to command
    int result = match("MID:123 CMD:START MODE:DEBUG FOO:bar baz", "/^MID:\\w+\\s+CMD:\\w+\\s+\\b[A-Z]{2,}\\b:[\\w\\s]+(?:\\s+\\b[A-Z]{2,}\\b:[\\w\\s]+)*\\\\n|$/gm" );
    printf("result == %d", result);
    return 0;
}
