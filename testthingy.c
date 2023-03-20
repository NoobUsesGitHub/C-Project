#include <stdio.h>
#include <string.h>
#include "prototypes.h"

#define coment ';'
#define delimints "    \t \f \r"

FileList *toOutput(FILE *fp, char *fileName)
{
  char c;
  char strNewName[strlen(fileName) + 1];
  bool sawTab=FALSE;
  /*nt lineNum = 0;*/
  char *change = "bin\0";

  FileList *outputFile;
  constNode(&outputFile);

  strcpy(strNewName, fileName);
  char *bit = strNewName + (strlen(strNewName) - 2);
  printf("%c", *change);
  printf("%c", *bit);
  while (*change != '\0')
  {
    *bit = *change;
    bit++;
    change++;
  }
  *bit = '\0';
  outputFile->fileName = (char *)malloc(strlen(strNewName) * sizeof(char));
  strcpy(outputFile->fileName, strNewName);

  outputFile->file = fopen(strNewName, "w");
  if (fp == NULL || outputFile->file == NULL)
  {
    outputFile->file = NULL;
    printf("File is not correct");
    return outputFile;
  }

  while (c = fgetc(outputFile->file) != EOF)
  {
    if (sawTab == TRUE)
    {
      if (c == '\n')
      {
        sawTab = FALSE;
      }
      else
      {
       c=binaryTranslate(c);
      }
      fputc(outputFile->file, c);
    }else
    {
      if(c=='\t')
        sawTab=TRUE;
      fputc(outputFile->file, c);
    }
  }

  return outputFile; /*tochange*/
}

char binaryTranslate(char c)
{
    if (c == '0')
      c = '.';
    if (c == '1')
      c = '/';
  return c;
}

int main(int argc, char *argv[])
{
  int i = 0;
  FileList *tempNode = NULL, *outputFilesHead = NULL, *macroFilesHead = NULL, *tempMacroNode = NULL, *binaryFilesHead = NULL;

  /*get input*/
  if (argc <= 1)
  {
    printf("please input file names");
    return 1;
  }

  stringToFiles(argc, argv, &macroFilesHead);

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