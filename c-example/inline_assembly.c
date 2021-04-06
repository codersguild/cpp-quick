#include<stdio.h>

long long int func(long long int a, long long int b)
{
  long long int c = 0;

  __asm__ __volatile__ ("addl %%ebx, %%eax;"
                       : "=a"(c)
                       : "a"(a), "b"(b));
  return c;
}

int main() {

   long long int a = 1233251470, b = 5236952144, c = 0;

   c = func(a, b);

   printf("c = %lld", c);
}

