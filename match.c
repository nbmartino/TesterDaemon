
#include "match.h"

int extract_kv_pair(char *source, const char *regexString, char *ret_str, int match_num, int group_num, char *multiBuf, int *hitCount)
{

  size_t maxMatches = 5;
  size_t maxGroups = 5;

  regex_t regexCompiled;
  regmatch_t groupArray[5];

  unsigned int m;
  char *cursor;

  char cursorCopy[MSG_TOKEN_LEN];

  unsigned int g;
  unsigned int offset;

  maxMatches = maxGroups = 5;

  *hitCount = 0;

  sprintf(logMsg, "\nsource: %s\n", source);
  logDebug(logMsg);

  /* init multibuf */
  if (multiBuf)
    strcpy(multiBuf, "");

  /* init ret_str */
  if (ret_str)
    strcpy(ret_str, "");

  if (regcomp(&regexCompiled, regexString, REG_EXTENDED | REG_ICASE))
  {
    sprintf(logMsg, "Could not compile regular expression.\n");
    logDebug(logMsg);
    return -1;
  };

  m = 0;
  cursor = source;
  for (m = 0; m < maxMatches; m++)
  {
    if (regexec(&regexCompiled, cursor, maxGroups, groupArray, 0))
      break; /*  No more matches */

    ++*hitCount;

    g = offset = 0;

    for (g = 0; g < maxGroups; g++)
    {
      if (groupArray[g].rm_so == (size_t)-1)
        break; /* No more groups */

      if (g == 0)
        offset = groupArray[g].rm_eo;

      strcpy(cursorCopy, cursor);
      sprintf(logMsg, "\ncursorCopy: %s\n", cursorCopy);
      logDebug(logMsg);
      cursorCopy[groupArray[g].rm_eo] = 0;
      sprintf(logMsg, "Match %u, Group %u: [%lld-%lld]: %s\n",
              m, g, groupArray[g].rm_so, groupArray[g].rm_eo,
              cursorCopy + groupArray[g].rm_so);
      logDebug(logMsg);
      /* copy KV token */
      if ((m == match_num) && (g == group_num))
      {
        strcpy(ret_str, cursorCopy);
      }

      /* if multiple param, accumulate params and pad with separator */
      if ((multiBuf != NULL) && (g == 0))
      {
        if (m > 0)
        {
          strcat(multiBuf, PARAM_SEPARATOR);
        }
        /* consider using strdup?? */
        strcat(multiBuf, cursorCopy);
      }
    }
    cursor += offset;
    sprintf(logMsg, "cursor: %d, offset %u", (int) cursor - offset, offset);
    logDebug(logMsg);
  }

  regfree(&regexCompiled);

  return cursor - source;
}
