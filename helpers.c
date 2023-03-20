#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "struct.h"
#include "prototypes.h"

/*
 * input: a pointer for a file node object
 * output: the node
 */
void constNode(FileList **f)
{
    *f = (FileList *)malloc(sizeof(FileList));
    (*(f))->file = NULL;
    (*(f))->fileName = NULL;
    (*(f))->next = NULL;
}

/*
input: a string that we want to hash
output: a double that is the encoded string
*/
double hasher(char *str)
{
    double size = strlen(str);
    double hash = 0;
    int i = 0;
    /*maybe change to while*/
    if (str[((int)size) - 1] == '\n')
        size--;
    while (str[i] != '\0')
    {
        if (str[i] != '\n')
            hash += ((int)(str[i])) / (size - i) * 7.0; /*hashing func- takes every letter and its place and calculates a key for it, adding them together*/
        i++;
    }
    return hash;
}

/*
    input: a header node, a name for the new macro and it's list of strings that it unfolds to
    output: the new macro node already connected to the list
*/
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
        current_node->next->hash = hasher(str);
        current_node->next->macroName = str;
        return current_node->next;
    }
}

void addToList(FileList *header, FILE *fp, char *fileName)
{
    char *str = (char *)malloc(strlen(fileName) * (sizeof(char) + 1));
    strcpy(str, fileName);
    if (header->file == NULL)
    {
        header->file = fp;
        header->fileName = str;
    }
    else
    {
        FileList *current_node = header;
        while (current_node->next != NULL)
        {
            current_node = current_node->next;
        }
        constNode(&(current_node->next));
        current_node->next->file = fp;
        current_node->next->fileName = str;
    }
}

/*
 * input:a file node header
 * will close all file objects
 */
void closeFileList(FileList *head)
{
    FileList *next = head;
    while (next->next != NULL)
    {
        fclose(head->file);
        free(head->fileName);
        next = head->next;
        free(head);
        head = next;
    }
    fclose(head->file);
    free(head->fileName);
    free(head->next);
    free(head);
}

void stringToFiles(int argc, char *argv[], FileList **header)
{
    int i, maxSize = 0;
    static char *asmblrType = ".as";
    i = 1;
    for (; i <= argc - 1; i++)
    {
        if (maxSize < strlen(argv[i]))
            maxSize = strlen(argv[i]);
    }
    char *str = (char *)malloc(maxSize * (sizeof(char) + 1));
    FILE *temp;
    i = 1;
    constNode(header);
    for (; i <= argc - 1; i++)
    {
        strcpy(str, argv[i]);
        strcat(str, asmblrType);
        temp = fopen(str, "r");
        addToList(*header, temp, str);
    }
    free(str);
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
    (*(m))->size = 0;
    (*(m))->next = NULL;
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

/*
    input: a list of strings and their size
    will go through the list and print them
*/
void printList(char **macro, int size, FILE *fp)
{

    while (size != 0)
    {
        fprintf(fp, "%s", *macro);
        macro++;
        size--;
    }
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
