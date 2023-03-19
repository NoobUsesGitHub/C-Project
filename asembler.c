#include <stdio.h>
#include <string.h>
#include "struct.h"
#include "prototypes.h"

int main(int argc, char *argv[])
{
    int i=0;
    FileList *macroNode=NULL,*tempNode=NULL,*inputFilesHead=NULL,*macroFilesHead=NULL,*tempMacroNode=NULL;
    
    /*get input*/
    if(argc<=1)
    {
        printf("please input file names");
        return 1; 
    }
    
    stringToFiles(argc,argv,&inputFilesHead);
    
    tempNode=inputFilesHead;
    constNode(&macroFilesHead);
    constNode(&tempMacroNode);
    macroNode=macroFilesHead;
    for (i=1;i<=argc-1;i++)
    {
        tempMacroNode=macroDecoder(tempNode->file,tempNode->fileName);
        addToList(macroNode,tempMacroNode->file,tempMacroNode->fileName);
        if(macroNode->file==NULL)/*assuming that the Macro decoder has found some error and finished early, after printing them*/
        {
            return 1;
        }
        tempNode=tempNode->next;/*going forward with the list*/
    }
    closeFileList(inputFilesHead);/*to do- check this really cleans the whole file list*/
    closeFileList(tempMacroNode);
    /*//open file
    //parse it 
    //pre process
    //start parsing it to binary/././././../././
    /push back to file*/
    return 1;
}

