#include <stdio.h>
#include <string.h>
#include <struct.h>
#include <macroDecoder.c>


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
    tempNode=inputFilesHead;
    macroFilesHead=macroNode;
    for (i=1;i<argc-1;i++)
    {
        macroNode.p=macroDecoder(tempNode.p);
        if(macroNode.p==NULL)/**assuming that the Macro decoder has found some error and finished early, after printing them**/
        {
            return 1;
        }
        tempNode=*tempNode.next;
        macroNode=*macroNode.next;
    }

    helper.closeFileList(inputFilesHead);
    //get input

    //open file
    //parse it 
    //pre process
    //start parsing it to binary/././././../././
    //push back to file
    return 1;
}

