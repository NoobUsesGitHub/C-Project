#include <stdio.h>
#include <string.h>
#include "prototypes.h"



FileList* toBinary(FILE *fp, char *fileName)
{
    int IC=0,DC=0,wordCount=0;/*wordCount=L*/
    bool skp = FALSE,signal=FALSE,foundErr=FALSE;
    char bit = ' ',label, *pch = NULL, str[MAXLINESIZE];
    char strNewName[strlen(fileName)];

    FileList *binaryFileNode;
    constNode(&binaryFileNode);
    /*
    █▄ ▄█ ▄▀▄ █▄▀ ██▀    ▄▀▀ █   ██▀ ▄▀▄ █▀▄ ██▀ █▀▄
    █ ▀ █ █▀█ █ █ █▄▄    ▀▄▄ █▄▄ █▄▄ █▀█ █▀▄ █▄▄ █▀▄
    */
    strcpy(strNewName, fileName);
    strNewName[strlen(strNewName) - 1] = 'm';
    binaryFileNode->fileName = (char *)malloc(strlen(strNewName) * sizeof(char));
    strcpy(binaryFileNode->fileName, strNewName);
    /*to change*/
    binaryFileNode->file = fopen(strNewName, "w");
    if (fp == NULL || binaryFileNode->file == NULL)
    {
        binaryFileNode->file = NULL;
        printf("File is not correct");/*need to print out to STDOUT and say which line*/
        return binaryFileNode;
    }

    while (fgets(str, 85, fp) != NULL)
    {
        

        /*might need to skip here on comments, not in macro decoder*/
        
        /* instruction label: opcode source-operand, target-operand
            label: opcode target-operand
            label: opcode 

        
        */

        pch = strtok(str, delimints); /*start strtok*/
        /*need to check for labels first LABELS MAX SIZE=30(+1 for :)
            insturction LABEL will receive Instruction Counter
        */
        while ((pch != NULL) && (skp != TRUE))
        {
            if(isSignal(pch))
            {
                signal=TRUE;
            }

            sscanf(str, "%c", &bit);
            if ((int)bit == ((int)suggest))
            {    
                /* data and string LABEL will recieve Data Counter*/
                /*check if data or string*/
                /*if entry has label, ignore label*/
                /*check if external*/
                /*if external has label, ignore label*/
                continue;
            }


            







            if (skp == FALSE&&isspace(pch)==0)
            {
                if (dumpIfexistsInMacro(header, hasher(pch),binaryFileNode->file) == 0)
                {
                    fprintf(binaryFileNode->file,"%s ", pch);
                }
            }

            pch = strtok(NULL, delimints);
        }
        skp = FALSE;
    }

    if(foundErr==TRUE)
    {
        binaryFileNode->file=NULL;
    }
    /*create .ent .ext*/
    freeList(header);
    return binaryFileNode; /*tochange*/  
}