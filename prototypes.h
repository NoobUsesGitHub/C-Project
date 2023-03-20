#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "struct.h"

/*helpers*/
void constNode(FileList**);

void addToList(FileList*, FILE*, char*);

void closeFileList(FileList*);

void stringToFiles(int, char **, FileList**);

void constMacroList(MacroList**);

void freeList(MacroList*);

void freeMacro(char **, int);

void addLineToNode(MacroList*, char*);

void printList(char**, int,FILE*);

int dumpIfexistsInMacro(MacroList*, double,FILE*);

MacroList* addMacroToList(MacroList*, char*, char**);

double hasher(char*);

void constMacroList(MacroList**);

int isspace(char*);

/*macro decoder*/
FileList* macroDecoder(FILE*, char*);

/*binaryMaker*/
FileList* toBinary(FILE*, char*);

/*outputMaker*/
FileList* toOutput(FILE*, char*);
char binaryTranslate(char);
