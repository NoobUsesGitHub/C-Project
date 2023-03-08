#include <stdio.h>
#include <string.h>


FileList macroDecoder(FILE* fp)
{
    char str[150];
    int i=0;
    while (fgets(str,150, fp)) 
    {
        i++;
        printf("%3d: %s\n", i, str);
    }   
    FileList f;
    f.file=fp;
    f.next=NULL;
    return f;
}