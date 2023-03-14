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
        /* u
        
▄▀▄ █▀▄ █▀▄    █▄█ ██▀ █▀▄ ██▀    ▀█▀ █▄█ ██▀    █▀▄ ██▀ ▄▀▀ ▄▀▄ █▀▄ ██▀ █▀▄    █ █▄ █ █▀ ▄▀▄ 
█▀█ █▄▀ █▄▀    █ █ █▄▄ █▀▄ █▄▄     █  █ █ █▄▄    █▄▀ █▄▄ ▀▄▄ ▀▄▀ █▄▀ █▄▄ █▀▄    █ █ ▀█ █▀ ▀▄▀ 
        
        */

        i++;
        int i=0;
  while (pch != NULL)
  {
    if(i==0)
    {
        if(pch[0]==';')
            printf ("first note is ; %c\n",pch[0]);
    }


    if(strcmp(pch,"mcr")==0)
    {
        printf("mcr started");
    }

    if(strcmp(pch,"endmcr")==0)
    {
        printf("mcr ended");
    }
    printf ("%s\n",pch);
    pch = strtok (NULL, "    \t \f \r");
    i++;
  }
        printf("%3d: %s\n", i, str);
    }

    return macroNode;/*tochange*/
}