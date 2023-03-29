#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
void intToBinary(char *placeholderString, int value)
{
    int bufferSize = strlen(placeholderString);
    char temp[bufferSize];
    memset(temp,'0',sizeof(char)*bufferSize);

    int i = 0;
    i = bufferSize - 1;
    while (value != 0)
    {
       temp[i]=value & 1;
        value=value >> 1;
        i--;
    }

    i = 0; /*
     for (; i < bufferSize; i++)
     {
         temp[i] = placeholderString[bufferSize - i - 1];
     }
     temp[bufferSize]='\0';*/
     strcpy(placeholderString, temp);
 
}
int main()
{
    int x = 0;
    char s[5];
    strcpy(s, "0000\0");
    printf("%s\n", s);
    scanf("%d", &x);
    intToBinary(s, x);
    printf("%sa\n", s);
    return 0;
}
