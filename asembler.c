#include <stdio.h>
#include <string.h>
#include "macroDecoder.c"
#include "helpers.c"

int main(int argc, char *argv[])
{
    int i=0;
    FileList *macroNode,*tempNode,*inputFilesHead,*macroFilesHead;
    /*constNode(&macroNode);
    constNode(&tempNode);*/
    /*constNode(&macroFilesHead);*/
    
    /*get input*/
    if(argc<=1)
    {
        printf("please input file names");
        return 1; 
    }
    
    stringToFiles(argc,argv,&inputFilesHead);
    
    tempNode=inputFilesHead;
    macroFilesHead=macroNode;
    for (i=1;i<=argc-1;i++)
    {
        macroDecoder(tempNode->file,macroNode);
        if(macroNode.file==NULL)/*assuming that the Macro decoder has found some error and finished early, after printing them*/
        {
            return 1;
        }
        if(tempNode->next!=NULL)
        {
            tempNode=tempNode->next;
            macroNode=macroNode->next;
        }
    }
    closeFileList(inputFilesHead);

    /*//open file
    //parse it 
    //pre process
    //start parsing it to binary/././././../././
    /push back to file*/
    return 1;
}

