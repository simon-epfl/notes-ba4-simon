Pour les entrées on utilise `scanf("%lf", &variable)`, le `&` permet de donner l'adresse de la variable à `scanf` pour qu'il la modifie.

Pour utiliser `M_PI` (= pi), 
```c
/* ligne pour avoir M_PI (= pi). A mettre AVANT le include de math.h. */
#define _USE_MATH_DEFINES
#include <math.h>
```

Ne pas oublier le mot-clef `const` le plus souvent que possible.

Les pointeurs :
- référence (éviter la duplication, pointeur A vers objet X, pointeur B vers objet X)
	- ne pas oublier de protéger l'argument avec un `const`
- généricité (on veut que le pointeur A pointe vers objet X puis vers objet Y)
	- `typedef double *Fonction(double)` 
- portée (pour éviter que l'objet ne soit enlevé de la mémoire)
	- par exemple en retour de fonction : `Complexe* resultat = malloc(sizeof(Complexe))` **et non pas &resultat!**

allouer un pointeur : créer une valeur puis en garder l'adresse dans le pointeur
libérer un pointeur : supprimer la valeur de la mémoire (mais l'adresse dans le pointeur est toujours la même). une bonne pratique est d'effacer aussi l'adresse du pointeur.

`nullptr` en C++ c'est `NULL`  en C

déclaration d'un pointeur : `int* ptr = NULL;` ou `int* ptr = &i;`
pour lire la valeur d'un pointeur `printf("%d", *ptr);`
pour les structures `p->x` est équivalent à `(*p).x` si `p` est un pointeur sur une structure

JCC écrit plutôt `type const* ptr` (identique à `const type* ptr`) $arrow$ déclare un pointeur sur un objet constant de type `type` (on ne pourra pas modifier la valeur de l'objet au travers de `ptr` mais on pourra faire pointer `ptr` vers un autre objet)
```c
*ptr = 9; // impossible !
ptr = &j; // possible!
```

et `type* const ptr` $arrow$ déclare un pointeur constant sur un objet (on ne pourra pas faire pointer `ptr` vers autre chose mais on pourra modifier la valeur de `obj` au travers de `ptr`)
```c
*ptr = 9; // possible !
ptr = &j; // impossible
```

allouer de la mémoire en C :
- allocation statique, à la compilation : sur le stack, variables locales
- allocation dynamique, pendant l'exécution : sur le heap, indépendamment du fait qu'il y ait une variable ou non

`ptr = malloc(taille);` pour allouer dans le `heap` 
`calloc(3, sizeof(double))` pour allouer 3 double à la suite dans le `heap` on ne fait pas `malloc(3 * sizeof(double))` car il pourrait y avoir un débordement avec la multiplication
ces fonctions renvoient `NULL` si l'allocation n'a pas pu se faire

`calloc` initialise aussi la mémoire à zéro, tandis que `malloc` n'initialise rien
on peut utiliser `memset` pour initialiser la mémoire `memset(ptr, 0, sizeof(*ptr))` pour initialiser à `0`

avec `free(ptr);` on libère la mémoire allouée
bonne pratique : ajouter aussi un `ptr = NULL` après.

```c
typedef struct {
	size_t size; // nombre d'éléments dans le tableau
	size_t allocated; // taille allouée en mémoire
	int* content;
} vector;
```

`realloc(ptr_old, nouvelle_taille)` (comme si c'était `re(m)alloc`) permet de réallouer des zones déjà allouées (en **augmentation** ou **diminution**). Le pointeur va être déplacé si nécessaire (si par exemple dans la zone mémoire initiale il n'y a plus la place de rajouter des éléments). Si le `realloc` échoue, la zone mémoire initiale sera inchangée (et `NULL` sera renvoyé).
attention : bien vérifier avec `realloc` qu'on vérifie qu'il n'y a pas de débordement!