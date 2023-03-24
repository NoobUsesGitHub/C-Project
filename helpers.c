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
        str[i] = ' ';
    }
}

/*
    input: a pointer to a char
    output: false if it is a space character, otherwise true
*/
bool isLetter(char *bit)
{
    char c = *bit;
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
        if (*str == ',')
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
        if (*str == ' ')
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
            if (i > 0 && str[i] == ',' && isspace(str[j - 1]))
            {
                str[j - 1] = str[i];
                continue;
            }
            str[j] = str[i];
            j++;
        }
        else if (i > 0 && isspace(str[i - 1]) == 0)
        {
            str[j] = ' ';
            j++;
        }
    }
    if (str[j - 1] == ' ' || str[j - 1] == '\t')
        j--;
    str[j] = '\0';
}

/*input: an opcode, and the line number
will print it if it is a real opcode*/
void dumpOpCode(char *pch, int IC)
{
    int opcode=realOpCode(pch);
    if ( opcode>-1)
    {
        printf("%d  %s", IC, opcodeToBinary(pch));
    }
    else
    {
        printf("not a real opcode!!!");
    }
}


void initHashTable(HashTable* table[])
{
    /*make not trash*/
    int size=OPCODE_NUMBER,i=0;
    char *cmdArray[]={"mov", "cmp", "add", "sub", "not", "clr", "lea", "inc", "dec", "jmp", "bne", "red", "prn", "jsr", "rts", "stop"};
    int operAmount[]={2    ,   2  ,   2  ,    2 ,   1  ,   1  ,   2  ,   1  ,   1  ,   1  ,   1  ,   1  ,   1  ,   1  ,   0  ,   0 };
    table=calloc(size,sizeof(HashTable));
    for(;i<size;i++)
    {
        *table[i]->hash=hasher(*cmdArray[i]);
        strcpy(*table[i]->key,*cmdArray[i]);
        table[i]->place=i;        
        table[i]->numberOfOper=operAmount[i];
    }

}

int realOpCode(char *pch,HashTable table[])
{
    double hash=hasher(pch);
    int place=-1;
    int i=0;
    for(;i<OPCODE_NUMBER;i++)
    {
        if(table[i].hash==hash)
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
    while(dataHeader->next!=NULL)
    {
        if(dataHeader->type==DATA)
            dataHeader->line=dataHeader->line+IC;
        dataHeader++;
    }
}

int numOfOpers(int opcode,HashTable *table)
{
    int i=0;
    for(;i<OPCODE_NUMBER;i++)
        if(opcode==*table[i].place)
            return *table[i].numberOfOper;
    return 0;
}

char* opcodeToBinary(char *pch)
{



    return "\0";
}