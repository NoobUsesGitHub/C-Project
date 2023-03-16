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
    char** macro;
    int size;
    struct macroList* next;
}MacroList;

typedef enum bool{TRUE=1, FALSE= 0}bool; 