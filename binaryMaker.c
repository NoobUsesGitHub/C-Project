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

    int IC = -1, DC = 0, wordCount = 0, spaceCount = 0, i = 0; /*wordCount=L*/
    Stype stype = 0;
    bool skp = FALSE, foundSymbol = FALSE, foundErr = FALSE, foundLabel = FALSE;
    char *bit = NULL, label[MAX_LABEL_SIZE], dataTester[7], opcode[5], oper1[MAX_LABEL_SIZE], oper2[MAX_LABEL_SIZE], *pch = NULL, str[MAX_LINE_SIZE];
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
        fprintf(stderr, "File is not correct"); /*need to print out to STDOUT and say which line*/
        return binaryFileNode;
    }

    while (fgets(str, MAX_LINE_SIZE, fp) != NULL) /*first pass*/
    {
        removeRedundantSpaces(str);
        IC++;
        clearStr(label, MAX_LABEL_SIZE); /*clearing label*/
        clearStr(dataTester, 7);
        clearStr(opcode, 5);
        clearStr(oper1, MAX_LABEL_SIZE);
        clearStr(oper2, MAX_LABEL_SIZE);
        i = 0;
        bit = str;

        /*checking for comment */
        if (*bit == COMMENT || *bit == '\n')
            continue; /*skiiiiip*/

        /*checking for a label*/
        while (isLetter(bit) == TRUE)
        {
            if (*bit == LABEL_END)
            {
                label[i] = '\0';
                foundLabel = TRUE; /*will be used later*/
            }
            label[i] = *bit;
            i++;
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
                printf("label %s is a register or opcode!", label);
                foundErr = TRUE;
            }
        }

        /*jumping for the next word*/
        /*checking for symbols first*/
        while (isLetter(bit) == FALSE)
            bit++;
        if (*bit == '\0' || *bit != '\n')
        {
            fprintf(stderr, "line %d eneded unexpectandly", IC);
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
            while (isLetter(bit) == TRUE)
                bit++;

            if (*bit == '\0' || *bit != '\n')
            {
                fprintf(stderr, "line %d eneded unexpectandly", IC);
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
                        fprintf(stderr, "string finished with no end");
                        foundErr = TRUE;
                        break;
                    }
                    oper1[i] = *bit;
                    i++;
                    bit++;
                }
                bit++;
                oper1[i] = '\0';

                dumpStr(oper1, &IC, SIMULATION);

                if (foundLabel == FALSE)
                {
                    clearStr(label, MAX_LABEL_SIZE);
                    sprintf(label, "X DC: %d", DC); /*adding a dummy name*/
                }
                dataNode = addSymbolToList(dataHeader, label, stype, DC);
                DC = DC + strlen(oper1) + 1;
                break;
            case EXTERN:
            case ENTRY:
                clearStr(label, MAX_LABEL_SIZE);
                /*collecting label, we ignore the first label*/
                while (isLetter(bit) == TRUE)
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

                dataNode = addSymbolToList(dataHeader, label, stype, DC);
                dumpDataOpers(oper1, &DC, SIMULATION); /*maybe not?*/
                break;
            }
            continue;
        }

        if (foundLabel == TRUE) /*if we have label, and still here, make it a code symbol*/
            dataNode = addSymbolToList(dataHeader, label, CODE, IC);

        /* instruction label: opcode source-operand, target-operand
        label: opcode target-operand
        label: opcode*/

        pch = strtok(str, delimints); /*start strtok*/
        spaceCount = countSpace(str);
        if (foundLabel == TRUE) /*skipping labels*/
        {
            pch = strtok(NULL, delimints);
            spaceCount--;
        }
        if (spaceCount > 2)
        {
            fprintf(stderr, "operator %s was found with too many operands", opcode);
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
            break;
        }

        /*keep an eye open for jmp jsr and bne NEED TO FIX STILL*/
        if (op_code_type == JMP || op_code_type == JSR || op_code_type == BNE)
            spaceCount = breakDownJumps(oper1, oper2, label);

        /*now we have the opcode, the two operators and the label if any,*/

        if (op_code_type == ERROR_NA)
        { /*if opcode a real opcode*/
            fprintf(stderr, "opcode %s not found",opcode);
            foundErr = TRUE;
        }

        if (stringToOperatorType(oper1) != ERROR_NA || stringToOperatorType(oper1) != ERROR_NA)
        { /*if any operator is a name of an opecode*/
            fprintf(stderr, "operator src %s not found",oper1);
            foundErr = TRUE;
        }

        dumpFullInstruction(label, opcode, oper1, oper2, spaceCount, &IC, SIMULATION, op_table);
    }
    if (foundErr == TRUE) /*to do - implement finding errors*/
    {
        fprintf(stderr, "there are error's in the first pass!");
    }
    else
    {
        addToData(dataHeader, IC);
    }
    rewind(fp);
    IC = 0;

    while (fgets(str, MAX_LINE_SIZE, fp) != NULL) /*second pass*/
    {
        removeRedundantSpaces(str);
        IC++;
        clearStr(label, MAX_LABEL_SIZE); /*clearing label*/
        clearStr(dataTester, 7);
        clearStr(opcode, 5);
        clearStr(oper1, MAX_LABEL_SIZE);
        clearStr(oper2, MAX_LABEL_SIZE);
        i = 0;
        bit = str;

        /*checking for comment */
        if (*bit == COMMENT || *bit == '\n')
            continue; /*skiiiiip*/

        /*checking for a label*/
        while (isLetter(bit) == TRUE)
        {
            if (*bit == LABEL_END)
            {
                label[i] = '\0';
                foundLabel = TRUE; /*will be used later*/
            }
            label[i] = *bit;
            i++;
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

        pch = strtok(str, delimints); /*start strtok*/
        spaceCount = countSpace(str);
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
            break;
        }

        /*keep an eye open for jmp jsr and bne NEED TO FIX STILL*/
        if (op_code_type == JMP || op_code_type == JSR || op_code_type == BNE)
            spaceCount = breakDownJumps(oper1, oper2, label);

        /*now we have the opcode, the two operators and the label if any,*/

        if (op_code_type == ERROR_NA) /*if opcode a real opcode*/
             { /*if opcode a real opcode*/
            fprintf(stderr, "opcode %s not found",opcode);
            foundErr = TRUE;
        }

        if (stringToOperatorType(oper1) != ERROR_NA || stringToOperatorType(oper1) != ERROR_NA) /*if any operator is a name of an opecode*/
            { /*if any operator is a name of an opecode*/
            fprintf(stderr, "operator src %s not found",oper1);
            foundErr = TRUE;
        }

        dumpFullInstruction(label, opcode, oper1, oper2, spaceCount, &IC, EXECUTION, op_table);
    }
    /*to do, dump correctly the symbols*/
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