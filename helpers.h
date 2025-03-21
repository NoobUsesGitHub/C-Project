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

void shiftLeftChar(char *, int);

void dumpDataOpers(char *, int *, int,FILE*);

void dumpStr(char *, int *,int,FILE*);

void intToBinary(char *, int);

char *opcodeToBinary(char *);

OperatorType stringToOperatorType(char*);

int getNumOfOperands(OperatorType, Operator*);

int realRegister(char*);

bool isAddTypeCorrect(OperatorType,int, int, Operator*,int);

bool existInAddressType(int, int[]);

bool dumpFullInstruction(char*,char*,char*,char*,int,int*,int,Operator*, Symbol *,FILE*);

int checkAddressType(char*, OperatorType, int, Symbol*);

void strcpyBySteps(char*, char*, int);

int breakDownJumps(char *, char *,char*);


int calculateOpcodeBinaryAndPrint(OperatorType , int , int, int, int *, Symbol *, char *,FILE*);

void calculateOperatorsBinaryAndPrint(char *, char *, int, int, int, int *, Symbol *,FILE*);

void checkIfExternal(char *, int, Symbol *);
int massIsSpace(char*);
#endif 