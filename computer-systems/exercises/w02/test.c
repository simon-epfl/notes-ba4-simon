#include <stdio.h>
#include <string.h>

void f(char* string)
{
  const size_t len = strlen(string);
  if (len >= 2) string[1] = 'e';
  if (len >= 6) string[5] = '\0';
  puts(string);
}

int main(void) 
{
  f("Hallo world!");
  return 0;
}