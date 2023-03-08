#include <stdio.h>
#include <string.h>
#include <macroDecoder.c>
#include "helpers.c"

int main(int argc, char *argv[])
{
    int i=0;
    FileList macroNode,tempNode,inputFilesHead,macroFilesHead;
    macroNode=nuller(&macroNode);
    tempNode=nuller(&tempNode);
    inputFilesHead=nuller(&inputFilesHead);
    macroFilesHead=nuller(&macroFilesHead);
    if(argc<=1)
    {
        printf("please input file names");
        return 1; 
    }
    
    inputFilesHead=stringToFiles(argc,argv);
    printf("problem here2");
    
    tempNode=inputFilesHead;
    macroFilesHead=macroNode;
    for (i=1;i<=argc-1;i++)
    {
        macroNode=macroDecoder(tempNode.file);
        if(macroNode.file==NULL)assuming that the Macro decoder has found some error and finished early, after printing them
        {
            return 1;
        }
        tempNode=*tempNode.next;
        macroNode=*macroNode.next;
    }
    closeFileList(&inputFilesHead);
    printf("problem here3");
    /*get input

    //open file
    //parse it 
    //pre process
    //start parsing it to binary/././././../././
    /push back to file*/
    return 1;
}

