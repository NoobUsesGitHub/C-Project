#include <stdio.h>
#include <string.h>
#include "helpers.c"


FileList macroDecoder(FILE* fp)
{
    char str[150];
    int i=0;
    while (fgets(str,150, fp)) 
    {
        i++;
        printf("%3d: %s\n", i, str);
    }   
    return NULL;
}