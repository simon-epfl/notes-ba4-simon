#include <stdio.h>
#include <string.h>

int main(void)
{

    FILE *sortie = NULL;
    sortie = fopen("ecriture.txt", "w");

    do
    {
        char name[10] = "";
        int age = -1;
        int res = 0;

        printf("Enter a name (CTRL+D to finish): ");
        fflush(stdout);

        fgets(name, 10, stdin);

        // if (fgets(name, 10, stdin) == NULL)
        // {
        //     break; // Si EOF est atteint, sortir de la boucle
        // }

        name[strcspn(name, "\n")] = '\0';

        do
        {
            printf("age: ");
            fflush(stdout);
            res = scanf("%d", &age);
            if (res != 1)
            {
                printf("Je vous ai demandé un nombre positif!, pas du charabia !\n");
            }
            /* vide le tampon d'entrée */
            while (!feof(stdin) && !ferror(stdin) && getc(stdin) != '\n')
                ;
        } while (!feof(stdin) && !ferror(stdin) && (res == 0 || age < 0));

        if(res == 1) {
            fprintf(sortie, "%-12s %d\n", name, age);
        }
    } while (!feof(stdin) && !ferror(stdin));

    fclose(sortie);

    return 0;
}
