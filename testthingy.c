#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
void intToBinary(char *placeHolderString, int value)
{
    int i = 0, size = strlen(placeHolderString);
    for(i=0;i<size;i++)
        if(value&(1<<(size-1-i)))
        {
            placeHolderString[i]='1';
        }else{
            placeHolderString[i]='0';
        }
    placeHolderString[size] = '\0';
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
