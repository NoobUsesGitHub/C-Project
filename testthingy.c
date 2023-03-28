#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

void removeRedundantSpaces(char *str)
{
    int i = 0, j = 0, len = strlen(str);
    char temp[len*2];
    while (i < len)
    {
        if (isspace(str[i]) != 0)
        { /*is space*/
            if ((j > 0) && isspace(temp[j - 1]) != 0)
                temp[j - 1] = str[i];
            else
            {
                temp[j] = str[i];
                j++;
            }
        }
        else
        {
            if (str[i] == ',' && isspace(temp[j - 1]) != 0)
            {
                j--;
            }
            temp[j] = str[i];
            j++;
            if (str[i] == ',')
            {
               temp[j] = ' ';
                j++;
            }
        }
        i++;
    }
    if (temp[j - 1] == ' ' || str[j - 1] == '\t')
        j--;
    temp[j] = '\0';
    strcpy(str, temp);
}	

int main()
{
char *s[24];
strcpy(s,"  111 222 ,555 8 8 8 9 ");
printf("%s\n",s);
removeRedundantSpaces(s);
printf("%sa\n",s);
  return 0;
}
