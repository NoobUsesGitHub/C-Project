#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
* input: a pointer for a file node object
* output: the node 
*/
void constNode(FileList *f)
{
    f=(FileList*)malloc(sizeof(FileList));
    (*f).file=NULL;
    (*f).next=NULL;
}


void addToList(FileList header, FILE *fp)
{
    FileList new_node;
    if (header.file == NULL) 
    {
        header.file = fp;
    } else 
    {
        FileList *current_node = &header;
        while (current_node->next != NULL) 
        {
            current_node = current_node->next;
        }
        constNode(&new_node);
        new_node.file=fp;
        current_node->next = &new_node;
    }
}


/*
* input:a file node header
* will close all file objects
*/
void closeFileList(FileList *head)
{
    FileList next=*head;
    while((*head).next!=NULL)
    {
        fclose((*head).file);
        next=*((*head).next);
        free(head);
        (*head)=next;
    }
    /*fclose((*head).file);*/
    free(head);
}


FileList stringToFiles(int argc,char *argv[])
{
    int i;
    static char *asmblrType=".as";
    FileList header;
    char *str;
    FILE *temp;
    i=1;
    for(;i<=argc-1;i++)
    {
        str=argv[i];
        strcat(str,asmblrType);
        temp=fopen(str,"r");
        addToList(header,temp);
    }
    return header;    
}



