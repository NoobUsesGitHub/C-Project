#include <stdio.h>
#include <string.h>
#define SIZE 6

int main()
{
    int a=5;
    int *v;

    v=&a;
    *v=4;
    
    return 1;
}

