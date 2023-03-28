#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

int main()
{
	unsigned i=1;
	i=i&0;
printf("%d",i);
i=1;
i=i&&0;
printf("%d",i);
  return 0;
}
