#include <stdio.h>
 
int main ()
{
   /* 局部变量定义 */
   char grade = 'B';
   int level = 0;
 
   level = switch(grade)
   {
   case 'A' :
      printf("很棒！\n" );
      return 1;
      break;
   case 'B' :
   case 'C' :
      printf("做得好\n" );
      return 2;
      break;
   case 'D' :
      printf("您通过了\n" );
      return 3;
      break;
   case 'F' :
      printf("最好再试一下\n" );
      return 4;
      break;
   default :
      return -1;
      printf("无效的成绩\n" );
   }
   printf("您的成绩是 %c/%d\n", grade, level);
 
   return 0;
}
