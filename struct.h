#ifndef STRUCT_H
#define STRUCT_H

#include <stdio.h>
#define MAX_LINE_SIZE 81
#define MAX_LABEL_SIZE 31
#define BINARY_LINE_SIZE 15
#define OPERATORS_AMOUNT 16
#define SIMULATION 1
#define EXECUTION 0
#define LABEL_END ':'
#define COMMENT ';'
#define symbolMarker '.' /* hanhaya- direction?instruction?*/
#define stringMarker '"' /* "abcd"*/
#define delimints "    \t \f \r"
#define SPACE_CHAR ' '
#define COMMA ','

typedef enum OperatorType
{
    MOV = 0,
    CMP,
    ADD,
    SUB,
    NOT,
    CLR,
    LEA,
    INC,
    DEC,
    JMP,
    BNE,
    RED,
    PRN,
    JSR,
    RTS,
    STOP,
    ERROR_NA = -1
} OperatorType;

typedef struct Operator
{
    OperatorType type;
    int num_of_operands;
    /*shitot miun*/
    int src_addressing_methods[4];
    int dst_addressing_methods[4];
} Operator;

typedef struct FileList
{
    FILE *file;
    char *fileName;
    struct FileList *next;
} FileList;

typedef struct MacroList
{
    char *macroName;
    double hash;
    char **macro;
    int size;
    struct MacroList *next;
} MacroList;

typedef enum Stype
{
    CODE = 0,
    DATA = 1,
    EXTERN = 2,
    ENTRY = 3,
    STRING = 4
} Stype;

typedef struct Symbol
{
    char *name;
    double hash;
    Stype type;
    int line;
    Stype externalType;
    char *input;
    struct Symbol *next;
} Symbol;


typedef enum bool
{
    TRUE = 1,
    FALSE = 0
} bool;

#endif 