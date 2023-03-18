/* strtok example */
#include <stdio.h>
#include <string.h>

#define MAXLINESIZE 85




int main()
{

  while (fgets(str, 85, f) != NULL)
  {
    /*skip lines of comments*/
    sscanf(str, "%c", &bit);
    if ((int)bit == ((int)coment))
      skp = TRUE;

    pch = strtok(str, delimints); /*start strtok*/

    if (strcmp(pch, "endmcr") == 0 || strcmp(pch, "endmcr\n") == 0)
    {
      skp = TRUE;
      macroCollectionStarted = FALSE;
    }

    if (macroCollectionStarted == TRUE)
    {
      addLineToNode(curMacro, str);
      skp = TRUE;
    }

    while ((pch != NULL) && (skp != TRUE) && (macroCollectionStarted == FALSE))
    {
      /*checking for mactros*/
      if (strcmp(pch, "mcr") == 0)
      {
        macroCollectionStarted = TRUE;
        pch = strtok(NULL, delimints);
        curMacro = addMacroToList(header, pch, NULL);
        skp = TRUE;
      }

      if (skp == FALSE)
      {
        if (dumpIfexistsInMacro(header, hasher(pch)) == 0)
        {
          printf("%s ", pch);
        }
      }

      pch = strtok(NULL, delimints);
    }
    skp = FALSE;
  }

  freeList(header);
  return 0;
}
