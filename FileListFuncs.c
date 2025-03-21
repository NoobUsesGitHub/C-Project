#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "helpers.h"
#include "FileListFuncs.h"

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
    input: a file header and a file to add it to and it's name
    will add the file to the linked list
*/
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

/*
 * input:a file node header
 * will remove all file objects
 */
void removeFileList(FileList *head)
{
    FileList *next = head;
    while (next->next != NULL)
    {
        fclose(head->file);
        remove(head->fileName);
        free(head->fileName);
        next = head->next;
        free(head);
        head = next;
    }
    fclose(head->file);
    remove(head->fileName);
    free(head->fileName);
    free(head->next);
    free(head);
}

/*
    input: the input from the user
    output: will open the files and keep them in the filelist node header included
*/
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
    input: a file list object
    will close it's file and reopen it on read only
*/
void reOpen(FileList *tempInputNode)
{
    fclose(tempInputNode->file);
    tempInputNode->file = fopen(tempInputNode->fileName, "r");
}