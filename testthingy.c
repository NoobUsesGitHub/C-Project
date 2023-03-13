/* strtok example */
#include <stdio.h>
#include <string.h>

int main ()
{
  char str[] ="mcr aaaaa This     a\tsample\tstring endmcr aadsad";
  char * pch;
  printf ("Splitting string \"%s\" into tokens:\n",str);
  pch = strtok (str,"    \t \f \r");
  int i=0;
  while (pch != NULL)
  {
    if(i==0)
    {
        
        if(pch[0]==';')
            printf ("first note is ; %c\n",pch[0]);

    }
    if(strcmp(pch,"mcr")==0)
    {
        printf("mcr started");
    }

    
    if(strcmp(pch,"endmcr")==0)
    {
        printf("mcr ended");
    }
    printf ("%s\n",pch);
    pch = strtok (NULL, " ,.-");
    i++;
  }
  return 0;
}