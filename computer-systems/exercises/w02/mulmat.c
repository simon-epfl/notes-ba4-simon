// /* C89 */
// #include <stdio.h>

// #define N 10

// typedef struct
// {
//     double* m;
//     size_t lignes;
//     size_t colonnes;
// } Matrice;

// Matrice* lire_matrice(void);
// void affiche_matrice(Matrice const*);
// Matrice* multiplication(Matrice const* a, Matrice const* b, Matrice* res);

// /* ---------------------------------------------------------------------- */
// int main(void)
// {
//     Matrice* M1 = lire_matrice();
//     Matrice* M2 = lire_matrice();
//     Matrice* M;

//     if (M1->colonnes != M2->lignes)
//         printf("Multiplication de matrices impossible !\n");
//     else
//     {
//         printf("Résultat :\n");
//         affiche_matrice(multiplication(&M1, &M2, &M));
//     }
//     return 0;
// }

// /* ---------------------------------------------------------------------- */
// Matrice* lire_matrice(void)
// {
//     Matrice* resultat = malloc(sizeof(Matrice));
//     size_t lignes = 2;
//     size_t colonnes = 2;

//     printf("Saisie d'une matrice :\n");

//     do
//     {
//         printf("  Nombre de lignes (< %d) : ", N + 1);
//         scanf("%lu", &lignes); /* "%zu" en C99 ; c'est mieux. */
//     } while ((lignes < 1) || (lignes > N));

//     do
//     {
//         printf("  Nombre de colonnes (< %d) : ", N + 1);
//         scanf("%lu", &colonnes);
//     } while ((colonnes < 1) || (colonnes > N));

//     resultat->lignes = lignes;
//     resultat->colonnes = colonnes;
//     {
//         size_t i, j;
//         for (i = 0; i < lignes; ++i)
//             for (j = 0; j < colonnes; ++j)
//             {
//                 printf("  M[%lu, %lu]=", i + 1, j + 1);
//                 scanf("%lf", &resultat->m[j*resultat->colonnes + i]);
//             }
//     }

//     return resultat;
// }

// /* ---------------------------------------------------------------------- */
// Matrice* multiplication(Matrice const* a, Matrice const* b, Matrice* res)
// {
//     Matrice* resultat = a; /* Disons que par convention on retourne a si la
//                            * multiplication ne peut pas se faire.
//                            */
//     size_t i, j, k;       /* variables de boucle */

//     if (a->colonnes == b->lignes)
//     {
//         resultat->lignes = a->lignes;
//         resultat->colonnes = b->colonnes;

//         for (i = 0; i < a->lignes; ++i)
//             for (j = 0; j < b->colonnes; ++j)
//             {
//                 resultat->m[i][j] = 0.0;
//                 for (k = 0; k < b->lignes; ++k)
//                     resultat->m[i][j] += a->m[i][k] * b->m[k][j];
//             }
//     }

//     *res = *resultat;
// }

// /* ---------------------------------------------------------------------- */
// void affiche_matrice(Matrice const* matrice)
// {
//     size_t i, j;
//     for (i = 0; i < matrice->lignes; ++i)
//     {
//         for (j = 0; j < matrice->colonnes; ++j)
//             printf("%g ", matrice->m[i][j]);
//         putchar('\n');
//     }
// }


#include <stdio.h>
#include <stdlib.h>

#ifndef SIZE_MAX
#define SIZE_MAX (~(size_t)0)
#endif

typedef struct {
   double* m;
  /* Attention ici : on stocke le tableau en continu donc PAS DE double**. *
   * Ceux qui préfèrent double** auront une indirection de plus et un      *
   * tableau de pointeurs en plus en mémoire: perte de place !             *
   * Sans compter  que, comme ce sera présenté dans le cours 9, de telles  *
   * données ne seraiennt pas continues en mémoire.                        */

   size_t lignes;
   size_t colonnes;
} Matrice;

Matrice* empty(Matrice*);
void libere(Matrice*);
Matrice* redimensionne(Matrice*, size_t lignes, size_t colonnes);
Matrice* lire_matrice(Matrice*);
void affiche_matrice(Matrice const *);
Matrice* multiplication(Matrice const * a, Matrice const * b,
                        Matrice* resultat);

/* ---------------------------------------------------------------------- */
int main(void)
{
  Matrice M1, M2, M3;

  (void) lire_matrice(&M1);
  /* On met cet appel à lire_matrice ici et non pas dans l'appel de    *
   * multiplication() car on ne peut garantir l'ordre d'évaluation des *
   * arguments de l'appel (à multiplication)) et donc on ne peut       *
   * garantir que la lecture de M1 sera faite avant celle de M2.       *
   * Mettre cet appel ici permet de le garantir.                       */

  if (multiplication(&M1, lire_matrice(&M2), empty(&M3))
      /* Attention à ne pas oublier d'initialiser M3 !! */
      == NULL) {
    printf("Multiplication de matrices impossible !\n");
  } else {
    printf("Résultat :\n");
    affiche_matrice(&M3);
  }

  libere(&M1);
  libere(&M2);
  libere(&M3);
  return 0;
}

/* ---------------------------------------------------------------------- */
Matrice* empty(Matrice* resultat)
{
  if (resultat != NULL) {
    resultat->lignes   = 0    ;
    resultat->colonnes = 0    ;
    resultat->m        = NULL ;
  }
  return resultat;
}

/* ---------------------------------------------------------------------- */
void libere(Matrice* resultat)
{
  if (resultat != NULL) {
    if (resultat->m != NULL) free(resultat->m);
    (void) empty(resultat);
  }
}

/* ---------------------------------------------------------------------- */
Matrice* lire_matrice(Matrice* resultat)
{
  if (resultat != NULL) {
    size_t lignes;
    size_t colonnes;

    do {
      printf("Saisie d'une matrice :\n");
    
      do {
        printf("  Nombre de lignes : ");
        scanf("%zu", &lignes);
      } while (lignes < 1);
    
      do {
        printf("  Nombre de colonnes : ");
        scanf("%zu", &colonnes);
      } while (colonnes < 1);

      resultat->lignes   = lignes;
      resultat->colonnes = colonnes;

      if (SIZE_MAX / lignes < colonnes) {
        resultat->m = NULL;
      } else {
        resultat->m = calloc(lignes*colonnes, sizeof(*(resultat->m)));
      }
      if (NULL == resultat->m) {
        printf("Matrice trop grande pour être allouée :-(\n");
      }

    } while (NULL == resultat->m);

    { size_t i, j;
      for (i = 0; i < lignes; ++i) 
        for (j = 0; j < colonnes; ++j) {
          printf("  M[%zu,%zu]=", i+1, j+1);
          scanf("%lf", &resultat->m[i*resultat->colonnes+j]);
        }
    }
  }
  return resultat;
}

/* ---------------------------------------------------------------------- */
Matrice* redimensionne(Matrice* resultat, size_t lignes, size_t colonnes)
{
  if (resultat != NULL) {
    if (SIZE_MAX / lignes < colonnes) return NULL;
    if (resultat->lignes*resultat->colonnes < lignes*colonnes) {
      if ((lignes*colonnes) > SIZE_MAX / sizeof(*(resultat->m))) return NULL;
      resultat->m = realloc(resultat->m, lignes*colonnes*sizeof(*(resultat->m)));
      if (NULL == resultat->m) {
        resultat->lignes   = 0;
        resultat->colonnes = 0;
        return NULL;
      } else {
        resultat->lignes   = lignes;
        resultat->colonnes = colonnes;
      }
    }
  }
  return resultat;
}

/* ---------------------------------------------------------------------- */
Matrice* multiplication(Matrice const * a, Matrice const * b,
                        Matrice* resultat)
{
  if (resultat != NULL) {
    size_t i, j, k;

    if ((a->colonnes == b->lignes) 
        && (redimensionne(resultat, a->lignes, b->colonnes) != NULL)) {
      for (i = 0; i < a->lignes; ++i) 
        for (j = 0; j < b->colonnes; ++j) {
          resultat->m[i*resultat->colonnes+j] = 0.0;
          for (k = 0; k < b->lignes; ++k) 
            resultat->m[i*resultat->colonnes+j] += a->m[i*a->colonnes+k] 
                                                   * b->m[k*b->colonnes+j];
        }
    } else {
      resultat = NULL;
    }
  }
  return resultat;
}

/* ---------------------------------------------------------------------- */
void affiche_matrice(Matrice const * matrice)
{
  size_t i, j;
  const size_t imax = matrice->lignes*matrice->colonnes;
  for (i = 0; i < imax; i += matrice->colonnes) {
    for (j = 0; j < matrice->colonnes; ++j) {
      printf("%g ", matrice->m[i+j]);
    }
    putchar('\n');
  }
}
