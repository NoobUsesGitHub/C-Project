#ifndef HELPERS_H
#define HELPERS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "struct.h"

Operator *createOperatorsTable();

void deleteOperatorsTable(Operator *);

double hasher(char *);

void clearStr(char *, int);

void printList(char **, int, FILE *);

bool isLetter(char *);

int dataLength(char *);

char *opcodeToBinary(char *);

int countSpace(char *);

void removeRedundantSpaces(char *);

void addToData(Symbol *, int);

void dumpDataOpers(char *, int *, int);

void dumpStr(char *, int *,int);

void intToBinary(char *, int);

char *opcodeToBinary(char *);

OperatorType stringToOperatorType(char*);

int getNumOfOperands(OperatorType, Operator*);

int realRegister(char*);

bool isAddTypeCorrect(OperatorType,int, int, Operator*);

bool existInAddressType(int, int[]);

void dumpFullInstruction(char*,char*,char*,char*,int,int*,int,Operator*);

#endif // HELPERS_H