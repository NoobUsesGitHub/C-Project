#ifndef HELPERS_H
#define HELPERS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "struct.h"

/*helpers*/
double hasher(char*);

void clearStr(char*,int);

void printList(char**, int , FILE*);

bool isLetter(char*);

int dataLength(char*);

#endif