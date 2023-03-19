#include <stdio.h>
#include <string.h>
#include "prototypes.h"

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

