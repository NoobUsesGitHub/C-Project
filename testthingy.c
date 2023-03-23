#include <stdio.h>
#include <string.h>



void removeRedundantSpaces(char *str)
{
    int i, j, len;
    len = strlen(str); /*to change*/
    j = 0;
    for (i = 0; i < len; i++)
    {
        if (isspace(str[i])!=0)
        {
          if(i>0 &&str[i]==',' && isspace(str[i - 1]) !=0)
          {
            str[j-1]=',';
            continue;  
          }

            str[j] = str[i];
            j++;
        }
        else if (i > 0 &&isspace(str[i])!=0)
        {
            str[j] = ' ';
            j++;
        }
    }
    if(str[j-1]==' '||str[j-1]=='\t')
        j--;
    str[j] = '\0';
}

int main() {
    char str[100]="LABEL: OPCODE OPER1  , OPER2   ";
    
    removeRedundantSpaces(str);
    printf("Modified string: %s", str);
    return 0;
}
