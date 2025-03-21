#ifndef MACROLISTFUNCS_H
#define MACROLISTFUNCS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "struct.h"

MacroList *addMacroToList(MacroList *, char *, char **);

void constMacroList(MacroList **);

void freeMacroList(MacroList *);

void freeMacro(char **, int);

void addLineToNode(MacroList *, char *);

int dumpIfexistsInMacro(MacroList *, double, FILE *);

#endif