#include <stdio.h>
#include <string.h>
/*#include <macroDecoder.c>*/
#include "struct.h"


int main(int argc, char *argv[])
{
    int i=0;
    FileList macroNode,tempNode,inputFilesHead,macroFilesHead;
    macroNode=helpers.nuller(macroNode);
    tempNode=helpers.nuller(tempNode);
    inputFilesHead=helpers.nuller(inputFilesHead);
    macroFilesHead=helpers.nuller(macroFilesHead);
    
    if(argc<=1)
    {
        printf("please input file names");
        return 1; 
    }
    inputFilesHead=stringToFiles(argc,argv);
    /*
    tempNode=inputFilesHead;
    macroFilesHead=macroNode;
    for (i=1;i<argc-1;i++)
    {
        macroNode=macroDecoder(tempNode.file);
        if(macroNode.file==NULL)/**assuming that the Macro decoder has found some error and finished early, after printing them
        {
            return 1;
        }
        tempNode=*tempNode.next;
        macroNode=*macroNode.next;
    }
    */
    helpers.closeFileList(inputFilesHead);
    //get input

    //open file
    //parse it 
    //pre process
    //start parsing it to binary/././././../././
    //push back to file
    return 1;
}

