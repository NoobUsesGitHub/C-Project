#include <stdio.h>
#include <string.h>
#include "helpers.h"
#include "outputMaker.h"
#include "FileListFuncs.h"

FileList *toOutput(FILE *fp, char *fileName)
{
  char c = ' ';
  char *change = "ob\0";
  char strNewName[strlen(fileName)];
  bool sawTab = FALSE;

  FileList *outputFile;
  constNode(&outputFile);

  strcpy(strNewName, fileName);
  strcpyBySteps(strNewName+(strlen(strNewName)-strlen(change)),change,3);
  outputFile->fileName = (char *)malloc(strlen(strNewName) * sizeof(char));
  strcpy(outputFile->fileName, strNewName);

  outputFile->file = fopen(strNewName, "w");
  if (fp == NULL || outputFile->file == NULL)
  {
    outputFile->file = NULL;
    fprintf(stdout, "%s: couldn't create output file",fileName);
    return outputFile;
  }
  c = (char)fgetc(fp);
  
/* skipping the first line*/
  while (c != '\n' && c != EOF)
  {
    fputc(c, outputFile->file);
    c = (char)fgetc(fp);
  }
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
      fputc(c, outputFile->file);
    }
    else
    {
      if (c == '\t')
        sawTab = TRUE;
      fputc(c, outputFile->file);
    }
    c = (char)fgetc(fp);
  }

  return outputFile;
}

/*
input: a char
output: if it's 0 . else if 1 /
*/
char binaryTranslate(char c)
{
  char output_char;
  if (c == '0')
    output_char = '.';
  else if (c == '1')
    output_char = '/';
  return output_char;
}
