/* strtok example */
#include <stdio.h>
#include <string.h>

#define coment ';'

int main()
{
  FILE *f = fopen("test", "r");
  if (f == NULL)
  {
    printf("wtf");
    return 1;
  }
  int i = 0;
  int skp = 0;
  char * pch;
  char bit=' ';

  char *str[85];
  while (fgets(str, 85, f)!=NULL)
  {
    sscanf(str,"%c",&bit);
    if ((int)bit == ((int)coment))
      skp = 1;

    pch = strtok(str, "    \t \f \r");
    while ((pch != NULL)&&(skp!=1))
    {
      if (strcmp(pch, "mcr") == 0)
      {
        printf("mcr started");
        skp = 1;
      }
      if (strcmp(pch, "endmcr") == 0 || strcmp(pch, "endmcr\n") == 0)
      {
        printf("mcr ended\n");
        skp = 1;
      }
      if (skp == 0)
        printf("%s\n", pch);

      pch = strtok(NULL, "    \t \f \r");
    }
    
      skp = 0;
  }
  return 0;
}