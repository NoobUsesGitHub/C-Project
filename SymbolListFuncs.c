#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "helpers.h"
#include "struct.h"
#include "outputMaker.h"
#include "SymbolListFuncs.h"

/*
 * input: a pointer for null symbol node object
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
    input: a header node, a naצe for the new Symbol and it's type, line number, it's string of data and its other type
   will link the new symbol to the main table
*/
void *addSymbolToList(Symbol *header, char *name, Stype type, int line, char *input, Stype externType)
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
        else
        {
            header->input = NULL;
        }
    }
    else
    { /*checking the first spot*/
        if (strcmp(current_node->name, name) == 0)
        {
            if ((type != EXTERN && type != ENTRY) && line != -1) /*if line -1 we are in the extern phase and we don't really care about duplicates*/
            {
                existsAlready = TRUE;
            }
            if (current_node->next != NULL)
                current_node = current_node->next;
        }

        while (current_node->next != NULL && existsAlready == FALSE)
        {
            if (strcmp(current_node->name, name) == 0)
            {
                if ((type != EXTERN && type != ENTRY) && line != -1) /*if line -1 we are in the extern phase and we don't really care about duplicates*/
                {
                    existsAlready = TRUE;
                    continue;
                }
            }
            current_node = current_node->next;
        }

        if (current_node->next == NULL && strcmp(current_node->name, name) == 0)
        {
            if ((type != EXTERN && type != ENTRY) && line != -1) /*if line -1 we are in the extern phase and we don't really care about duplicates*/
            {
                existsAlready = TRUE;
            }
        }
        /*last check on current*/
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
                return 0;
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
    return 0;
}

/*
 * input:a Symbol node header
 * will close all file objects
 */
void freeSyList(Symbol *head)
{
    Symbol *next = head;
    while (next != NULL)
    {
        free(head->name);
        if(head->input!=NULL)
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
    while (sym_list != NULL && line == -1)
    {
        if (sym_list->hash == hsh && (sym_list->line != -1 || (sym_list->type == EXTERN && sym_list->line == -1)))
        {
            if (sym_list->type == EXTERN)
                line = 0;
            else
            {
                line = sym_list->line;
            }
        }
        sym_list = sym_list->next;
    }
    if (sym_list != NULL && line == -1 && sym_list->hash != 0 && sym_list->hash != hsh)
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
        if (header->type == DATA || header->type == STRING)
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
    used for Qsort
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


/*
    input: a header of the symbols table, the file name, a data symbol type, and the extention
    will push all the data symbols of that type to a file
*/
void dumpSymbols(Symbol *header, char *fileName, Stype stype, char *extention)
{
    int size = strlen(fileName) + 1;
    char newName[size];
    char binary[BINARY_LINE_SIZE];
    bool found_any = FALSE;
    char *bit = NULL;
    strcpy(binary, "00000000000000");
    strcpy(newName, fileName);
    strcpyBySteps(newName + strlen(newName) + 1 - strlen(extention), extention, 4);
    newName[size] = 0;
    FILE *fp = fopen(newName, "w");
    if (fp == NULL)
        fprintf(stdout, "we had trouble opening a %s file", extention);
    while (header != NULL)
    {
        if (stype != EXTERN)
        {
            if (header->type == stype || (header->externalType == stype && header->externalType == CODE) || (stype == DATA && header->type == STRING))
            {
                found_any = TRUE;
                intToBinary(binary, header->line);
                bit = binary;
                while (*bit != '\0')
                {
                    *bit = binaryTranslate(*bit);
                    bit++;
                }
                fprintf(fp, "%s\t%s\n", header->name, binary);
                strcpy(binary, "00000000000000");
            }
            else
            {
                if (header->type != stype && header->externalType == stype)
                {
                    found_any = TRUE;
                    intToBinary(binary, header->line);
                    bit = binary;
                    while (*bit != '\0')
                    {
                        *bit = binaryTranslate(*bit);
                        bit++;
                    }
                    fprintf(fp, "%s\t%s\n", header->name, binary);
                    strcpy(binary, "00000000000000");
                }
            }
        }
        else
        {
            if (header->type == CODE && header->externalType == EXTERN)
            {
                found_any = TRUE;
                intToBinary(binary, header->line);
                bit = binary;
                while (*bit != '\0')
                {
                    *bit = binaryTranslate(*bit);
                    bit++;
                }
                fprintf(fp, "%s\t%s\n", header->name, binary);
                strcpy(binary, "00000000000000");
            }
        }
        header = header->next;
    }
    fclose(fp);
    if (!found_any)
        remove(newName);
}

/*
input: the header of the list of symbols, the Instruction counter and file to print to
will create an array and print the symbols ordered by line
*/
void dumpSymbolsToMainFile(Symbol *header, int *IC, FILE *fp, int mode)
{
    int numOfSymbols = countSymbols(header);
    Symbol *arr[numOfSymbols];
    fillSymArr(arr, numOfSymbols, header);
    qsort(arr, numOfSymbols, sizeof(Symbol *), SymbolCompare);

    int i = 0;
    numOfSymbols = countSymbols(header);
    for (; i < numOfSymbols; i++)
    {
        switch (arr[i]->type)
        {
        case STRING:
            dumpStr(arr[i]->input, IC, mode, fp);
            break;

        case DATA:
            dumpDataOpers(arr[i]->input, IC, mode, fp);
            break;
        case CODE:
        case EXTERN:
        case ENTRY:
            break;
        }
    }
}