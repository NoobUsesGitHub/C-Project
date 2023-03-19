#include <stdio.h>
#include <string.h>
#include "prototypes.h"

#define coment ';'
#define delimints "    \t \f \r"


FileList* toBinary(FILE *fp, char *fileName)
{/*

    int i = 0;
    bool macroCollectionStarted = FALSE, skp = FALSE;
    MacroList *header, *curMacro;
    constMacroList(&header);
    char bit = ' ',*line[MAXLINESIZE], *pch = NULL, *str[MAXLINESIZE];
    char strNewName[strlen(fileName)];

    FileList *macroFileNode;
    constNode(&macroFileNode);
    
    █▄ ▄█ ▄▀▄ █▄▀ ██▀    ▄▀▀ █   ██▀ ▄▀▄ █▀▄ ██▀ █▀▄
    █ ▀ █ █▀█ █ █ █▄▄    ▀▄▄ █▄▄ █▄▄ █▀█ █▀▄ █▄▄ █▀▄
    
    strcpy(strNewName, fileName);
    strNewName[strlen(strNewName) - 1] = 'm';
    macroFileNode->fileName = (char *)malloc(strlen(strNewName) * sizeof(char));
    strcpy(macroFileNode->fileName, strNewName);
    /*to change
    macroFileNode->file = fopen(strNewName, "w");
    if (fp == NULL || macroFileNode->file == NULL)
    {
        macroFileNode->file = NULL;
        printf("File is not correct");
        return macroFileNode;
    }

    while (fgets(str, 85, fp) != NULL)
    {
        /*skip lines of comments
        sscanf(str, "%c", &bit);
        if ((int)bit == ((int)coment))
            skp = TRUE;

        pch = strtok(str, delimints); start strtok

        if (strcmp(pch, "endmcr") == 0 || strcmp(pch, "endmcr\n") == 0)
        {
            skp = TRUE;
            macroCollectionStarted = FALSE;
        }

        if (macroCollectionStarted == TRUE)
        {
            addLineToNode(curMacro, str);
            skp = TRUE;
        }

        while ((pch != NULL) && (skp != TRUE) && (macroCollectionStarted == FALSE))
        {
            checking for mactros
            if (strcmp(pch, "mcr") == 0)
            {
                macroCollectionStarted = TRUE;
                pch = strtok(NULL, delimints);
                curMacro = addMacroToList(header, pch, NULL);
                skp = TRUE;
            }

            if (skp == FALSE&&isspace(pch)==0)
            {
                if (dumpIfexistsInMacro(header, hasher(pch),macroFileNode->file) == 0)
                {
                    fprintf(macroFileNode->file,"%s ", pch);
                }
            }

            pch = strtok(NULL, delimints);
        }
        skp = FALSE;
    }

    freeList(header);

     tochange*/
     printf("yeah");
     return NULL;
}