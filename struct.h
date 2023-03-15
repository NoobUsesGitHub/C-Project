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
    struct macroList* next;
}MacroList;