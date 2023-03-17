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
    m->macro = (char **)realloc(m->macro, m->size * sizeof(char) * MAXLINESIZE);
  }
  else
  {
    m->macro = (char **)malloc(m->size * sizeof(char) * MAXLINESIZE);
    if (m->macro == NULL)
      printf("can't allocate memory..");
  }

  m->macro[m->size - 1] = (char *)malloc(MAXLINESIZE * sizeof(char));

  strcpy(m->macro[m->size - 1], str);
}

double hasher(char *str)
{
  int size = sizeof(str) / sizeof(char);
  double hash = 0;
  int i = 0;
  /*maybe change to while*/
  for (; str[i] != '\0'; i++)
  {
    hash += ((int)(str[i])) / (size - i) * 7; /*hashing func*/
  }
  return hash;
}

MacroList *addMacroToList(MacroList *header, char *macroName, char **macroList)
{
  char *str = (char *)malloc(strlen(macroName) * (sizeof(char) + 1));
  strcpy(str, macroName);
  if (header->macroName == NULL)
  {
    header->macro = macroList;
    header->hash = hasher(str);
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
void freeMacro(char **head, int size)
{
  int i = 0;
  for (; i < size; i++)
  {
    free(head[i]);
  }
  free(head);
}

/*
 * input:a file node header
 * will close all file objects
 */
void freeList(MacroList *head)
{
  MacroList *next = head;
  while (next != NULL)
  {
    free(head->macroName);
    freeMacro(head->macro, head->size);
    next = head->next;
    free(head);
    head = next;
  }
}

double *addToHashTable(double *hash, char *str, int *size)
{
  hash = (double *)realloc(hash, (*size + 1) * sizeof(double));
  *size += 1;
  hash[*size - 1] = hasher(str); /*no idea why the fuck this shit is failing on me*/
  return hash;
}

int main()
{
  double *hash = NULL;
  int hashSize = 1;
  FILE *f = fopen("test", "r");
  if (f == NULL)
  {
    printf("wtf");
    return 1;
  }
  hash = (double *)malloc(sizeof(double) * hashSize);
  int i = 0;
  bool skp = FALSE;
  bool macroCollectionStarted = FALSE;
  MacroList *header, *curMacro;
  constMacroList(&header);
  char *pch = NULL;
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
        hash = addToHashTable(hash, pch, &hashSize);
        skp = TRUE;
      }

      if (skp == FALSE)
        printf("%s\n", pch);
      pch = strtok(NULL, delimints);
    }
    skp = FALSE;
  }

  freeList(header);
  free(hash);

  while (hashSize != 0)
  {
    printf("%f\n", hash[hashSize - 1]);
    hashSize--;
  }
  printf("done");
  return 0;
}
