/* strtok example */
#include <stdio.h>
#include <string.h>

int main ()
{
  char str[] ="mcr aaaaa This     a\tsample\tstring endmcr aadsad";
  char * pch;
  printf ("Splitting string \"%s\" into tokens:\n",str);
  pch = strtok (str,"    \t \f \r");
  while (pch != NULL)
  {
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
  }
  return 0;
}