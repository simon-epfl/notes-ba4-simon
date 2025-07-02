#include <math.h>
#include <stdio.h>
#include <string.h>

#define start  32
#define stop  253
#define TAILLE 256 // 256 characters
typedef unsigned long int Statistique[TAILLE];

FILE *request_file(void);

FILE *request_file(void)
{

    FILE *entree = NULL;

    int idx = 0;

    do
    {
        printf("Entrez le nom du fichier:");
        char res[100];
        fflush(stdout);
        fgets(res, 100, stdin);
        res[strcspn(res, "\n")] = '\0';
        entree = fopen(res, "r");
        if (entree == NULL)
        {
            fprintf(stderr,
                    "Erreur: le fichier %s ne peut etre ouvert en lecture !\n",
                    res);
        }
        idx = idx + 1;
    } while (idx <= 3 && entree == NULL);

    return entree;
}

int main()
{
    FILE *file = request_file();

    return 0;
}

void initialise_statistique(Statistique stat)
{
    int i;
    for (i = 0; i < TAILLE; ++i)
    {
        stat[i] = 0;
    }
}

unsigned long int collecte_statistique(Statistique stat, FILE* f)
{
  int c;                    /* le caractère lu             */
  unsigned long int nb = 0; /* le nombre d'éléments comptés */

  while ((c = getc(f)) != EOF) {
    /* est-ce que le caractère lu est dans l'intervalle qu'on étudie ? */
    if (( ((unsigned char) c) >= start) &&
        ( ((unsigned char) c) <= stop ) ) {
      ++(stat[c - start]); /* on incrément la statistique pour ce caractère */
      ++nb; /* on incrémente le nombre total d'éléments comptés */
    }
  }

  return nb;
}

void affiche(Statistique stat, unsigned long int nb, unsigned short int taille)
{
  unsigned short int i;

  if (nb == 0) { /* on doit calculer la somme si nb == 0 */
    for (i = 0; i < taille; ++i)
      nb += stat[i];
  }
  
  printf("STATISTIQUES :\n");
  for (i = 0; i < taille; ++i) {
    /* on n'affiche que les résultats pour des statistiques supérieures à 0 */
    if (stat[i] != 0) {
      printf("%c : %10lu - %6.2f%%\n", (char) (i+start), stat[i],
             100.0 * stat[i] / (double) nb);
    }
  }
}
