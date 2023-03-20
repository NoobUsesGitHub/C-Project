#include <stdio.h>
#include <string.h>
#include "prototypes.h"

#define coment ';'
#define delimints "    \t \f \r"
FileList* toOutput(FILE *fp, char *fileName)
{
  char c = ' ';
  char strNewName[strlen(fileName) + 1];
  bool sawTab = FALSE;
  /*nt lineNum = 0;*/
  char *change = "bin\0";

  FileList *outputFile;
  constNode(&outputFile);

  strcpy(strNewName, fileName);
  char *bit = strNewName + (strlen(strNewName) - 2);
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
  c = (char)fgetc(fp);
  while (c != EOF)
  {
    if (sawTab == TRUE)
    {
      if (c == '\n')
      {
        sawTab = FALSE;
      }
      else
      {
        c = binaryTranslate(c);
      }
      fputc(c,outputFile->file);
    }
    else
    {
      if (c == '\t')
        sawTab = TRUE;
      fputc(c,outputFile->file);
    }
    c = (char)fgetc(fp);
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
