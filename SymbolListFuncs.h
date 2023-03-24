#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "helpers.h"

/*SymbolListFuncs*/
int checkSymbolType(char*);

Symbol *addSymbolToList(Symbol *header, char *name, Stype type, int line)
