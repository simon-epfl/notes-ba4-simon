### Algorithmes de tri

input: a seq. of $n$ numbers
output: a permutation (reordering) of the input seq.
#### Tri par insertion

- au début on a rien
- on prend les cartes une par une et on les insère au bon endroit
- pour connaître le bon endroit, on compare la nouvelle carte avec les cartes existantes de droite à gauche
#### Tri par fusion

- on sépare notre liste en deux jusqu'à avoir des listes de taille 1
- ensuite on fusionne les paires de listes triées pour produire une liste triée

$$ T(n) = cases(Theta(1) "if" n < c, a T(n/b) + D(n) + C(n)) $$
(prix de diviser, prix de combiner)

### Résoudre les relations de récurrence

$T(n) = 2 T(n/2) + c dot n$
$= 2(2 T(n/4) + c dot n/2) + c dot n = 4 T(n/4) + 2 dot c n$
$... = 8 T(n/8) + 3 dot c n$

On voit un pattern ! $T(n) = 2^k T(n/2^k) + k dot c n$ 
On en déduit $T(n) = Theta(n log n)$

#### Par induction

on veut montrer que $exists a in RR "s.t." a > 0 "and" T(n) <= a dot n log n$.
- cas de base : on trouve la valeur de $T(2), T(3), T(4)$ et on ajuste a tel que le cas de base soit satisfait.
- récurrence : $2 T(n/2) + c n <= 2 dot (a n)/2 log(n / 2) + c dot n = a dot n log(n/2) + c n = a dot n log (n) - a n + c n$ (on utilise l'hypothèse d'induction) $<= a dot n log(n)$ (on prend $a >= c$ comme ça $-a n + c n <= 0$).
- donc on peut trouver un $a$ tel quel le cas de base et la récurrence soient satisfaits donc $T(n) = O(n log n)$.
On doit prouver la même chose pour la lower bound ($exists b > 0 "s.t." T(n) >= b dot n log n forall n>= 0$).

#### Master method

On a $T(n) = a T(n/b) + f(n)$, $a >= 1, b > 1$.
- si $f(n) = Theta(n^(log_b (a)))$, then $T(n) = Theta(n^(log_b (a)) log n)$ 

### Loop invariant

Similar to induction but up to a certain $n$.

* Initialization
* Maintenance
* Termination


