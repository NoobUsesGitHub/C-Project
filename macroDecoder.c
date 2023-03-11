#include <stdio.h>
#include <string.h>
#include "struct.h"
#define MAXLINESIZE 85


FileList* macroDecoder(FILE* fp,char* fileName)
{
    char str[MAXLINESIZE];
    int i=0;
    FileList *macroNode;
    constNode(&macroNode);
/*
▀█▀ ▄▀▄    █▀ █ ▀▄▀    ▀▄▀ ▄▀▄ █ █    █▀ █ █ ▄▀▀ █▄▀ 
 █  ▀▄▀    █▀ █ █ █     █  ▀▄▀ ▀▄█    █▀ ▀▄█ ▀▄▄ █ █ 
    */char strNewName[strlen(fileName)];
    strcpy(strNewName,fileName);
    strNewName[strlen(strNewName)-1]='m';
    macroNode->fileName=(char*)malloc(strlen(strNewName)*sizeof(char));
    strcpy(macroNode->fileName,strNewName);/*to change*/
    macroNode->file=fopen(strNewName,"w");
    while (fgets(str,MAXLINESIZE, fp)) 
    {
        /*
        
▄▀▄ █▀▄ █▀▄    █▄█ ██▀ █▀▄ ██▀    ▀█▀ █▄█ ██▀    █▀▄ ██▀ ▄▀▀ ▄▀▄ █▀▄ ██▀ █▀▄    █ █▄ █ █▀ ▄▀▄ 
█▀█ █▄▀ █▄▀    █ █ █▄▄ █▀▄ █▄▄     █  █ █ █▄▄    █▄▀ █▄▄ ▀▄▄ ▀▄▀ █▄▀ █▄▄ █▀▄    █ █ ▀█ █▀ ▀▄▀ 
        
        */
        i++;
        printf("%3d: %s\n", i, str);
    }

    return macroNode;/*tochange*/
}