#include <stdio.h>
#include <string.h>
#include "helpers.h"
#include "binaryMaker.h"
#include "FileListFuncs.h"
#include "SymbolListFuncs.h"
#include "struct.h"

FileList *toBinary(FILE *fp, char *fileName)
{
    Operator *op_table = createOperatorsTable();

    int IC = 100, DC = 0, wordCount = 0, spaceCount = 0, i = 0; /*wordCount=L*/
    Stype stype = 0;
    bool skp = FALSE, foundSymbol = FALSE, foundErr = FALSE, foundLabel = FALSE;
    char *bit = NULL, label[MAX_LABEL_SIZE], dataTester[7], opcode[5];
    char oper1[MAX_LABEL_SIZE], oper2[MAX_LABEL_SIZE], *pch = NULL, str[MAX_LINE_SIZE];
    char temp[MAX_LABEL_SIZE];
    char strNewName[strlen(fileName)];
    Symbol *dataHeader = NULL;
    Symbol *dataNode = NULL;
    OperatorType op_code_type;

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
        fprintf(stdout, "File is not correct\n"); /*need to print out to STDOUT and say which line*/
        return binaryFileNode;
    }

    while (fgets(str, MAX_LINE_SIZE, fp) != NULL) /*first pass*/
    {
        removeRedundantSpaces(str);
        /*IC++;*/
        clearStr(label, MAX_LABEL_SIZE); /*clearing label*/
        clearStr(dataTester, 7);
        clearStr(opcode, 5);
        clearStr(oper1, MAX_LABEL_SIZE);
        clearStr(oper2, MAX_LABEL_SIZE);
        i = 0;
        foundLabel=FALSE;
        bit = str;

        /*checking for comment */
        if (*bit == COMMENT || *bit == '\n' || *bit == '\0')
        {
            /*IC--;*/
            continue; /*skiiiiip*/
        }

        /*checking for a label*/
        while (isLetter(bit) == TRUE && foundLabel == FALSE)
        {
            if (*bit == LABEL_END)
            {
                label[i] = '\0';
                foundLabel = TRUE; /*will be used later*/
                bit++;
                continue;
            }
            label[i] = *bit;
            i++;
            bit++;
        }

        if (foundLabel == FALSE)
        {
            bit = str;                       /*reseting point*/
            clearStr(label, MAX_LABEL_SIZE); /*clearing label*/
        }
        else
        {
            /*check if label is a real register or opcode*/
            if (stringToOperatorType(label) != ERROR_NA || realRegister(label) != -1)
            {
                fprintf(stdout, "label %s is a register or opcode!\n", label);
                foundErr = TRUE;
            }
        }

        /*jumping for the next word*/
        /*checking for symbols first*/
        while (isLetter(bit) == FALSE)
            bit++;
        
        if (*bit == '\0')
        {
            fprintf(stdout, "line %d eneded unexpectandly\n", IC);
            foundErr = TRUE;
        }

        i = 0;
        if (*bit == symbolMarker) /*we met a sybol!*/
        {
            bit++; /*skipping the dot!*/
            while (isLetter(bit) == TRUE)
            {
                dataTester[i] = *bit;
                i++;
                bit++;
            }
            stype = checkSymbolType(dataTester);

            /*jumping for the next word*/
            while (isLetter(bit) == FALSE)
                bit++;

            if (*bit == '\0' || *bit == '\n')
            {
                fprintf(stdout, "line %d eneded unexpectandly\n", IC);
                foundErr = TRUE;
            }

            i = 0;
            switch (stype)
            {
            case STRING:
                bit++;              /*skipping the "*/
                while (*bit != '"') /*check how many "" you have*/
                {
                    if (*bit == '\n')
                    {
                        fprintf(stdout, "string finished with no end\n");
                        foundErr = TRUE;
                        break;
                    }
                    oper1[i] = *bit;
                    i++;
                    bit++;
                }
                bit++;
                oper1[i] = '\0';

                dumpStr(oper1, &IC, SIMULATION, NULL);

                if (foundLabel == FALSE)
                {
                    clearStr(label, MAX_LABEL_SIZE);
                    sprintf(label, "X DC: %d", DC); /*adding a dummy name*/
                }
                dataNode = addSymbolToList(dataHeader, label, stype, DC, oper1, CODE);
                DC = DC + strlen(oper1) + 1;
                break;
            case EXTERN:
                clearStr(label, MAX_LABEL_SIZE);
                /*collecting label, we ignore the first label*/
                while (isLetter(bit) == TRUE)
                {
                    label[i] = *bit;
                    bit++;
                    i++;
                }
                label[i] = '\0';
                dataNode = addSymbolToList(dataHeader, label, stype, -1, label, CODE);
                break;
            case ENTRY:
                clearStr(label, MAX_LABEL_SIZE);
                /*collecting label, we ignore the first label*/
                while (isLetter(bit) == TRUE)
                {
                    label[i] = *bit;
                    bit++;
                    i++;
                }
                label[i] = '\0';
                dataNode = addSymbolToList(dataHeader, label, stype, DC, label, CODE);
                DC++;
                break;

            case DATA:
                i = 0;
                while (*bit != '\n')
                {
                    if (isLetter(bit) == TRUE)
                    {
                        oper1[i] = *bit;
                        i++;
                    }
                    bit++;
                }

                if (foundLabel == FALSE)
                {
                    clearStr(label, MAX_LABEL_SIZE);
                    sprintf(label, "X DC: %d", DC); /*adding a dummy name*/
                }

                dataNode = addSymbolToList(dataHeader, label, stype, DC, oper1, CODE);
                DC++;
                /*dumpDataOpers(oper1, &DC, SIMULATION, NULL); maybe not?*/
                break;
            }
            continue;
        }

        if (foundLabel == TRUE) /*if we have label, and still here, make it a code symbol*/
            dataNode = addSymbolToList(dataHeader, label, CODE, IC, NULL, CODE);

        /* instruction label: opcode source-operand, target-operand
        label: opcode target-operand
        label: opcode*/
        spaceCount = countSpace(str);
        strcpy(temp, str);
        pch = strtok(temp, delimints); /*start strtok*/

        if (foundLabel == TRUE) /*skipping labels*/
        {
            pch = strtok(NULL, delimints);
            spaceCount--;
        }
        if (spaceCount > 2)
        {
            fprintf(stdout, "operator %s was found with too many operands\n", opcode);
            foundErr = TRUE;
            continue;
        }
        switch (spaceCount)
        {
        case 0: /*opcode*/
            break;

        case 1: /*opcode oper1*/
            strcpy(opcode, pch);
            op_code_type = stringToOperatorType(opcode);
            pch = strtok(NULL, delimints);
            strcpy(oper1, pch);
            oper1[strlen(oper1) - 1] = '\0';
            break;

        case 2:
            /*opcode oper1, oper 2*/
            strcpy(opcode, pch);
            op_code_type = stringToOperatorType(opcode);
            pch = strtok(NULL, delimints);
            strcpy(oper1, pch);
            oper1[strlen(oper1) - 1] = '\0'; /*skipping the ,*/
            pch = strtok(NULL, delimints);
            strcpy(oper2, pch);
            oper2[strlen(oper2) - 1] = '\0';
            break;
        }

        /*keep an eye open for jmp jsr and bne NEED TO FIX STILL*/
        if (op_code_type == JMP || op_code_type == JSR || op_code_type == BNE)
            spaceCount = breakDownJumps(oper1, oper2, label);

        /*now we have the opcode, the two operators and the label if any,*/

        if (op_code_type == ERROR_NA)
        { /*if opcode a real opcode*/
            fprintf(stdout, "opcode %s not found\n", opcode);
            foundErr = TRUE;
        }

        if (stringToOperatorType(oper1) != ERROR_NA || stringToOperatorType(oper1) != ERROR_NA)
        { /*if any operator is a name of an opecode*/
            fprintf(stdout, "operator src %s not found\n", oper1);
            foundErr = TRUE;
        }
        if (stringToOperatorType(oper2) != ERROR_NA || stringToOperatorType(oper2) != ERROR_NA)
        { /*if any operator is a name of an opecode*/
            fprintf(stdout, "operator src %s not found\n", oper2);
            foundErr = TRUE;
        }

        dumpFullInstruction(label, opcode, oper1, oper2, spaceCount, &IC, SIMULATION, op_table, dataHeader, binaryFileNode->file);
    }
    if (foundErr == TRUE)
    {
        fprintf(stdout, "there are error's in the first pass!\n");
    }
    else
    {
        addToData(dataHeader, IC);
        fixEntryPositions(dataHeader);
    }
    rewind(fp);

    fprintf(binaryFileNode->file, "%d %d\n", IC - 100, DC);
    IC = 100;

    while (fgets(str, MAX_LINE_SIZE, fp) != NULL) /*second pass*/
    {
        removeRedundantSpaces(str);
        /*IC++;*/
        clearStr(label, MAX_LABEL_SIZE); /*clearing label*/
        clearStr(dataTester, 7);
        clearStr(opcode, 5);
        clearStr(oper1, MAX_LABEL_SIZE);
        clearStr(oper2, MAX_LABEL_SIZE);
        i = 0;
        bit = str;
        foundLabel=FALSE;

        /*checking for comment */
        if (*bit == COMMENT || *bit == '\n' || *bit == '\0')
        {
            /*IC--;*/
            continue; /*skiiiiip*/
        }

        /*checking for a label*/
        while (isLetter(bit) == TRUE&&foundLabel==FALSE)
        {
            if (*bit == LABEL_END)
            {
                label[i] = '\0';
                foundLabel = TRUE; /*will be used later*/
                bit++;
                continue;
            }
            label[i] = *bit;
            i++;
            bit++;
        }

        if (foundLabel == FALSE)
        {
            bit = str;                       /*reseting point*/
            clearStr(label, MAX_LABEL_SIZE); /*clearing label*/
        }

        /*jumping for the next word*/
        /*checking for symbols first*/
        while (isLetter(bit) == FALSE)
            bit++;

        i = 0;
        if (*bit == symbolMarker) /*we met a sybol!*/
        {
            continue; /*we skip those, we collected them all*/
        }

        /* instruction label: opcode source-operand, target-operand
        label: opcode target-operand
        label: opcode*/

        spaceCount = countSpace(str);
        strcpy(temp, str);
        pch = strtok(temp, delimints); /*start strtok*/

        if (foundLabel == TRUE) /*skipping labels*/
        {
            pch = strtok(NULL, delimints);
            spaceCount--;
        }

        switch (spaceCount)
        {
        case 0: /*opcode*/
            break;

        case 1: /*opcode oper1*/
            strcpy(opcode, pch);
            op_code_type = stringToOperatorType(opcode);
            pch = strtok(NULL, delimints);
            strcpy(oper1, pch);
            break;

        case 2:
            /*opcode oper1, oper 2*/
            strcpy(opcode, pch);
            op_code_type = stringToOperatorType(opcode);
            pch = strtok(NULL, delimints);
            strcpy(oper1, pch);
            oper1[strlen(oper1) - 1] = '\0'; /*skipping the ,*/
            pch = strtok(NULL, delimints);
            strcpy(oper2, pch);
            oper2[strlen(oper2) - 1] = '\0';
            break;
        }

        /*keep an eye open for jmp jsr and bne NEED TO FIX STILL*/
        if (op_code_type == JMP || op_code_type == JSR || op_code_type == BNE)
            spaceCount = breakDownJumps(oper1, oper2, label);

        /*now we have the opcode, the two operators and the label if any,*/

        if (op_code_type == ERROR_NA) /*if opcode a real opcode*/
        {                             /*if opcode a real opcode*/
            fprintf(stdout, "opcode %s not found\n", opcode);
            foundErr = TRUE;
        }

        if (stringToOperatorType(oper1) != ERROR_NA || stringToOperatorType(oper1) != ERROR_NA) /*if any operator is a name of an opecode*/
        {                                                                                       /*if any operator is a name of an opecode*/
            fprintf(stdout, "operator src %s not found\n", oper1);
            foundErr = TRUE;
        }

        if (stringToOperatorType(oper2) != ERROR_NA || stringToOperatorType(oper2) != ERROR_NA) /*if any operator is a name of an opecode*/
        {                                                                                       /*if any operator is a name of an opecode*/
            fprintf(stdout, "operator src %s not found\n", oper2);
            foundErr = TRUE;
        }

        dumpFullInstruction(label, opcode, oper1, oper2, spaceCount, &IC, EXECUTION, op_table, dataHeader, binaryFileNode->file);
    }
    dumpSymbolsToMainFile(dataHeader, IC, binaryFileNode->file);

    if (!foundErr)
    {
        dumpSymbols(dataHeader, fileName, ENTRY, ".ent");
        dumpSymbols(dataHeader, fileName, EXTERN, ".ext");
        dumpSymbols(dataHeader, fileName, DATA, ".dat");
    }
    /*second pass*/
    freeSyList(dataHeader);
    deleteOperatorsTable(op_table);
    return binaryFileNode; /*tochange*/
}