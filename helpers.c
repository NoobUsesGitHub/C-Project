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
    FileList header,temp;
    char *str;
    constNode(&header);
    temp.file=header.file;
    temp.next=header.next;
    
    i=1;

    for(;i<=argc-1;i++)
    {
        str=argv[i];
        strcat(str,asmblrType);
        temp.file=fopen(str,"r");
        temp=temp.next;
    }
    return header;    
}




void addToList(FileList header, FILE *fp)
{
    
    if (header == NULL) {
        header = new_node;
    } else {
        FileList *current_node = header;
        while (current_node->next != NULL) {
            current_node = current_node->next;
        }
        current_node->next = new_node;
}






}