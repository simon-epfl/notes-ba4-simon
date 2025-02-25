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

$$ T(n) = cases(theta(1) "if" n < c, a T(n/b) + D(n) + C(n)) $$
(prix de diviser, prix de combiner)














































#### Loop invariant

Similar to induction but up to a certain $n$.

* Initialization
* Maintenance
* Termination

