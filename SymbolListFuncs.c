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
    (*(s))->externalType = CODE;
    (*(s))->next = NULL;
}

/*
    input: a header node, a nase for the new macro and it's list of strings that it unfolds to
    output: the new macro node already connected to the list
*/
Symbol *addSymbolToList(Symbol *header, char *name, Stype type, int line, char *input, Stype externType)
{
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
        header->externalType = externType;
        if (input != NULL)
        {
            header->input = (char *)malloc((strlen(input) + 1) * (sizeof(char)));
            strcpy(header->input, input);
        }
    }
    else
    {
        while (current_node != NULL && existsAlready == FALSE)
        {
            if (strcmp(current_node->name, name) == 0)
            {
                if (type != EXTERN && line != -1) /*if line -1 we are in the extern phase and we don't really care about duplicates*/
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
            current_node->next->externalType = externType;
            if (input != NULL)
            {
                current_node->next->input = (char *)malloc((strlen(input) + 1) * (sizeof(char)));
                strcpy(current_node->next->input, input);
            }
        }
        else
        {
            if ((type != EXTERN && type != ENTRY) && (type != CODE && externType == EXTERN))
            {
                current_node->name = NULL;
                fprintf(stdout, "Symbol %s ay line %d exists already!!", name, line);
                return current_node->next;
            }
            /*
                entry
                code + externtype==extern
            */
            while (current_node->next != NULL)
            {
                current_node = current_node->next;
            }

            constSymbol(&(current_node->next));
            current_node->next->name = str;
            current_node->next->hash = hasher(str);
            current_node->next->type = type;
            current_node->next->line = line;
            current_node->next->externalType = externType;
            if (input != NULL)
            {
                current_node->next->input = (char *)malloc((strlen(input) + 1) * (sizeof(char)));
                strcpy(current_node->next->input, input);
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
    if (strcmp(str, "data") == 0)
    {
        return DATA;
    }

    if (strcmp(str, "string") == 0)
    {
        return STRING;
    }

    if (strcmp(str, "entry") == 0)
    {
        return ENTRY;
    }

    if (strcmp(str, "extern") == 0)
    {
        return EXTERN;
    }

    return CODE;
}

/*
    input: a string, the symbol table
    output: the line where the symbol appeared, if it doesn't exist,-1
*/
int existInSymbolTable(char *oper, Symbol *sym_list, int mode)
{
    double hsh = hasher(oper);
    int line = -1;
    while (sym_list != NULL)
    {
        if (sym_list->hash == hsh && (sym_list->line != -1 || sym_list->type == EXTERN && sym_list->line == -1))
            if (sym_list->type == EXTERN)
                line = 0;
        sym_list = sym_list->next;
    }
    if (sym_list != NULL && sym_list->hash != 0 && sym_list->hash != hsh)
    {
        return -1;
    }
    return line;
}

/*
    input: a string, the symbol table
    output: the symobol's type appeared, if it doesn't exist default CODE
    we assume we check before if it exists, but we have defualt anyway
*/
Stype symbolTypeFromTable(char *oper, Symbol *sym_list)
{
    double hsh = hasher(oper);

    while (sym_list != NULL)
    {
        if (sym_list->hash == hsh)
            return (sym_list->type == EXTERN || sym_list->externalType == EXTERN) ? EXTERN : sym_list->type;
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
    while (header != NULL && header->name != NULL)
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
    while (header != NULL && header->name != NULL && i < numOfSymbols)
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
    return ((Symbol *)a)->line < ((Symbol *)b)->line;
}

/*
    input: the list of symbols
    will go through every ENTRY node and will update it with it's corresponding label which appeared somewhere
*/
void fixEntryPositions(Symbol *dataHeader)
{
    Symbol *pointer = NULL;
    Symbol *current_node = dataHeader;
    bool found = FALSE;
    while (current_node != NULL && current_node->name != NULL)
    {
        if (current_node->type == ENTRY && current_node->line == -1)
        {
            found = FALSE;
            pointer = dataHeader;
            while (pointer != NULL && !found)
            {
                if (pointer->type != ENTRY && pointer->hash == current_node->hash)
                {
                    current_node->line = pointer->line;
                    found = TRUE;
                }
                pointer = pointer->next;
            }
        }
        current_node = current_node->next;
    }
}
