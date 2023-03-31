#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "helpers.h"
#include "MacroListFuncs.h"





/*
    input: a header node, a name for the new macro and it's list of strings that it unfolds to
    output: the new macro node already connected to the list
*/
MacroList *addMacroToList(MacroList *header, char *macroName, char **macroList)
{
    char *str = (char *)malloc(strlen(macroName) * (sizeof(char) + 1));
    MacroList *current_node=header;
    strcpy(str, macroName);
    if (header->macroName == NULL)
    {
        header->macro = macroList;
        header->hash = hasher(str);
        header->macroName = str;
    }
    else
    {
        while (current_node->next != NULL)
        {
            current_node = current_node->next;
        }
        constMacroList(&(current_node->next));
        current_node->next->macro = macroList;
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
void constMacroList(MacroList **m)
{
    *m = (MacroList *)malloc(sizeof(MacroList));
    (*(m))->macroName = NULL;
    (*(m))->macro = NULL;
    (*(m))->hash= 0;
    (*(m))->size = 0;
    (*(m))->next = NULL;
}

/*
 * input:a file node header
 * will close all file objects
 */
void freeMacroList(MacroList *head)
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
void addLineToNode(MacroList *m, char *str)
{
    m->size++;
    if (m->size > 1)
    {
        m->macro = (char **)realloc(m->macro, m->size * sizeof(char) * MAX_LINE_SIZE);
    }
    else
    {
        m->macro = (char **)malloc(m->size * sizeof(char) * MAX_LINE_SIZE);
        if (m->macro == NULL)
            fprintf(stdout, "can't allocate memory.."); 
    }

    m->macro[m->size - 1] = (char *)malloc(MAX_LINE_SIZE * sizeof(char));

    strcpy(m->macro[m->size - 1], str);
}


/*
input: a header node of a macro list and a double of a hash
output: 1 if a node with this hash was found, 0 if not
will also print the list of said node
*/
int dumpIfexistsInMacro(MacroList *header, double hash, FILE *fp)
{
    bool found = FALSE;
    while (header != NULL && found == FALSE)
    {
        if (header->hash == hash)
        {
            printList(header->macro, header->size, fp);
            found = TRUE;
        }
        header = header->next;
    }
    return found == TRUE ? 1 : 0;
}
