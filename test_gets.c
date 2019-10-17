#include <stdio.h>
#include <string.h>
int main()
{
    char s1[100], s2[100];
    
    printf("输入第一个字符串: ");
    scanf("%s", s1);

    printf("输入第二个字符串: ");
    scanf("%s", s2);

    int len1 = strlen(s1);
    int len2 = strlen(s2);
    printf("%d %d", len1, len2);
s1[len1] = ' ';
    for (int i = 0; i <= len2; i++)
    {
        s1[i + 1 + len1] = s2[i];
    }

    printf("%s\n", s1);
    // system("pause");
    return 0;
}
