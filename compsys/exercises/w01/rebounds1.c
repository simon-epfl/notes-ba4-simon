#include <math.h>
#include <stdio.h>

const double g = 9.81;

int main()
{

    double h0 = 0.0;
    printf("Entrez h0:");
    scanf("%lf", &h0);

    double eps = 0.0;
    printf("Entrez eps:");
    scanf("%lf", &eps);

    int nbr = 0;
    printf("Entrez nbr:");
    scanf("%d", &nbr);

    double v = sqrt(2 * h0 * g);
    double v1 = 0.0;
    double h1 = 0.0;

    for (int current_nbr = 0; current_nbr < nbr; current_nbr = current_nbr + 1) {
        v1 = eps * v;
        h1 = pow(v1, 2)/(2 * g);
        v = sqrt(2 * h1 * g);
    }

    printf("At the %dth bounce, the height will be %lf m.", nbr, h1);

    return 0;
}
