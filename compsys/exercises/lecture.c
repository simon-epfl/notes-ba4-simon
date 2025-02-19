#include <math.h>
#include <stdio.h>
#include <stdbool.h>
#include <limits.h>

int main(void)
{

    FILE *entree = NULL;
    entree = fopen("ecriture.txt", "r");

    puts("+-----------------+-----+");

    // do {
    //     // reading the first line
        
    //     int currentValueIdx = 0;
    //     char currentValue[100];
    //     char currentChar = NULL;
    //     // reading the name
    //     do {
    //         currentChar = getc(entree);
    //         currentValue[currentValueIdx] = currentChar;
    //         currentValueIdx = currentValueIdx + 1;
    //     } while (currentChar != " ");

    //     currentValue = {0};
    //     // reading the name
    //     do {
    //         currentChar = getc(entree);
    //         currentValue[currentValueIdx] = currentChar;
    //         currentValueIdx = currentValueIdx + 1;
    //     } while (currentChar != " ");

    //     printf("| %-15s | %3s |\n", currentChar, "7s");
    // }

    int min = INT_MAX;
    int max = INT_MIN;

    while (!feof(entree)) {
        char nom[100];
        int age = 0.0;
        int lu = 0;
        // on ne met pas le & pour le nom car c'est déjà un pointeur !
        lu = fscanf(entree, "%12s %d", nom, &age);
        // ça renvoie le nb d'items lu
        if (lu == 2) {
            if (age < min) {
                min = age;
            }
            if (age > max) {
                max = age;
            }
            printf("| %-15s | %3d |\n", nom, age);
        }
    }

    puts("+-----------------+-----+\n");

    printf("Min: %d\n", min);
    printf("Max: %d\n", max);

    return 0;
}
