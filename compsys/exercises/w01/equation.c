#include <math.h>
#include <stdio.h>
#include <stdbool.h>

const double g = 9.81;
const int PI = 3.14;

int main()
{

    int a0 = ask("Entrez a0:");
    int a1 = ask("Entrez a1:");
    int a2 = ask("Entrez a2:");

    double Q = ((3 * a1) - pow(a2, 2))/9;
    double R = (9 * a2 * a1 - 27 * a0 - 2 * pow(a2, 3))/(54);

    double D = pow(Q, 3) + pow(R, 2);

    double theta = acos(R/(sqrt(-pow(Q, 3))));

    if (D < 0) {
        double z1 = 2 * sqrt(-Q) * cos(theta/3) - 1/3 * a2;
        double z2 = 2 * sqrt(-Q) * cos((theta + 2 * PI)/3) - 1/3 * a2;
        double z3 = 2 * sqrt(-Q) * cos((theta + 4 * PI)/3) - 1/3 * a2;
        printf("Root 1: %lu, Root 2: %lu, Root 3: %lu", z1, z2, z3);
    } else {
        double S = pow((R + sqrt(D)), 1.0/3.0);
        double T = pow((R - sqrt(D)), 1.0/3.0);
    
        if (D == 0 && (S + T) != 0) {
            double z1 = -1/3 * a2 + (S + T);
            double z2 = -1/3 - 1/2 * (S + T);
            printf("Root 1: %lu, Root 2: %lu", z1, z2);
        } else {
            double z1 = -1/3 * a2 + (S + T);
            printf("Single root: %lu", z1);
        }
    }
}

int ask(char question[]) {

    int res = 0;
    printf(question);
    scanf("%d", &res);

}
