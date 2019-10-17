#include <time.h>
#include <stdio.h>

int main(void)
{
    time_t t;
    struct tm *t_start;

    t = time(NULL) - 2 - 2;
    t_start = localtime(&t);
    printf("the number of seconds since january 1, 1970 is %ld\n", t);
    printf("month/day:%d/%d,  time: %d/%d\n", t_start->tm_mon, t_start->tm_mday, t_start->tm_hour, t_start->tm_min);
    return 0;
}
