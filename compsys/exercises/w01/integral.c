#include <math.h>
#include <stdio.h>
#include <stdbool.h>

const double g = 9.81;
const int PI = 3.14;

int main()
{
    int a = ask("Enter a:");
    int b = ask("Enter b:");

    printf("%lu", integrate(a, b));

    return 0;
}

double f(double x)
{
    return pow(x, 2);
}

double integrate(double a, double b)
{
    return (b - a) / 840.0 *
           (41 * f(a) +
            216 * f((5 * a + b) / 6.0) +
            27 * f((2 * a + b) / 3.0) +
            272 * f((a + b) / 2.0) +
            27 * f((a + 2 * b) / 3.0) +
            216 * f((a + 5 * b) / 6.0) +
            41 * f(b));
}

int ask(char question[])
{

    int res = 0;
    printf(question);
    scanf("%d", &res);
}
