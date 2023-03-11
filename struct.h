#include <stdio.h>
typedef struct FileList
{
    FILE* file;
    char* fileName;
    struct FileList* next;
}FileList;