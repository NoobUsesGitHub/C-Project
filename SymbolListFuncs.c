#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "helpers.h"
#include "struct.h"
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
    (*(s))->externalType = 0;
    (*(s))->next = NULL;
}

/*
    input: a header node, a nase for the new macro and it's list of strings that it unfolds to
    output: the new macro node already connected to the list
*/
Symbol *addSymbolToList(Symbol *header, char *name, Stype type, int line, char *input)
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
        switch (type)
        {
        case EXTERN:
            header->externalType = EXTERN;
            break;

        case ENTRY:
            header->externalType = ENTRY;
            break;

        default:
            header->externalType = CODE;
            break;
        }
        header->input = (char *)malloc((strlen(input) + 1) * (sizeof(char)));
        strcpy(header->input, input);
    }
    else
    {
        while (current_node->next != NULL && existsAlready == FALSE)
        {
            if (type != EXTERN && strcmp(current_node->name, name))
            {
                existsAlready = TRUE;
                continue;
            }
            current_node = current_node->next;
        }
        if (existsAlready == FALSE)
        {
            constSymbol(&(current_node->next));
            current_node->next->name = str;
            current_node->next->hash = hasher(str);
            current_node->next->type = type;
            current_node->next->line = line;
            switch (type)
            {
            case EXTERN:
                current_node->next->externalType = EXTERN;
                break;

            case ENTRY:
                current_node->next->externalType = ENTRY;
                break;

            default:
                current_node->next->externalType = CODE;
                break;
            }

            current_node->next->input = (char *)malloc((strlen(input) + 1) * (sizeof(char)));
            strcpy(current_node->next->input, input);
        }
        else
        {
            if (type != EXTERN && type != ENTRY)
            {
                current_node->name = NULL;
                fprintf(stdout, "Symbol %s exists already!!", name);
                return current_node->next;
            }
            else if (type == ENTRY)
            {
                current_node->externalType=ENTRY;
            }
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
        free(head->input);
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
int existInSymbolTable(char *oper, Symbol *sym_list)
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
Stype symbolTypeFromTable(char *oper, Symbol *sym_list)
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

/*
    input: the header of a symbol list
    output: how many symbols aren't code
*/
int countSymbols(Symbol *header)
{
    int i = 0;
    while (header->input != NULL)
    {
        if (header->type != CODE && header->type != ENTRY && header->type != EXTERN)
            i++;
        header = header->next;
    }
    return i;
}

/*
    input: an array, number of symbols should be filled there and the symbol list header
    will fill the array with only the symbols that aren't codes
*/
void fillSymArr(Symbol *arr[], int numOfSymbols, Symbol *header)
{
    int i = 0;
    while (header->input != NULL && i < numOfSymbols)
    {
        if (header->type != CODE)
        {
            arr[i] = header;
            i++;
        }
        header = header->next;
    }
}

/*
    input: two pointers
    output: 1 if as symbols a's line position is greater than b's line position
*/
int SymbolCompare(const void *a, const void *b)
{
    return ((Symbol *)a)->line > ((Symbol *)b)->line;
}