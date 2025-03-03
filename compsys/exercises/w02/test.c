#include <stdio.h>
#include <stdlib.h>

double* f(double a) 
{ 
  double b = a;
  return &b;
}     
   
int main(void) 
{ 
  double* ptr = f(9.0);
  printf("%f", *ptr);
  return 0; 
}
