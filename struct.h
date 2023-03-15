#include <stdio.h>
typedef struct FileList
{
    FILE* file;
    char* fileName;
    struct FileList* next;
}FileList;

typedef struct MacroList
{
    char* MacroName;
    char** macro;
    struct MacroList* next;
}MacroList;