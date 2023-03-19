#include <stdio.h>
#include <string.h>
#include "prototypes.h"

#define coment ';'
#define delimints "    \t \f \r"

FileList* toOutput(FILE *fp, char *fileName)
{
    char *str[MAXLINESIZE];
    char strNewName[strlen(fileName) + 1];
    int lineNum = 0;

    FileList *outputFile;
    constNode(&outputFile);

    strcpy(strNewName, fileName);
    strcpy(strNewName[strlen(strNewName) - 2], "bin");
    outputFile->fileName = (char *)malloc(strlen(strNewName) * sizeof(char));
    strcpy(outputFile->fileName, strNewName);

    outputFile->file = fopen(strNewName, "w");
    if (fp == NULL || outputFile->file == NULL)
    {
        outputFile->file = NULL;
        printf("File is not correct");
        return outputFile;
    }

    while (fscanf("%d %s", &lineNum, &str) != 2)
    {
        binaryTranslate(&str);
        fprintf(outputFile->file, "%d\t%s ",lineNum,str);
    }

    return outputFile; /*tochange*/
}

void binaryTranslate(char **str)
{
    char *bit=*str[0];
    while(*bit!='\0')
    {  
        if(bit=='0')bit='.';
        if(bit=='1')bit='/';
        bit++;
    }
}