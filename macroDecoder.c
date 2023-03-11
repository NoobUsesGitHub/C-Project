#include <stdio.h>
#include <string.h>
#include "struct.h"
#include "helpers.c"


void macroDecoder(FILE* fp,FileList* node)
{
    char str[150];
    int i=0;
    while (fgets(str,150, fp)) 
    {
        i++;
        printf("%3d: %s\n", i, str);
    }   
    constNode(node);
    node->file=fp;
}