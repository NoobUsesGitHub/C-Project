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
    strNewName[strlen(strNewName) - 4]= "bin\0";
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

int main(int argc, char *argv[])
{
    int i=0;
    FileList *tempNode=NULL,*outputFilesHead=NULL,*macroFilesHead=NULL,*tempMacroNode=NULL,*binaryFilesHead=NULL;
    
    /*get input*/
    if(argc<=1)
    {
        printf("please input file names");
        return 1; 
    }
    
    stringToFiles(argc,argv,&macroFilesHead);

    tempNode=macroFilesHead;
    constNode(&outputFilesHead);
    tempMacroNode=outputFilesHead;
    for (i=1;i<=argc-1;i++)
    {
        tempMacroNode=toOutput(tempNode->file,tempNode->fileName);
        if(tempMacroNode->file==NULL)/*assuming that the Macro decoder has found some error and finished early, after printing them*/
        {
            return 1;
        }
        addToList(outputFilesHead,tempMacroNode->file,tempMacroNode->fileName);
        tempNode=tempNode->next;/*going forward with the list*/
    }
    closeFileList(outputFilesHead);

    return 1;
}