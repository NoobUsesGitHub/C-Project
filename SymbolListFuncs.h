#ifndef SYMBOLLISTFUNCS_H
#define SYMBOLLISTFUNCS_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "helpers.h"
#include "struct.h"

/*SymbolListFuncs*/


void constSymbol(Symbol**);
void *addSymbolToList(Symbol *, char *, Stype, int, char *, Stype);
void freeSyList(Symbol *);
Stype checkSymbolType(char *);
int existInSymbolTable(char *, Symbol *, int);
Stype symbolTypeFromTable(char *, Symbol *);
int countSymbols(Symbol *);
void fillSymArr(Symbol *[], int, Symbol *);
int SymbolCompare(const void *, const void *);
void fixEntryPositions(Symbol *);
#endif