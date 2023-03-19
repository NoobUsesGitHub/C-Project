#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "struct.h"

/*helpers*/
void constNode(FileList**);

double hasher(char*);

MacroList* addMacroToList(MacroList*, char*, char**);

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