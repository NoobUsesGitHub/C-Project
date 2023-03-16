/* strtok example */
#include <stdio.h>
#include <string.h>
#include "struct.h"
#define MAXLINESIZE 85

#define coment ';'
#define delimints "    \t \f \r"

/*
 * input: a pointer for a file node object
 * output: the node
 */
void constMacroList(MacroList **m)
{
  *m = (MacroList *)malloc(sizeof(MacroList));
  (*(m))->macroName = NULL;
  (*(m))->macro = NULL;
  (*(m))->size = 0;
  (*(m))->next = NULL;
}

/*
 * input: a pointer for a file node object
 * output: the node
 */
void addLineToNode(MacroList *m, char *str)
{
  m->size++;
  if (m->size > 1)
  {
    realloc(m->macro, m->size * sizeof(char) * MAXLINESIZE);
    if (m->macro == NULL)
      return;
  }else
  {
    m->macro=(char**)malloc( m->size * sizeof(char) * MAXLINESIZE);
  }
  strcpy(m->macro[m->size], str);
}

MacroList *addMacroToList(MacroList *header, char *macroName, char **macroList)
{
  char *str = (char *)malloc(strlen(macroName) * (sizeof(char) + 1));
  strcpy(str, macroName);
  if (header->macroName == NULL)
  {
    header->macro = macroList;
    header->macroName = str;
  }
  else
  {
    MacroList *current_node = header;
    while (current_node->next != NULL)
    {
      current_node = current_node->next;
    }
    constMacroList(&(current_node->next));
    current_node->next->macro = macroList;
    current_node->next->macroName = str;
    return current_node->next;
  }
}

/*
 * input:a file node header
 * will close all file objects
 */
void freeList(MacroList *head)
{
  MacroList *next = head;
  while (next->next != NULL)
  {
    free(head->macroName);
    freeMacro(head->macro);
    next = head->next;
    free(head);
    head = next;
  }
  free(head->macroName);
  freeMacro(head->macro);
  free(head->next);
  free(head);
}

int main()
{
  FILE *f = fopen("test", "r");
  if (f == NULL)
  {
    printf("wtf");
    return 1;
  }
  int i = 0;
  bool skp = FALSE;
  bool macroCollectionStarted = FALSE;
  MacroList *header, *curMacro;
  constMacroList(&header);
  char *pch;
  char bit = ' ';

  char *str[85];
  while (fgets(str, 85, f) != NULL)
  {
    /*skip lines of comments*/
    sscanf(str, "%c", &bit);
    if ((int)bit == ((int)coment))
      skp = TRUE;

    pch = strtok(str, delimints); /*start strtok*/

    if (strcmp(pch, "endmcr") == 0 || strcmp(pch, "endmcr\n") == 0)
    {
      printf("mcr ended\n");
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
        printf("mcr started");
        macroCollectionStarted = TRUE;
        pch = strtok(NULL, delimints);
        curMacro = addMacroToList(header, pch, NULL);
        skp = TRUE;
      }

      if (skp == FALSE)
        printf("%s\n", pch);
      pch = strtok(NULL, delimints);
    }
    skp = FALSE;
  }

  freeList(header);
  return 0;
}
