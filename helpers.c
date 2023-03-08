#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FileList nuller(FileList*);
/*
* input: a pointer for a file node object
* output: the node 
*/
FileList nuller(FileList *f)
{
    (*f).file=(FILE*) malloc(sizeof(FILE));
    (*f).next=NULL;
    return *f;
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
    header=nuller(&header);
    temp.file=header.file;
    temp.next=header.next;
    
    i=1;

    for(;i<=argc-1;i++)
    {
        str=argv[i];
        strcat(str,asmblrType);
        temp.file=fopen(str,"r");
        temp=(*temp.next);
    }
    return header;    
}
