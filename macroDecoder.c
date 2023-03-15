#include <stdio.h>
#include <string.h>
#include "struct.h"
#define MAXLINESIZE 85

FileList *macroDecoder(FILE *fp, char *fileName)
{
    
    int i = 0,skp = 0;
    char *line[MAXLINESIZE],*pch=NULL,*str[MAXLINESIZE];
    char strNewName[strlen(fileName)];

    FileList *macroNode;
    constNode(&macroNode);
    /*
    █▄ ▄█ ▄▀▄ █▄▀ ██▀    ▄▀▀ █   ██▀ ▄▀▄ █▀▄ ██▀ █▀▄ 
    █ ▀ █ █▀█ █ █ █▄▄    ▀▄▄ █▄▄ █▄▄ █▀█ █▀▄ █▄▄ █▀▄ 
    */
    strcpy(strNewName, fileName);
    strNewName[strlen(strNewName) - 1] = 'm';
    macroNode->fileName = (char *)malloc(strlen(strNewName) * sizeof(char));
    strcpy(macroNode->fileName, strNewName);
    /*to change*/
    macroNode->file = fopen(strNewName, "w");
    if (fp == NULL ||macroNode->file== NULL)
    {
        macroNode->file=NULL;
        printf("File is not correct");
        return macroNode;
    }

    while (fgets(line, 85, f))
    {
        pch = strtok(line, "    \t \f \r");
        i = 0;
        while (pch != NULL)
        {
            if (i == 0)
            {
                if (pch[0] == ';')
                {
                    printf("first note is ; %c\n", pch[0]);
                    skp = 1;
                }
            }
            if (strcmp(pch, "mcr") == 0)
            {
                printf("mcr started");
                skp = 1;
            }
            if (strcmp(pch, "endmcr") == 0)
            {
                printf("mcr ended");
                skp = 1;
            }
            if (skp == 0)
                printf("%s\n", pch);

            pch = strtok(NULL, "    \t \f \r");
            i++;
            skp = 0;
        }
    }

    
    return macroNode; /*tochange*/
}