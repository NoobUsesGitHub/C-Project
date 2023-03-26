#ifndef SYMBOLLISTFUNCS_H
#define SYMBOLLISTFUNCS_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "helpers.h"

/*SymbolListFuncs*/
Stype checkSymbolType(char*);

Symbol *addSymbolToList(Symbol *header, char *name, Stype type, int line);
void freeSyList(Symbol*);
#endif