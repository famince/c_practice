
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>

int main(int argc, char *argv[])
{
    char buffer[100];
    buffer[0] = 'a';
    buffer[1] = 'b';
    buffer[2] = 'c';
    buffer[3] = '\0';
    buffer[4] = 'd';
    buffer[5] = 'e';

    printf("%c\n", buffer[4]);
    printf("%c\n", buffer[5]);
    printf("%c\n", buffer[6]);
    printf("%s\n", buffer);
}
