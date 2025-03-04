#include <stdio.h>
#include <math.h>

double f(double x) {
  return sin(x);
}

double demander_nombre(void)
{
  double res = 0;
  printf("Entrez un nombre réel : ");
  scanf("%lf", &res);
  return res;
}

double integre(double a, double b)
{
  double res =
       41.0 * ( f(a) + f(b) )
    + 216.0 * ( f((5*a+b)/6.0) + f((5*b+a)/6.0) )
    +  27.0 * ( f((2*a+b)/3.0) + f((2*b+a)/3.0) )
    + 272.0 * f((a+b)/2.0) ;

  res *= (b-a)/840.0;

  return res;
}


int main(void)
{
  double
    a = demander_nombre(),
    b = demander_nombre();
  printf("Integrale de sin(x) entre %f et %f : %.12f\n", a, b, integre(a, b));
  return 0;
}
