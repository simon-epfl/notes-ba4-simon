#include <stdio.h>

void f(double* ptr) 
{ 
  double a = 1.2; 
  ptr = &a; 
}     
   
int main(void) 
{ 
  double x = 9.8;
  double* p = &x; 
  f(p); 
  printf("%f\n", *p); 
  return 0; 
}
