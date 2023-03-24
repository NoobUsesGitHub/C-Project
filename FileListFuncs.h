#ifndef FILELISTFUNCS_H
#define FILELISTFUNCS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "struct_h"

void constNode(FileList**);

void addToList(FileList*, FILE*, char*);

void closeFileList(FileList*);

void stringToFiles(int, char **, FileList**);

#endif // FILELISTFUNCS_H