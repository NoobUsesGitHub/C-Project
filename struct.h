#include <stdio.h>
typedef struct FileList
{
    FILE* file;
    struct FileList* next;
}FileList;