#include<stdio.h>
#include<string.h>

int main(void)
{
    char *str_array[64] = {};
    char str[128] = "_services._dns-sd._udp.local||_http._tcp.local||RICOH Aficio MP C3001 [0026733B6314]._http._tcp.local";

    char *p;
    char *strtok_data;
    int index = 0;
    str_array[index] = strtok_r(str, "||", &strtok_data);
    while (str_array[index] != NULL) {
        printf("str_array[%d]: %s\n", index, str_array[index]);

        index ++;
        str_array[index] = strtok_r(NULL, "||", &strtok_data);
    }
    return 0;
}
