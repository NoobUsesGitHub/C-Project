#include <stdio.h>
#include <string.h>
#include "struct.h"
#define MAXLINESIZE 85


FILE* macroDecoder(FILE* fp,char* fileName)
{
    char str[MAXLINESIZE];
    int i=0;
    char strNewName[strlen(fileName)];
    strcpy(strNewName,fileName);
    strNewName[strlen(strNewName)-1]='m';
    FILE* fMacro=fopen(fileName,"w");
    while (fgets(str,MAXLINESIZE, fp)) 
    {
        i++;
        printf("%3d: %s\n", i, str);
    }
    puts(strNewName);
    return fMacro;/*tochange*/
}