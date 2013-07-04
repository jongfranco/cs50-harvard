#include <stdio.h>
  #include <stdlib.h>
 #include <string.h>

  char* mystrdup(char* s)
  {
      int len = strlen(s);
     char* copy = malloc(len);
      for (int i = 0; i <= len; i++)
     {
         copy[i] = s[i];
     }
     return copy;
 }

 int main(void)
  {
      char* hello = mystrdup("hello");
     printf("%s, CS50x!\n", hello);
     return 0;

  }
