#include <stdio.h>
#include <math.h>
#include <stdlib.h>

double s(double x) {
  return sin(x);
}

double e(double x) {
    return exp(x);
}

double f1(double x) {
    return log10(x) + x;
}

double f2(double x) {
    return exp(sqrt(x));
}

double f3(double x) {
    return exp(sqrt(x + 8));
}

typedef double (*Function)(double);

int request_function() {
    printf("Please enter a number between 1-5: ");
    int res = 0;
    scanf("%d", &res);
    return res;
}

double demander_nombre(void)
{
  double res = 0;
  printf("Entrez un nombre réel : ");
  scanf("%lf", &res);
  return res;
}

double integre(double a, double b, Function f)
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

    Function* arr = calloc(2, sizeof(Function));
    arr[0] = f1;
    arr[1] = f2;

    double
        a = demander_nombre(),
        b = demander_nombre();
    printf("Integrale de f entre %f et %f : %.12f\n", a, b, integre(a, b, arr[request_function()]));
    return 0;
}