#include <stdio.h>
#include <string.h>
#include <struct.h>

FileList nuller(FileList f)
{
    f.p=NULL;
    f.next=NULL;
    return f;
}


void closeFileList(FileList head)
{
    while(head.next!=NULL)
    {
        fclose(head.p);    
        head=*(head.next);
    }
    fclose(head.p);
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
