#ifndef MACRODECODER_H
#define MACRODECODER_H

#include <stdio.h>
#include <string.h>
#include "struct.h"

FileList* macroDecoder(FILE*, char*);

int massIsSpace(char*);
#endif // MACRODECODER_H