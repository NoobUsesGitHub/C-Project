#include <stdio.h>
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


typedef enum bool{TRUE=1, FALSE= 0}bool; 