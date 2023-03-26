#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "helpers.h"
#include "SymbolListFuncs.h"

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
        header->line = line;
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
            current_node->next->line = line;
        }
        else
        {
            current_node->name = NULL;
            fprintf(stderr, "Symbol%s exists already!!", name);
            return current_node->next;
        }
    }
    return current_node;
}

/*
 * input:a file node header
 * will close all file objects
 */
void freeSyList(Symbol *head)
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

/*
    input: a string, the symbol table
    output: the line where the symbol appeared, if it doesn't exist,-1
*/
Stype existInSymbolTable(char *oper, Symbol *sym_list)
{
    double hsh = hasher(oper);

    while (sym_list->next != NULL)
    {
        if (sym_list->hash == hsh)
            return sym_list->line;
        sym_list = sym_list->next;
    }
    if (sym_list != NULL && sym_list->hash != 0 && sym_list->hash != hsh)
    {
        return -1;
    }
    return sym_list->line;
}

/*
    input: a string, the symbol table
    output: the symobol's type appeared, if it doesn't exist default CODE
    we assume we check before if it exists, but we have defualt anyway
*/
int symbolTypeFromTable(char *oper, Symbol *sym_list)
{
    double hsh = hasher(oper);

    while (sym_list->next != NULL)
    {
        if (sym_list->hash == hsh)
            return sym_list->type;
        sym_list = sym_list->next;
    }
    if (sym_list != NULL && sym_list->hash != 0 && sym_list->hash != hsh)
    {
        return CODE;
    }
    return sym_list->type;
}