#ifndef OUTPUTMAKER_H
#define OUTPUTMAKER_H
#include <stdio.h>
#include <string.h>
#include "helpers.h"

#define coment ';'
#define delimints "    \t \f \r"
/*outputMaker*/
FileList* toOutput(FILE*, char*);

char binaryTranslate(char);
#endif