#include <stdio.h>
#include <string.h>
#include "helpers.h"


int main(int argc, char *argv[])
{
    int i=0;
    FileList *tempNode=NULL,*inputFilesHead=NULL,*macroFilesHead=NULL,*tempMacroNode=NULL,*binaryFilesHead=NULL,*outputFilesHead=NULL;
    
    /*get input*/
    if(argc<=1)
    {
        printf("please input file names");
        return 1; 
    }
    
    stringToFiles(argc,argv,&inputFilesHead);
    
    tempNode=inputFilesHead;
    constNode(&macroFilesHead);
    tempMacroNode=macroFilesHead;
    for (i=1;i<=argc-1;i++)
    {
        tempMacroNode=macroDecoder(tempNode->file,tempNode->fileName);
        if(tempMacroNode->file==NULL)/*assuming that the Macro decoder has found some error and finished early, after printing them*/
        {
            return 1;
        }
        addToList(macroFilesHead,tempMacroNode->file,tempMacroNode->fileName);
        tempNode=tempNode->next;/*going forward with the list*/
    }
    closeFileList(inputFilesHead);/*to do- check this really cleans the whole file list*/
    
    
    tempNode=macroFilesHead;
    constNode(&binaryFilesHead);
    tempMacroNode=binaryFilesHead;
    for (i=1;i<=argc-1;i++)
    {
        tempMacroNode=toBinary(tempNode->file,tempNode->fileName);
        if(tempMacroNode->file==NULL)/*assuming that the Macro decoder has found some error and finished early, after printing them*/
        {
            return 1;
        }
        addToList(binaryFilesHead,tempMacroNode->file,tempMacroNode->fileName);
        tempNode=tempNode->next;/*going forward with the list*/
    }
    closeFileList(macroFilesHead);

   
  tempNode = macroFilesHead;
  constNode(&outputFilesHead);
  tempMacroNode = outputFilesHead;
  for (i = 1; i <= argc - 1; i++)
  {
    tempMacroNode = toOutput(tempNode->file, tempNode->fileName);
    if (tempMacroNode->file == NULL) /*assuming that the Macro decoder has found some error and finished early, after printing them*/
    {
      return 1;
    }
    addToList(outputFilesHead, tempMacroNode->file, tempMacroNode->fileName);
    tempNode = tempNode->next; /*going forward with the list*/
  }
  closeFileList(outputFilesHead);
    return 1;
}

