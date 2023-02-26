#include <stdio.h>
#include <string.h>
struct FileList
{
    FILE* p;
    struct FileList* next;
};
typedef struct FileList FileList;

