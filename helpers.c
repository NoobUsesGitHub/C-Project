#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "struct.h"

/*
* input: a pointer for a file node object
* output: the node 
*/
FileList nuller(FileList *f)
{
    *(f).file=(FILE*) malloc(sizeof(FILE));
    *(f).next=NULL;
    return *f;
}

/*
* input:a file node header
* will close all file objects
*/
void closeFileList(FileList *head)
{
    FileList next=*head;
    while(*(head).next!=NULL)
    {
        fclose(*(head).file);
        next=*(*(head).next);
        free(*(head));
        head=next;
    }
    fclose(*(head).file);
    free(head);
}


FileList stringToFiles(int argc,char *argv[])
{
    int i=0;
    FileList header,temp;
    char *str;
    header=nuller(header);
    temp=header;

    for(i=1;i<argv-1;i++)
    {
        str=argv[i];
        strcat(*str,'.as');
        temp.file=fopen(str,'r');
        temp=temp.next;
    }
    return header;    
}
