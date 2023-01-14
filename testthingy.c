#include <stdio.h>
#include <string.h>
#define SIZE 81

int main()
{
    FILE *fp1,*fp2;
    char line[SIZE];
    fp1=fopen("f1","r");
    fp2=fopen("f2","w");
    
    while(fgets(line, SIZE,fp1)!=NULL)
    {
        if(strcmp(line,"aaaa")!=0)
        {
            fputs(line,fp2);
        }
    }
    remove("f1");
    /*remove(file pointer) removes a file, 0 if worked*/
    fclose(fp2);

    return 1;
}


