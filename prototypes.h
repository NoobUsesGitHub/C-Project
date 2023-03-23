#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "struct.h"

/*fileListFuncs*/
void constNode(FileList**);

void addToList(FileList*, FILE*, char*);

void closeFileList(FileList*);

void stringToFiles(int, char **, FileList**);

/*MacroListFuncs*/
void constMacroList(MacroList**);

void freeList(MacroList*);

void freeMacro(char **, int);

void addLineToNode(MacroList*, char*);

int dumpIfexistsInMacro(MacroList*, double,FILE*);

MacroList* addMacroToList(MacroList*, char*, char**);

void constMacroList(MacroList**);


/*SymbolListFuncs*/
int checkSymbolType(char*);

Symbol *addSymbolToList(Symbol *header, char *name, Stype type, int line)

/*helpers*/
double hasher(char*);

void clearStr(char*,int);

void printList(char**, int , FILE*);

bool isLetter(char*);

int dataLength(char*);

/*macro decoder*/
FileList* macroDecoder(FILE*, char*);

/*binaryMaker*/
FileList* toBinary(FILE*, char*);

/*outputMaker*/
FileList* toOutput(FILE*, char*);
char binaryTranslate(char);
