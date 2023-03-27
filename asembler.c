#include <stdio.h>
#include <string.h>
#include "helpers.h"
#include "outputMaker.h"
#include "binaryMaker.h"
#include "macroDecoder.h"

int main(int argc, char *argv[])
{
  int i = 0;
  FileList *tempInputNode = NULL;
  FileList *inputFilesHead = NULL;
  FileList *macroFilesHead = NULL;
  FileList *tempOutput = NULL;
  FileList *binaryFilesHead = NULL;
  FileList *outputFilesHead = NULL;

  /*get input*/
  int not_enough_args = (argc <= 1);
  if (not_enough_args)
  {
    fprintf(stderr, "Please input file names");
    return 1;
  }

  stringToFiles(argc, argv, &inputFilesHead);

  tempInputNode = inputFilesHead;
  constNode(&macroFilesHead);
  tempOutput = macroFilesHead;
  for (i = 1; i <= argc - 1; i++)
  {
    tempOutput = macroDecoder(tempInputNode->file, tempInputNode->fileName);
    if (tempOutput->file == NULL) /*assuming that the Macro decoder has found some error and finished early, after printing them*/
    {
      return 1;
    }
    addToList(macroFilesHead, tempOutput->file, tempOutput->fileName);
    tempInputNode = tempInputNode->next; /*going forward with the list*/
  }
  closeFileList(inputFilesHead);

  tempInputNode = macroFilesHead;
  constNode(&binaryFilesHead);
  tempOutput = binaryFilesHead;
  for (i = 1; i <= argc - 1; i++)
  {
    tempOutput = toBinary(tempInputNode->file, tempInputNode->fileName);
    if (tempOutput->file == NULL) /*assuming that the binary file maker has found some error and finished early, after printing them*/
    {
      return 1;
    }
    addToList(binaryFilesHead, tempOutput->file, tempOutput->fileName);
    tempInputNode = tempInputNode->next; /*going forward with the list*/
  }
  closeFileList(macroFilesHead);

  tempInputNode = macroFilesHead;
  constNode(&outputFilesHead);
  tempOutput = outputFilesHead;
  for (i = 1; i <= argc - 1; i++)
  {
    tempOutput = toOutput(tempInputNode->file, tempInputNode->fileName);
    if (tempOutput->file == NULL) /*assuming that the output maker has found some error and finished early, after printing them*/
    {
      return 1;
    }
    addToList(outputFilesHead, tempOutput->file, tempOutput->fileName);
    tempInputNode = tempInputNode->next; /*going forward with the list*/
  }
  closeFileList(outputFilesHead);
  return 1;
}
/*to do- valgrind*/
/*to do - add more error finding*/
/*to do - fix entry and external*/
/*to do - decide if extern and entry stay*/
/*to do - fix comments and such*/
/*to do - go through everything correctly*/
/*to do - make sure that we post correct file names*/
/*to do - make sure they print to file*/