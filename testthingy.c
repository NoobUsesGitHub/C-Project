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
        
    /*check for;*/
        printf ("checking first note %c\n",pch[0]);

    }
    if(strcmp(pch,"mcr")==1)
    {
        printf("mcr started");
    }

    
    if(strcmp(pch,"endmcr")==1)
    {
        printf("mcr ended");
    }
    printf ("%s\n",pch);
    pch = strtok (NULL, " ,.-");
    i++;
  }
  return 0;
}