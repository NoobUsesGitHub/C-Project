#include <stdio.h>
#define MAXLINESIZE 81
#define coment ';'
#define suggest '.' /* hanhaya- direction? idk*/
#define delimints "    \t \f \r"

typedef struct FileList
{
    FILE* file;
    char* fileName;
    struct FileList* next;
}FileList;

typedef struct MacroList
{
    char* macroName;
    double hash;
    char** macro;
    int size;
    struct MacroList* next;
}MacroList;

typedef struct Symbol
{
    char* name;
    double hash;
    int size;
    int line;
    struct Symbol* next;
}Symbol;

typedef enum bool{TRUE=1, FALSE= 0}bool; 