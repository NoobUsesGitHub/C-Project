#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
* input: a pointer for a file node object
* output: the node 
*/
void constNode(FileList** f)
{
    *f=(FileList*)malloc(sizeof(FileList));
    (*(f))->file=NULL;
    (*(f))->next=NULL;
}


void addToList(FileList* header, FILE *fp)
{
    if (header->file == NULL )
    {
        header->file = fp;
    } else 
    {
        FileList *current_node = header;
        while (current_node->next != NULL) 
        {
            current_node = current_node->next;
        }
        constNode(&(current_node->next));
        current_node->next->file=fp;
    }
}


/*
* input:a file node header
* will close all file objects
*/
void closeFileList(FileList *head)
{
    FileList* next=head;
    while(next->next!=NULL)
    {
        fclose(head->file);
        next=head->next;
        free(head);
        head=next;
    }
    fclose(head->file);
    free(head->next);
    free(head);
}


void stringToFiles(int argc,char *argv[],FileList** header)
{
    int i;
    static char *asmblrType=".as";
    char *str;
    FILE *temp;
    i=1;
    constNode(header);
    for(;i<=argc-1;i++)
    {
        puts(argv[i]);
     /*   strcpy(str,argv[i]);
        strcat(str,asmblrType);
        temp=fopen(str,"r");
        addToList(*header,temp);*/
    }
}



