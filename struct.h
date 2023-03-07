#include <stdio.h>
struct FileList
{
    FILE* file;
    struct FileList* next;
};
typedef struct FileList FileList;