#include <stdio.h>
#include <time.h>

int main()
{
    time_t time_seconds          = time(NULL);
    time_t hours_before_seconds = time_seconds - 14400;

    struct tm now_time;
    struct tm cur_time;
    struct tm hours_before;
    localtime_r(&time_seconds, &now_time);
    localtime_r(&hours_before_seconds, &hours_before);
    localtime_r(&time_seconds, &cur_time);

    printf("%d-%d-%d %d:%d:%d\n", hours_before.tm_year + 1900, hours_before.tm_mon + 1,
            hours_before.tm_mday, hours_before.tm_hour, hours_before.tm_min, hours_before.tm_sec);

    printf("%d-%d-%d %d:%d:%d\n", cur_time.tm_year + 1900, cur_time.tm_mon + 1,
            cur_time.tm_mday, cur_time.tm_hour, cur_time.tm_min, cur_time.tm_sec);

    //printf("%d-%d-%d %d:%d:%d\n", now_time.tm_year + 1900, now_time.tm_mon + 1,
    //        now_time.tm_mday, now_time.tm_hour, now_time.tm_min, now_time.tm_sec);

}
