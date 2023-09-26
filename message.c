#include <regex.h>
/*
* Match string against the extended regular expression in
* pattern, treating errors as no match.
*
* return 1 for match, 0 for no match
*/

int
match(const char *string, char *pattern)
{
  
      int status;
      regex_t re;
      regmatch_t matches[2];
      if (regcomp(&re, pattern, REG_EXTENDED /*| REG_NOSUB*/) != 0) {
           return(0);      /* report error */
      }
      do{
        status = regexec(&re, string, (size_t) 2, matches, 0);
        /* Print key-value pair */ 
        char *key = &string[matches[1].rm_so];
        char *value = &string[matches[1].rm_eo];
        printf("%.*s=%.*s\n", key, value);
      } while (status == 0)
      
      regfree(&re);
      if (status != 0) {
            return(0);      /* report error */
      }
      return(1);
}

int main()
{
 int result = match("MID:123 CMD:START MODE:DEBUG FOO:bar baz", "^MID:\\w+\\s+CMD:\\w+\\s+\\b[A-Z]{2,}\\b:[\\w\\s]+(?:\\s+\\b[A-Z]{2,}\\b:[\\w\\s]+)*\\n|$" );
 printf("result == %d", result);
  return 0;
}
