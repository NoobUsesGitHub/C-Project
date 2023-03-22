#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "prototypes.h"

/*
    input: a header node, a name for the new macro and it's list of strings that it unfolds to
    output: the new macro node already connected to the list
*/
Symbol *addMacroToList(Symbol *header, char *macroName, char **Symbol)
{
    char *str = (char *)malloc(strlen(macroName) * (sizeof(char) + 1));
    Symbol *current_node=header;
    strcpy(str, macroName);
    if (header->macroName == NULL)
    {
        header->macro = Symbol;
        header->hash = hasher(str);
        header->macroName = str;
    }
    else
    {
        while (current_node->next != NULL)
        {
            current_node = current_node->next;
        }
        constSymbol(&(current_node->next));
        current_node->next->macro = Symbol;
        current_node->next->hash = hasher(str);
        current_node->next->macroName = str;
        return current_node->next;
    }
    return current_node;
}

/*
 * input: a pointer for null macro node object
 * output: the node
 */
void constSymbol(Symbol **m)
{
    *m = (Symbol *)malloc(sizeof(Symbol));
    (*(m))->macroName = NULL;
    (*(m))->macro = NULL;
    (*(m))->size = 0;
    (*(m))->next = NULL;
}

/*
 * input:a file node header
 * will close all file objects
 */
void freeList(Symbol *head)
{
    Symbol *next = head;
    while (next != NULL)
    {
        free(head->macroName);
        freeMacro(head->macro, head->size);
        next = head->next;
        free(head);
        head = next;
    }
}

/*
 * input:a macro node header
 * will free all nodes
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
 * input: a pointer for a macro node object, a string
 * will take the string and add it to the node' internal node list
 */
void addLineToNode(Symbol *m, char *str)
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
            printf("can't allocate memory.."); /*add to errors?*/
    }

    m->macro[m->size - 1] = (char *)malloc(MAXLINESIZE * sizeof(char));

    strcpy(m->macro[m->size - 1], str);
}
