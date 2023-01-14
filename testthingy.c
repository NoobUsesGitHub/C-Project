#include <stdio.h>
#include <string.h>


int main()
{
    FILE *fp;

    fp=fopen("f1","a");
    if(fp==NULL)
    {
        return 0;
    }
    putc('a',fp);
    fclose(fp);

    return 1;
}


