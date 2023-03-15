/* strtok example */
#include <stdio.h>
#include <string.h>
#include "struct.h"

#define coment ';'
#define delimints "    \t \f \r"

int main()
{
  FILE *f = fopen("test", "r");
  if (f == NULL)
  {
    printf("wtf");
    return 1;
  }
  int i = 0;
  int skp = 0;
  char *pch;
  char bit = ' ';

  char *str[85];
  while (fgets(str, 85, f) != NULL)
  {
    sscanf(str, "%c", &bit);
    if ((int)bit == ((int)coment))
      skp = 1;

    pch = strtok(str, delimints); /*start strtok*/
    while ((pch != NULL) && (skp != 1))
    {
      if (strcmp(pch, "mcr") == 0)
      {
        printf("mcr started");

        skp = 1;
      }
      if (strcmp(pch, "endmcr") == 0 || strcmp(pch, "endmcr\n") == 0)
      {
        printf("mcr ended\n");
        skp = 1;
      }
      if (skp == 0)
        printf("%s\n", pch);

      pch = strtok(NULL, delimints);
    }

    skp = 0;
  }
  return 0;
}

/*
 * input: a pointer for a file node object
 * output: the node
 */
void constMacroNode(MacroNode **m)
{
  *m = (MacroNode *)malloc(sizeof(MacroNode));
  (*(m))->MacroName = NULL;
  (*(m))->macro = NULL;
  (*(m))->next = NULL;
}

void addToList(MacroNode *header, char *macroName, char **macroList)
{
  char *str = (char *)malloc(strlen(macroName) * (sizeof(char) + 1));
  strcpy(str, macroName);
  if (header->MacroName == NULL)
  {
    header->macro = macroList;
    header->MacroName = str;
  }
  else
  {
    MacroNode *current_node = header;
    while (current_node->next != NULL)
    {
      current_node = current_node->next;
    }
    constMacroNode(&(current_node->next));
    current_node->next->macro = macroList;
    current_node->next->macroName = str;
  }
}