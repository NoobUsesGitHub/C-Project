#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

int main()
{
	char str[4];
	strcpy(str,"mov");
	printf("%d",isspace(str));
  return 0;
}
