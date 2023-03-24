#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "helpers.h"

/*fileListFuncs*/
void constNode(FileList**);

void addToList(FileList*, FILE*, char*);

void closeFileList(FileList*);

void stringToFiles(int, char **, FileList**);