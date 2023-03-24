#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "helpers.h"

/*
input: a string that we want to hash
output: a double that is the encoded string
*/
double hasher(char *str)
{
    double size = strlen(str);
    double hash = 0;
    int i = 0;
    /*maybe change to while*/
    if (str[((int)size) - 1] == '\n')
        size--;
    while (str[i] != '\0')
    {
        if (str[i] != '\n')
            hash += ((int)(str[i])) / (size - i) * 7.0; /*hashing func- takes every letter and its place and calculates a key for it, adding them together*/
        i++;
    }
    return hash;
}

/*
    input: a string pointer
    will fill it with spaces
*/
void clearStr(char *str, int size)
{
    int i = size;
    while (i >= 0)
    {
        str[i] = spaceChar;
    }
}

/*
    input: a pointer to a char
    output: false if it is a space character, otherwise true
*/
bool isLetter(char *bit)
{
    return (*bit != '\n' && isspace(*bit) == 0) ? TRUE : FALSE;
}

/*
    input: a list of strings and their size
    will go through the list and print them
*/
void printList(char **str, int size, FILE *fp)
{

    while (size != 0)
    {
        fprintf(fp, "%s", *str);
        str++;
        size--;
    }
}

/*
    input: a string of .data's input
    output: the number of words it will take
*/
int dataLength(char *str)
{
    int i = 0;
    while (*str != '\n' && isLetter(str) == TRUE)
    {
        if (*str == comma)
            i++;
        str++;
    }
    return i + 1;
}

/*
    input: a string
    output: the number of spaces in it
*/
int countSpace(char *str)
{
    int i = 0;
    while (*str != '\n' && isLetter(str) == TRUE)
    {
        if (*str == spaceChar)
            i++;
        str++;
    }
    return i + 1;
}

void removeRedundantSpaces(char *str)
{
    int i, j, len;
    len = strlen(str); /*to change*/
    j = 0;
    for (i = 0; i < len; i++)
    {
        if (isspace(str[i]) == 0)
        {
            if (i > 0 && str[i] == comma && isspace(str[j - 1]))
            {
                str[j - 1] = str[i];
                continue;
            }
            str[j] = str[i];
            j++;
        }
        else if (i > 0 && isspace(str[i - 1]) == 0)
        {
            str[j] = spaceChar;
            j++;
        }
    }
    if (str[j - 1] == spaceChar || str[j - 1] == '\t')
        j--;
    str[j] = '\0';
}

/*input: an opcode, and the line number
will print it if it is a real opcode*/
void dumpOpCode(char *pch, int IC)
{
    int opcode = realOpCode(pch);
    if (opcode > -1)
    {
        printf("%d  %s", IC, opcodeToBinary(pch));
    }
    else
    {
        printf("not a real opcode!!!");
    }
}

void initHashTable(HashTable *table[])
{
    /*make not trash*/
    int size = OPCODENUMBER, i = 0;
    char *cmdArray[] = {"mov", "cmp", "add", "sub", "not", "clr", "lea", "inc", "dec", "jmp", "bne", "red", "prn", "jsr", "rts", "stop"};
    int operAmount[] = {2, 2, 2, 2, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 0, 0};
    table = calloc(size, sizeof(HashTable));
    for (; i < size; i++)
    {
        *table[i]->hash = hasher(*cmdArray[i]);
        strcpy(*table[i]->key, *cmdArray[i]);
        table[i]->place = i;
        table[i]->numberOfOper = operAmount[i];
    }
}

/*
    input: a string , the opcode hashtable
    output: the opcode's place in the table

*/
int realOpCode(char *pch, HashTable table[])
{
    double hash = hasher(pch);
    int place = -1;
    int i = 0;
    for (; i < OPCODENUMBER; i++)
    {
        if (table[i].hash == hash)
            return table[i].place;
    }
    return place;
}

/*
    input: the Symbol table, the final number of lines
    will add IC to all data lines (step 17)
*/
void addToData(Symbol *dataHeader, int IC)
{
    while (dataHeader->next != NULL)
    {
        if (dataHeader->type == DATA)
            dataHeader->line = dataHeader->line + IC;
        dataHeader++;
    }
}
/*
    input: opcode and the hashtable of opcodes
    output: the number of operators for that opcode
*/
int numOfOpers(int opcode, HashTable *table)
{
    int i = 0;
    for (; i < OPCODENUMBER; i++)
        if (opcode == *table[i].place)
            return *table[i].numberOfOper;
    return -1;
}

void dumpDataOpers(char *str, int *DC)
{
    int size = strlen(str);
    char temp[size];
    char binaryChar[14];
    int value, i = 0;
    while (*str != '\n')
    {
        /*will run on the string until i finish the number or meet "," */
        if (*str == comma)
        {
            value = atoi(temp);
            intToBinary(binaryChar, value);
            printf("%d  %s", *IC, binaryChar);
            *DC++;
            clearStr(temp, size);
        }
        else
        {
            temp[i] = *str;
            str++;
            i++;
        }
    }
    if (*temp != spaceChar)
    {

        value = atoi(temp);
        intToBinary(binaryChar, value);
        printf("%d  %s", *DC, binaryChar);
        *DC++;
        clearStr(temp, size);
        *DC++;
    }
}
}

char *opcodeToBinary(char *pch)
{

    return "\0";
}

void dumpStr(char *oper, int *DC)
{
    int size = strlen(oper);
    char binaryChar[14];
    int value;
    while (*oper != '\0')
    {
        value = (int)(*oper);
        intToBinary(binaryChar, value);
        printf("%d  %s", *DC, binaryChar);
        *IC++;
        oper++;
    }
    printf("%d  %s", *DC, binaryChar);
    *DC++;
}

void intToBinary(char *binaryChar, int value)
{
    /*make not shit*/
    int i;
    for (i = 13; i >= 0; i--)
    {
        binaryChar[i] = (value & 1) + '0';
        value >>= 1;
    }
    binaryChar[0] = (value < 0) ? '1' : '0';
    binaryChar[14] = '\0';
}