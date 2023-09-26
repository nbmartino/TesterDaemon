/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, Java, PHP, Ruby, Perl,
C#, OCaml, VB, Swift, Pascal, Fortran, Haskell, Objective-C, Assembly, HTML, CSS, JS, SQLite, Prolog.
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <regex.h>
#include <stdio.h>
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
      if (status = regcomp(&re, pattern,0) != 0) {
          printf("reg compile error! status: %d\n", status);
           //return(0);      /* report error */
      }
      printf("after compile\n");
      int iter = 0;
      do{
          iter++;
        status = regexec(&re, str, (size_t) 4, matches, 0);
        /* Print key-value pair */ 
        char *key = &str[matches[1].rm_so];
        char *value = &str[matches[1].rm_eo];
        printf("\niter: %d %s=%s\n", iter, key, value);
        for(size_t m = 0; m < 4; m++){
            printf("\nm: %zu s:%lld,e:%lld\n", m, matches[m].rm_so, matches[m].rm_eo);
        }
    
      } while (status == 0);
      
      regfree(&re);
      printf("status: %d", status);
      if (status != 0) {

            return(0);      /* report error */
      }
      return 0;
}

int main()
{
printf("main\n");

// check message format
// parse message
// call script associated to command
 int result = match("MID:123 CMD:START MODE:DEBUG FOO:bar baz", "/^MID:\\w+\\s+CMD:\\w+\\s+\\b[A-Z]{2,}\\b:[\\w\\s]+(?:\\s+\\b[A-Z]{2,}\\b:[\\w\\s]+)*\\\\n|$/gm" );
 printf("result == %d", result);
  return 0;
}
