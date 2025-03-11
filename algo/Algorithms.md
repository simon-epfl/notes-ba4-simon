### Algorithmes de tri

entrée : a seq. of $n$ numbers
sortie : a permutation (reordering) of the input seq.
#### Tri par insertion

- au début on a rien
- on prend les cartes une par une et on les insère au bon endroit
- pour connaître le bon endroit, on compare la nouvelle carte avec les cartes existantes de droite à gauche
#### Tri par fusion

- on sépare notre liste en deux jusqu'à avoir des listes de taille 1
- ensuite on fusionne les paires de listes triées pour produire une liste triée

## Divide and conquer

On a la relation de récurrence suivante :
$$ T(n) = cases(Theta(1) "if" n < c, a T(n/b) + D(n) + C(n)) $$
(prix de diviser, prix de combiner)

$a$ est le nombre de sous-problèmes créés à chaque récurrence, et $n/b$ est la taille de chaque sous-problème.

> [!tldr] Exemple
> On peut imaginer un algo qui prend une liste de taille $n$ et sépare cette liste en 3 sous-listes de taille $n/2$.
> --> $a = 3$ et $b = 2$.

### Master theorem

- On est dans le cas **bottom-heavy** quand le coût du divide and combine est plus petit que $n^(log_b (a - epsilon))$ pour un $epsilon > 0$, c-a-d que le nombre total de feuilles. Car (avec de l'analyse), on a $n^(log_b a) = a^(log_b n)$, qui est le nombre de feuilles, étant donné qu'on a $a$ enfants par noeud et que la taille de l'arbre est $log_b (n)$. La majorité du calcul est situé dans le nombre de divisions à faire pour calculer toutes les feuilles (diviser un par deux et combiner deux en un ne coûte pas très cher). Formellement, quand $D(n) + C(n) = O(n^(log_b (a - epsilon)))$. Et donc :
$$ T(n) = Theta(n^(log_b a)) $$
![[image.png|462x223]]

- On est dans le cas **top-heavy** quand le coût du divide et combine est plus grand que $n^(log_b a + epsilon)$. Formellement, quand : $D(n) + C(n) = Omega(n^(log_b a))$. C'est-à-dire que diviser et combiner coûte très cher, donc tout le coût du calcul sera fait à la racine (quand on devra séparer la grosse liste de taille $n$, la racine). Et donc :
$$T(n) = Theta(f(n))$$
- Quand les deux sont équilibrés, $C(n) + D(n) = Theta(n^(log_b a))$, on a :
$$ T(n) = Theta(n^(log_b a) dot log_b (n)) $$
#### Dans le cas unbalanced ?

Si on a la récurrence suivante : $T(n) = T(n/5) + 2 T((2n)/5) + Theta(n)$
On sait qu'on aura une branche à gauche très courte en $log_5(n)$ et une branche à droite très longue en $log_(5/2) (n)$. On peut donc bound notre taille d'arbre :
$$ log_5(n) <= "hauteur arbre" <= log_(5/2) (n) $$
Supposons qu'on est dans le cas d'un arbre balanced avec une hauteur de $log_5(n)$. On a donc la relation $T_"low" (n) = 5 T(n/5) + Theta(n)$. Et on peut construire un arbre balanced avec $T_"high" (n) = 5/2 T((2n)/5) + Theta(n)$. Et d'après le master theorem : $$Theta(n log_5 (n)) <= T(n) <= Theta(n log_(5/2) (n)) arrow.double.long T(n) = Theta(n log n)$$Mais pourquoi peut-on dire que $T_"low" (n) <  T(n)$ ? Parce que le problème semble très différent, on sépare maintenant en 5 problèmes (donc plus de divisions et de fusions ?), au lieu de 3, et puis on change la taille de ces problèmes, etc. il n'y a pas que la hauteur qui compte pour définir si un problème est plus coûteux qu'un autre, si ?
$arrow$ en fait, dans un cas comme dans l'autre, on a **toujours** $Theta(n)$ travail à chaque étage, et c'est ça qui compte. Certes, on aura plus de divisions et plus de listes à fusionner, mais comme combiner et diviser est fait en $Theta(n)$, alors diviser deux listes de taille $(2n)/5$ ou 4 listes de taille $n/5$ est indentique (à un facteur constant $c$ devant près). Donc les deux programmes ont le même coût jusqu'à ce qu'un des deux arrive à la fin de sa hauteur (et la hauteur détermine la complexité parce que c'est le nombre d'étages de $Theta(n)$ qu'on aura, le nombre de $c n$ opérations à faire !).
### Résoudre les relations de récurrence

$T(n) = 2 T(n/2) + c dot n$
$= 2(2 T(n/4) + c dot n/2) + c dot n = 4 T(n/4) + 2 dot c n$
$... = 8 T(n/8) + 3 dot c n$

On voit un pattern ! $T(n) = 2^k T(n/2^k) + k dot c n$ 
On en déduit $T(n) = Theta(n log n)$
#### Prouver complexité d'une récurrence par induction

on veut montrer que $exists a in RR "s.t." a > 0 "and" T(n) <= a dot n log n$.
- cas de base : on trouve la valeur de $T(2), T(3), T(4)$ et on ajuste a tel que le cas de base soit satisfait.
- récurrence : $2 T(n/2) + c n <= 2 dot (a n)/2 log(n / 2) + c dot n = a dot n log(n/2) + c n = a dot n log (n) - a n + c n$ (on utilise l'hypothèse d'induction) $<= a dot n log(n)$ (on prend $a >= c$ comme ça $-a n + c n <= 0$).
- donc on peut trouver un $a$ tel quel le cas de base et la récurrence soient satisfaits donc $T(n) = O(n log n)$.
On doit prouver la même chose pour la lower bound ($exists b > 0 "s.t." T(n) >= b dot n log n forall n>= 0$).
### Loop invariant

Similar to induction but up to a certain $n$.

* Initialization
* Maintenance
* Termination

### Maximum sub-arrays problem

On a une entrée $[0, 2, -4, 3, -1, 4, 5, 7, -9]$ et on veut trouver le sous-intervalle avec la plus grande somme $[3, -1, 4, 5, 7]$.

On peut tout bruteforce, tester toutes les combinaisons : $O(n^2)$.

On peut faire mieux en $n log n$ avec du divide et conquer :
- on peut séparer le problème en deux (c'est facile on coupe au milieu)
- mais comment combiner les deux, une fois qu'on a les solutions de l'un et de l'autre ? (en reprenant l'exemple plus haut, $[3], [5,7]$).
	- on connaît la solution à gauche
	- on connaît la solution à droite
	- mais on doit vérifier qu'en se chevauchant on a pas une meilleure solution $O(n)$:
		- pour ça on doit trouver la plus grande somme à gauche qui commence au milieu (ici $3 - 1 = 2$)
		- trouver la plus grande somme à droite qui commence au milieu (ici $4 + 5 + 7 = 16$)
		- les sommer ($2 + 16 = 18$)
	- comparer ces trois solutions prendre la meilleure

### Matrix multiplication

On a comme entrées deux matrices carrées, $n times n$ :
- $A = (a_(i j))$
- $B = (b_(i j))$

On sort une matrice carrée $n times n$ : $C = (c_(i j))$ où $A dot B = C$.

Example (n = 2) 

$$ mat(c_(1 1), c_(1 2); c_(2 1), c_(2 2) ) = mat(a_11, b_11; a_21, a_22) dot mat(b_11, b_12; b_21, b_22) $$
$$c_11 = a_11 b_11 + a_12 b_21 + ... + a_(1 n) b_(n 1) = sum_(k = 1)^n a_(1 k) b_(k 1)$$
$$ " Plus généralement, " c_(i j) = sum_(k = 1)^n a_(i k)b_(k j) $$

On peut écrire un algo simple qui en temps $Theta(n^3)$ qui calcule $c_(i j)$ (trois boucles for jusqu'à $n$ qui pour chaque entrée $i, j$ somme tous les produits).
$arrow$ le temps utilisé par cet algo est $Theta(n^2)$, parce qu'on ne créé par une variable à chaque boucle (pour la dernière boucle qui somme les produits on les ajoute à une variable existante $c_(i j)$).

**Avec divide and conquer**

Block multiplication : si on sépare notre matrice carré de taille $n times n$ en 4 matrices de taille $n/2 times n/2$, on peut multiplier ces matrices entre elles pour obtenir la matrice finale. Par exemple :

$C_11 = A_11 times B_11 + A_12 times B_21$
$C_12 = A_11 times B_12 + A_12 times B_22$
...
$C_22 = A_21 times B_12 + A_22 times B_22$

Comme on le voit, recombiner les problèmes est plus facile (c'est une addition sur tous les $i, j$ donc en $n^2$). On a 8 sous-produits à calculer.

$$ T(n) = cases(Theta(1) "if " n = 1, 8 T(n/2) + Theta(n^2) " if " n>1) $$

avec le Master theorem, on réalise qu'on résout la récurrence : $T(n) = Theta(n^3)$. pas de progrès !
problème : on a trop de sous-problèmes (8 !)

> [!tip] Sous-problème plus simple, multiplier des nombres complexes
> 
> $(a + i b) dot (c + i d) = (a dot c - b dot d) + i (a dot d + b dot c) = r$
> 
> Pour multiplier 2 complexes, on a dû faire 4 produits de nombres réels.
> Calculons :
> $s_1 = (a + b) dot (c + d) = a c + a d + b c + b d$
> $s_2 = a dot c$
> $s_3 = b dot d$
> 
> $r = (s_2 - s_3) + i(s_1 - s_2 - s_3)$
> 
> Maintenant on a un produit de moins nécessaire pour trouver $r$! On a plus d'additions et de soustractions. On peut utiliser le même principe pour les matrices.

En appliquant cette méthode aux matrices, on arrive à 7 produits !
## Multiplier deux nombres entiers

On a deux entiers de $n$ chiffres $x$ et $y$ en base $b$. On doit trouver $x dot y$.
Ce qu'on a vu au lycée c'est un algo en $Theta(n^2)$.

Note : multiplier par $b^k$ c'est considéré en $O(1)$, c'est juste un shift.

On peut séparer nos deux nombres en deux parties :
$$ X = X_H dot 10^(n/2) + X_L " et " Y = Y_H dot 10^(n/2) + Y_L$$
Par exemple si $X = 1234$, on a $n/2 = 2$ donc $X_H = 12, X_L = 34$.

On veut calculer :$$X dot Y = (X_H dot 10^(n/2) + X_L) dot (Y_H dot 10^(n/2) + Y_L) \ = X_H dot Y_H dot 10^n + (X_H Y_L + X_L Y_H) dot 10^(n/2) + X_L Y_L $$
On a donc $4$ multiplications de taille $n/2$ ! mais avec l'algo de **Karatsuba**, on peut réutiliser l'astuce des nombres complexes et calculer :
$$ M = (X_H + X_L) dot (Y_H + Y_L) \ X dot Y = X_H Y_H dot 10^n + (M - X_H Y_H - X_L Y_L) dot 10^(n/2) + X_L Y_L $$
En fait, on a donc en fait que 3 multiplications de taille $n/2$ à calculer ! $M, X_L Y_L, X_H Y_H$ 

On arrive à :
$$ T(n) = 3T(n/2) + Theta(n) = Theta(n^(log_2(3))) $$

## Heaps

**(min/max)-heap property** : on veut que chaque noeud ait une valeur plus grande (ou plus petite pour le min-heap) que chacun de ses enfants directs.
- on sait que la maximum est toujours en haut de l'arbre
- la hauteur d'un noeud est le plus long chemin simple (le nombre de segments) entre le noeud et une feuille 

On utilise un tableau pour stocker les heaps :

![[image-20.png|486x256]]

### Heapify

Comment maintenir la **(min/max)-heap property** ? Il existe un algorithme qui nous permet de retrouver la heap-property si elle n'est pas respectée qu'à la racine en **O(log n)**. 

- comparer $A[i], A[L(i)], a[R(i)]$
- si nécessaire, échanger $A[i]$ avec le plus grand des enfants
- continuer jusqu'à ce que la règle soit correcte

### Build Max/Min Heap

Cet algorithme est en **O(n log n)** et permet de construire un heap à partir d'un tableau désordonné. Il appelle **heapify** sur chaque élément du tableau. $n dot "heapify" = n dot log n$.
## Heap sort

Heapsort a la même complexité que le **merge sort**, mais est **in-place** (comme insertion sort). Le meilleur des deux mondes ?

- on créé un max-heap à partir du tableau
- on fait un **build-max-heap**
- on prend le premier élément max et on le met au début du tableau (on le discard)
- on met le dernier élément du tableau à sa place
- on appelle **heapify**
- etc. en boucle jusqu'à ce que le tableau soit trié
