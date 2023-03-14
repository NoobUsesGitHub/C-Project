/* strtok example */
#include <stdio.h>
#include <string.h>

int main()
{
  FILE *f = fopen("test", "r");
  if (f == NULL)
  {
    printf("wtf");
    return 1;
  }

  /*char str[] ="mcr aaaaa This     a\tsample\tstring endmcr /o hjdfhasfhashfhash fsafasasfas f asfa sfa s aaaaa /o";*/
  char *pch;
  /*printf ("Splitting string \"%s\" into tokens:\n",str);*/
  int i = 0;
  int skp = 0;
  char *str[85];
  while (fgets(str, 85, f))
  {
    pch = strtok(str, "    \t \f \r");
    i = 0;
    while (pch != NULL)
    {
      if (i == 0)
      {
        if (pch[0] == ';')
        {
          printf("first note is ; %c\n", pch[0]);
          skp = 1;
        }
      }

      if (strcmp(pch, "mcr") == 0)
      {
        printf("mcr started");
        skp = 1;
      }

      if (strcmp(pch, "endmcr") == 0)
      {
        printf("mcr ended");
        skp = 1;
      }

      if (skp == 0)
        printf("%s\n", pch);

      pch = strtok(NULL, "    \t \f \r");
      i++;
      skp = 0;
    }
  }
  return 0;
}