#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <struct.h>

FileList nuller(FileList f)
{
    FileList f;
    f.file=(FILE*) malloc(sizeof(FILE));
    f.next=NULL;
    return f;
}


void closeFileList(FileList head)
{
    while(head.next!=NULL)
    {
        fclose(head.file);    
        head=*(head.next);
    }
    fclose(head.file);
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
        temp.p=fopen(str,'r');
        temp=*temp.next;
    }
    return header;    
}
