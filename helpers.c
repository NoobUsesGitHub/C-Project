#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "prototypes.h"

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
        if (str[i] != ' ' && str[i] != '\t')
        {
            str[j] = str[i];
            j++;
        }
        else if (i > 0 && str[i - 1] != ' ' && str[i - 1] != '\t')
        {
            str[j] = ' ';
            j++;
        }
        else if (i > 0 && str[i] != ',' && str[i - 1] != ' ' && str[i - 1] != '\t')
        {
            str[j] = ',';
            j++;
        }
    }
    if(str[j-1]==' '||str[j-1]=='\t')
        j--;
    str[j] = '\0';
}