#include <stdio.h>
#include <string.h>
/*
▀█▀ ▄▀▄    ██▄ ██▀    █▀▄ ██▀ █   ██▀ ▀█▀ ██▀ █▀▄ 
 █  ▀▄▀    █▄█ █▄▄    █▄▀ █▄▄ █▄▄ █▄▄  █  █▄▄ █▄▀ 
 */
unsigned int perfect_hash(char* s) {
    unsigned int hash = 0;
    int len = strlen(s);
    
    if (len == 1) {
        hash = s[0] % 17;
    } else if (len == 2) {
        hash = (s[0] * 26 + s[1]) % 109;
    } else if (len == 3) {
        hash = (s[0] * 676 + s[1] * 26 + s[2]) % 1009;
    } else {
        printf("Error: String must have at most 3 characters.\n");
    }
    
    return hash;
}

int main() {
    char* s1 = "abc";
    char* s2 = "def";
    char* s3 = "ghi";
    char* s4 = "jklm";
    
    printf("%s hashes to %u\n", s1, perfect_hash(s1));
    printf("%s hashes to %u\n", s2, perfect_hash(s2));
    printf("%s hashes to %u\n", s3, perfect_hash(s3));
    printf("%s hashes to %u\n", s4, perfect_hash(s4));
    
    return 0;
}

