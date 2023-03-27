#ifndef SYMBOLLISTFUNCS_H
#define SYMBOLLISTFUNCS_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "helpers.h"

/*SymbolListFuncs*/
Stype checkSymbolType(char*);

Symbol *addSymbolToList(Symbol *, char *, Stype, int, char *);
void freeSyList(Symbol*);
#endif