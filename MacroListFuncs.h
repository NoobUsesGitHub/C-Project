#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "helpers.h"

/*MacroListFuncs*/
void constMacroList(MacroList**);

void freeList(MacroList*);

void freeMacro(char **, int);

void addLineToNode(MacroList*, char*);

int dumpIfexistsInMacro(MacroList*, double,FILE*);

MacroList* addMacroToList(MacroList*, char*, char**);

void constMacroList(MacroList**);

