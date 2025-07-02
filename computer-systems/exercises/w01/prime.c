#include <math.h>
#include <stdio.h>
#include <stdbool.h>

const double g = 9.81;

int main()
{
    int n = 0;
    printf("Entrez n:");
    scanf("%d", &n);
    bool isPrime = true;

    if (n % 2 == 0) {
        isPrime = false;
        printf("The number is not prime, because it is divisible by 2");
    } else {
        for (int a = 3; a <= sqrt(n); a++) {
            if (n % a == 0) {
                printf("The number is not prime, because it is divisible by %d", a);
                isPrime = false;
            }
        }
    }

    if (isPrime) {
        printf("I strongly believe that this number is prime");
    }

    return 0;
}
