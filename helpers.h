#ifndef HELPERS_H
#define HELPERS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "struct.h"

double hasher(char *);

void clearStr(char *, int);

void printList(char **, int, FILE *);

bool isLetter(char *);

int dataLength(char *);

char *opcodeToBinary(char*);

int realOpCode(char*,HashTable[]);

int countSpace(char*);

void removeRedundantSpaces(char *);

void dumpOpCode(char*, int);

void initHashTable(HashTable**);

void addToData(Symbol*, int);

int numOfOpers(int,HashTable*);

void dumpDataOpers(char*, int*);

void dumpStr(char*, int*);

void intToBinary(char*,int);

char*opcodeToBinary(char*);

#endif // HELPERS_H