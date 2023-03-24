#ifndef STRUCT_H
#define STRUCT_H

#include <stdio.h>
#define MAXLINESIZE 81
#define MAXLABELSIZE 31
#define OPCODENUMBER 16
#define LABELEND ':'
#define comment ';'
#define comma ','
#define spaceChar ' '
#define symbolMarker '.' /* hanhaya- direction? idk*/
#define stringMarker '"' /* "abcd"*/
#define delimints "    \t \f \r"


typedef struct FileList
{
    FILE* file;
    char* fileName;
    struct FileList* next;
}FileList;

typedef struct MacroList
{
    char* macroName;
    double hash;
    char** macro;
    int size;
    struct MacroList* next;
}MacroList;

typedef struct Symbol
{
    char* name;
    double hash;
    Stype type;
    int line;
    struct Symbol* next;
}Symbol;

typedef enum Stype{CODE=0, DATA=1,EXTERN=2,ENTRY=3,STRING=4}Stype;

typedef struct HashTable {
    char *key;
    double hash;
    int place;
    int numberOfOper;
}HashTable;

typedef enum bool{TRUE=1, FALSE= 0}bool; 

#endif