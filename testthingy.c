/* strtok example */
#include <stdio.h>
#include <string.h>

int main ()
{
  char str[] ="This     a\tsample\tstring";
  char * pch;
  printf ("Splitting string \"%s\" into tokens:\n",str);
  pch = strtok (str,"    \t \f \r");
  while (pch != NULL)
  {
    printf ("%s\n",pch);
    pch = strtok (NULL, " ,.-");
  }
  return 0;
}