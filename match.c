
#include "match.h"


int extract_kv_pair(const char *source, const char *regexString, char *ret_str, int match_num, int group_num)
{

  size_t maxMatches = 5;
  size_t maxGroups = 5;
  
  regex_t regexCompiled;
  regmatch_t groupArray[maxGroups];
  unsigned int m;
  char * cursor;

  debug_log("\nsource: %s\n", source);

  if (regcomp(&regexCompiled, regexString, REG_EXTENDED | REG_ICASE))
    {
      debug_log("Could not compile regular expression.\n");
      return 1;
    };

  m = 0;
  cursor = source;
  for (m = 0; m < maxMatches; m ++)
    {
      if (regexec(&regexCompiled, cursor, maxGroups, groupArray, 0))
        break;  // No more matches

      unsigned int g = 0;
      unsigned int offset = 0;
      for (g = 0; g < maxGroups; g++)
        {
          if (groupArray[g].rm_so == (size_t)-1)
            break;  // No more groups

          if (g == 0)
            offset = groupArray[g].rm_eo;

          char cursorCopy[strlen(cursor) + 1];
          strcpy(cursorCopy, cursor);
            
          cursorCopy[groupArray[g].rm_eo] = 0;
          debug_log("Match %u, Group %u: [%2u-%2u]: %s\n",
                 m, g, groupArray[g].rm_so, groupArray[g].rm_eo,
                 cursorCopy + groupArray[g].rm_so);
          /* copy KV token */
          if ((m == match_num) && (g == group_num))
            {
             strcpy (ret_str,cursorCopy + groupArray[g].rm_so);
            }  
            
        }
      cursor += offset;
      debug_log("cursor: %lld, offset %lld", cursor, offset);
    }

  regfree(&regexCompiled);
  
  return cursor - source;
}