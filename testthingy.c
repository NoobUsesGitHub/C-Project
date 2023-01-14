#include <stdio.h>
#include <string.h>
#define SIZE 81

int main()
{
    FILE *fp1=NULL,*fp2=NULL;
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
    if(remove(fp1)==0)
        printf("0");
    /*remove(file pointer) removes a file, 0 if worked*/
    fclose(fp2);

    return 1;
}


