#include <stdio.h>
#include <string.h>
#include "prototypes.h"

FileList *toBinary(FILE *fp, char *fileName)
{
    int IC = -1, DC = 0, wordCount = 0, stype = 0; /*wordCount=L*/
    bool skp = FALSE, foundSymbol = FALSE, foundErr = FALSE, foundLabel = FALSE;
    char bit = ' ', label[MAXLABELSIZE], dataTester[7], opcode[4], oper1[MAXLABELSIZE], oper2[MAXLABELSIZE], *pch = NULL, str[MAXLINESIZE];
    char strNewName[strlen(fileName)];
    Symbol *dataHeader, *dataNode;

    constSymbol(&dataHeader);
    constSymbol(&dataHeader);

    FileList *binaryFileNode;
    constNode(&binaryFileNode);
    /*
    █▄ ▄█ ▄▀▄ █▄▀ ██▀    ▄▀▀ █   ██▀ ▄▀▄ █▀▄ ██▀ █▀▄
    █ ▀ █ █▀█ █ █ █▄▄    ▀▄▄ █▄▄ █▄▄ █▀█ █▀▄ █▄▄ █▀▄
    */
    strcpy(strNewName, fileName);
    strNewName[strlen(strNewName) - 1] = 'n'; /*change the name create function for concat*/
    binaryFileNode->fileName = (char *)malloc(strlen(strNewName) * sizeof(char));
    strcpy(binaryFileNode->fileName, strNewName);
    /*to change*/
    binaryFileNode->file = fopen(strNewName, "w");
    if (fp == NULL || binaryFileNode->file == NULL)
    {
        binaryFileNode->file = NULL;
        printf("File is not correct"); /*need to print out to STDOUT and say which line*/
        return binaryFileNode;
    }

    while (fgets(str, 85, fp) != NULL)
    {
        removeRedundantSpaces(str);
        IC++;
        clearStr(label, MAXLABELSIZE); /*clearing label*/
        clearStr(dataTester, 7);
        clearStr(oper1, MAXLABELSIZE);
        i = 0;
        bit = str;

        /*checking for comment*/
        if (*bit == comment)
            continue; /*skiiiiip*/

        /*checking for a label*/
        while (isLetter(*bit) == TRUE)
        {
            if (*bit == LABELEND)
            {
                label[i] = '\0';
                foundLabel = TRUE; /*will be used later*/
            }
            label[i] = *bit;
            i++;
        }

        if (foundLabel == FALSE)
        {
            bit = str;       /*reseting point*/
            clearStr(label); /*clearing label*/
        }

        /*jumping for the next word*/
        /*checking for symbols first*/
        while (isLetter(*bit) == FALSE)
            bit++;
        if (*bit == '\0' || bit != '\n')
            printf("weldp");

        i = 0;
        if (*bit == symbolMarker)/*we met a sybol!*/
        {
            bit++; /*skipping the dot!*/
            while (isLetter(*bit) == TRUE)
            {
                dataTester[i] = *bit;
                i++;
                bit++;
            }
            stype = checkSymbolType(dataTester);

            /*jumping for the next word*/
            while (isLetter(*bit) == TRUE)
                bit++;

            if (*bit == '\0' || bit != '\n')
                printf("weldp");

            i = 0;
            switch (stype)
            {
            case STRING:
                bit++; /*skipping the "*/
                while (*bit != '"')
                {
                    if (*bit == '\n')
                    {
                        printf("string finished with no end");
                        break;
                    }
                    oper1[i] = *bit;
                    i++;
                    bit++;
                }
                bit++;
                oper1[i] = '\0';

                /*

                    WTF AM I DOING

                    WITH THE OPERANDS?
                */

                if (foundLabel == FALSE)
                {
                    clearStr(label, MAXLABELSIZE);
                    sprintf(label, "X DC: %d", DC); /*adding a dummy name*/
                }
                dataNode = addSymbolToList(dataHeader, label, stype, DC);
                DC = DC + strlen(oper1) + 1;
                break;
            case EXTERN:
            case ENTRY:
                clearStr(label, MAXLABELSIZE);
                /*collecting label, we ignore the first label*/
                while (isLetter(*bit) == TRUE)
                {
                    label[i] = *bit;
                    i++;
                }
                label[i] = '\0';
                dataNode = addSymbolToList(dataHeader, label, stype, DC);
                DC++;
                break;

            case DATA:
                i = 0;
                while (*bit != '\n')
                {
                    if (isLetter(*bit) == TRUE)
                    {
                        oper1[i] = *bit;
                        i++;
                    }
                    bit++;
                }
                /*

                WTF AM I DOING WITH OPERANDS

                */
                if (foundLabel == FALSE)
                {
                    clearStr(label, MAXLABELSIZE);
                    sprintf(label, "X DC: %d", DC); /*adding a dummy name*/
                }

                dataNode = addSymbolToList(dataHeader, label, stype, DC);
                DC = DC + dataLength(oper1) + 1;
                break;
            }
            continue;
        }

        
        if(foundLabel==TRUE)/*if we have label, and still here, make it a code symbol*/
            dataNode=addSymbolToList(dataHeader,label,CODE,IC);
 
        /*breaking here for a moment, we have the instruction part of the first pass*/



        /* instruction label: opcode source-operand, target-operand
        label: opcode target-operand
        label: opcode


    */

        /*
             insturction LABEL will receive Instruction Counter
         */

        pch = strtok(str, delimints); /*start strtok*/

        if (foundLabel == TRUE) /*skiping label*/
            pch = strtok(NULL, delimints);


        /*with or without the label, we have at max 3 words now, the only thing is if the , is a word for itself*/
        while ((pch != NULL) && (skp != TRUE))
        {
            if (isSignal(pch))
            {
                signal = TRUE;
            }



            pch = strtok(NULL, delimints);
        }
        skp = FALSE;
    }

    if (foundErr == TRUE)
    {
        binaryFileNode->file = NULL;
    }else
    {
        /*dump symbol tables*/
    }
    /*create .ent .ext*/
    freeList(header);
    return binaryFileNode; /*tochange*/
}