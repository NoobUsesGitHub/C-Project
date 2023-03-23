#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "prototypes.h"

/*
 * input: a pointer for null macro node object
 * output: the node
 */
void constSymbol(Symbol **s)
{
    *s = (Symbol *)malloc(sizeof(Symbol));
    (*(s))->name = NULL;
    (*(s))->hash = 0.0;
    (*(s))->type = CODE;
    (*(s))->line = 0;
    (*(s))->next = NULL;
}

/*
    input: a header node, a nase for the new macro and it's list of strings that it unfolds to
    output: the new macro node already connected to the list
*/
Symbol *addSymbolToList(Symbol *header, char *name, Stype type, int line)
{ /*do i need to return here?*/
    char *str = (char *)malloc(strlen(name) * (sizeof(char) + 1));
    Symbol *current_node = header;
    bool existsAlready = FALSE;
    strcpy(str, name);
    if (header->name == NULL)
    {
        header->name = str;
        header->hash = hasher(str);
        header->type = type;
        header->line = type;
    }
    else
    {
        while (current_node->next != NULL && existsAlready == FALSE)
        {
            if (type != EXTERN && strcmp(current_node->name, name))
                existsAlready = TRUE;
            current_node = current_node->next;
        }
        if (existsAlready == FALSE)
        {
            constSymbol(&(current_node->next));
            current_node->next->name = str;
            current_node->next->hash = hasher(str);
            current_node->next->type = type;
            current_node->next->line = type;
        }
        else
        {
            current_node->name = NULL;
            printf("%s exists already!!", name);
            return current_node->next;
        }
    }
    return current_node;
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
        free(head->name);
        next = head->next;
        free(head);
        head = next;
    }
}

/*
    input: a string to check which type it is
    output: it's type
*/
Stype checkSymbolType(char *str)
{
    if (strcmp(str, ".data"))
    {
        return DATA;
    }

    if (strcmp(str, ".string"))
    {
        return STRING;
    }

    if (strcmp(str, ".entry"))
    {
        return ENTRY;
    }

    if (strcmp(str, ".extern"))
    {
        return EXTERN;
    }

    return CODE;
}