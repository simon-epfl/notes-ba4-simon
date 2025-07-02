## Divide and conquer

On a la relation de récurrence suivante :
$$ T(n) = cases(Theta(1) "if" n < c, a T(n/b) + D(n) + C(n)) $$
(prix de diviser, prix de combiner)

$a$ est le nombre de sous-problèmes créés à chaque récurrence, et $n/b$ est la taille de chaque sous-problème.

> [!tldr] Exemple
> On peut imaginer un algo qui prend une liste de taille $n$ et sépare cette liste en 3 sous-listes de taille $n/2$.
> $arrow a = 3$ et $b = 2$.
### Master theorem

- On est dans le cas **bottom-heavy** quand le coût du divide and combine est plus petit que $n^(log_b (a - epsilon))$ pour un $epsilon > 0$, c-a-d que le nombre total de feuilles. Car (avec de l'analyse), on a $n^(log_b a) = a^(log_b n)$, qui est le nombre de feuilles, étant donné qu'on a $a$ enfants par noeud et que la taille de l'arbre est $log_b (n)$. La majorité du calcul est situé dans le nombre de divisions à faire pour calculer toutes les feuilles (diviser un par deux et combiner deux en un ne coûte pas très cher). Formellement, quand $D(n) + C(n) = O(n^(log_b (a - epsilon)))$. Et donc :
$$ T(n) = Theta(n^(log_b a)) $$
![[assets/image.png|462x223]]

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

![[assets/image-20.png|486x256]]

### Heapify

Comment maintenir la **(min/max)-heap property** ? Il existe un algorithme qui nous permet de retrouver la heap-property si elle n'est pas respectée qu'à la racine en **O(log h)**. 

- comparer $A[i], A[L(i)], a[R(i)]$
- si nécessaire, échanger $A[i]$ avec le plus grand des enfants
- continuer jusqu'à ce que la règle soit correcte

### Build Max/Min Heap

Cet algorithme est en **$Theta$(n)** et permet de construire un heap à partir d'un tableau désordonné. Il appelle **heapify** sur chaque élément du tableau (sauf sur les tous petits noeuds du bas mais ça importe peu). $n dot "heapify" = n dot log h$...?

Sauf qu'en fait, plus on remonte dans l'arbre pour faire n'est pas $log n$!
$$ sum_(h = 0)^(log n) ("# noeuds") dot O(h) = O(sum_(h = 0)^(log n) n/2^h dot h) $$
(le nombre de noeuds à chaque hauteur $h$ est inférieur à $n/(2^h)$ )
On peut montrer avec de l'analyse que $$ sum_(h = 0)^(log n) h/(2^h) < 2" car " sum_(h = 0)^(infinity) h/(2^h) = (1/2)/(1 - 1/2)^2 = 2$$
```
build_max_heap(A, n):
	for i = floor(n/2) downto 1
			max_heapify(A, i, n)
```

> [!tip] Comment montrer que **build_max_heap'** est en $n log n$ 
> 
> ![[assets/image-34.png]]
> 
> On sait que pour chaque noeud $i$ inséré on a un travail de $log(i)$ pour le faire remonter dans le worst case :
> $$ sum_(i = 0)^h "floor"(log(i)) <= sum_(i = n/2)^n "floor"(log(i)) <= n/2 log(n/2) " en " O(n log n)$$
## Heap sort

Heapsort a la même complexité que le **merge sort**, mais est **in-place** (comme insertion sort). Le meilleur des deux mondes ?

- on créé un max-heap à partir du tableau
- on fait un **build-max-heap** (n log n)
- on prend le premier élément max et on le met au début du tableau (on le discard)
- on met le dernier élément du tableau à sa place
- on appelle **heapify**
- etc. en boucle jusqu'à ce que le tableau soit trié (donc $n$ heapify, en $n log n$)

```
heap_sort(A, n):
	build_max_heap(A, n)
	for i = n downto 2
		exchange A[1] with A[i]
		max_heapify(A, 1, i - 1)
```

## Priority Queues

- we want to maintain a **dynamic set S of elements** using heaps
- each set element has a **key** and a **value**

**Supported operations**

- `maximum_element(A, n)`: this is $Theta(1)$, we just have to return the first one
- `extract_maximum_element(A, n)`: $Theta(log n)$, we remove the maximum element, and replace it with the last one and run `heapify`
- `increase_key_value(A, key, n)`: $Theta(log n)$, on met à jour l'élément puis on regarde tous ses parents. S'il est plus grand, on inverse les deux.
- `insert_into_heap(A, key, n)`: $Theta(log n)$, on insert l'élément tout au bout avec une valeur de $- infinity$ puis on appelle `increase_key_value` dessus

## Stack implementation (last-in, first-out)

Utiles pour les allocations mémoires. 

![[assets/image-21.png|328x166]]

`Q.top` pointe à la position du dernier élément (celui qui vient d'arriver).
### Opérations

- `empty`: on check si le top est 0
- `push` : `S.top <- S.top + 1` puis `S[S.top] <- x`
- `pop`: `S.top <- S.top - 1` et `return S[S.top + 1]`

elles sont en $Theta(1)$.
## Queue implementation (first-in, first-out)

![[assets/image-22.png|0x0]]

- `Q.head` pointe à la position du premier élément
- `Q.tail` pointe à la position de là où le prochain élément arriverait

### Opérations

- `enqueue(Q, x)`:
	`Q[Q.tail] = x` et `if (Q.tail == Q.length) Q.tail = 1 else Q.tail += 1`

parce que si on enqueue deux fois, on va faire pointer la tail vers `1`! (parce que `13` n'existe pas)
et comme la head est `7` (soit après), on sait qu'on aura `8`, `9`, etc. définis

**Stacks** aned et sont bien et très performantes mais... ont un support limité : pas de recherche, par exemple.
## Linked list

- `L.head` pointe vers la tête de la liste
- chaque noeud `N` stocke `N.prev`, `N.key`, `N.next`
### Opérations

- `search`: $Theta(n)$
	`x <- L.head` and `while(x != nil and x.key != k) x = x.next` then `return x`
- `insert(x)`: $Theta(1)$
	`new_el = (/, x, L.head)` and `L.head.next = L.head` and `L.head <- new_el`
- `delete(x)`: $Theta(1)$
	`x.prev.next = x.next` (on lit celui avant x à celui après x)
	 (attention à bien gérer tous les cas)

> [!tip] Pour simplifier les opérations (gérer les cas de nuls, etc), on peut ajouter des sentinels! 
> 
> C'est-à-dire ajouter des éléments fake pour que les éléments réels ne soient jamais les premiers ou derniers.
> 
> ![[assets/image-29.png|639x454]]

## Binary search trees

à gauche, on met tous les nombres plus petits que la racine, et à droite tous les nombres plus grands (et on préfère avoir un arbre équilibré). créer un binary search trees c'est comme encoder dans un arbre la stratégie pour trouver le nombre avec un jeu de "tu dis plus grand ou plus petit"
### Comment stocker un binary search tree ?

On peut faire quelque chose comme les linked list. Chaque élément stocke : 
- la référence du parent `x.p`
- la référence de l'enfant gauche `x.left`
- la référence de l'enfant droit `x.right`
- la valeur de l'élément `x.key`

> [!question] Pourquoi on n'utilise pas le même tableau que pour les heaps ?
> 
> Pour les heaps, utilise le fait qu'on a à chaque fois un arbre "nearly-completed" (équilibré). Ici, on ne force pas forcément ça, on veut juste que l'enfant droit soit plus grand que le parent, et que l'enfant gauche soit plus petit. Ces deux exemples sont des binary search trees valides :
> 
> ![[assets/image-30.png|596x372]]
> ![[assets/image-31.png|477x285]]

### Opérations de recherche

La propriété la plus importante est la taille de l'arbre $h$.

- `tree_search(ptr_to_root, key)` en $Theta(h)$
	```c
	if (x == nil or ptr_to_root.key == key) return x
	else if (k < ptr_to_root.key) return tree_search(ptr_to_root.left, key)
	else return tree_search(ptr_to_root.right, key)
	```
- `tree_minimum(ptr_to_root)` en $Theta(h)$
	```c
	while (ptr_to_root.left != nil) ptr_to_root = ptr_to_root.left
	return ptr_to_root
	```
same for `tree_maximum`
- `successor(ptr_to_root)` (the next bigger node)
	```c
	if (ptr_to_root.right != null) return tree_minimum(ptr_to_root.right)
	else
		y = ptr_to_root.p
		while (y != null && x == y.right)
			x = y
			y = y.p
		return y
	```

> [!question] successor ?
> 
> C'est le noeud juste plus grand que le noeud actuel. Ici, le successeur de 5 est 6 :
> ![[assets/image-32.png|584x355]]

**printing orders :**
- in order : afficher à gauche, puis le root, puis à droite
- pre order : afficher le root, puis à gauche, puis à droite
- post order : afficher à gauche, puis à droite, puis le root

**comment insérer dans un binary search?**
- on cherche pour la clef
- quand on trouve nil, on insert là

**comment supprimer $z$ ?**
- si c'est une feuille, on supprime
- si c'est un noeud avec un enfant, on fait comme pour une linked list (on change juste les références)
- sinon, on trouve le successeur $y$ et on remplace $z$ par $y$
## Dynamic programming

Se souvenir de se qu'on a fait pour éviter de le refaire.

**Bottom-up** : on part de $f(0)$ et on remonte en cachant les résultats (fibo). ça ressemble un peu à remplir une table au fur et à mesure.
**Top-down fibo** : on part toujours de $f(n)$ puis on appelle $f(n-1)$, $f(n-2)$, avec un dictionnaire mémo qu'ils mettent à jour. on part de l'hypothèse qu'on connait les réponses des problèmes précédents.

```python
def fibonacci(n, memo=None):
    if memo is None:
        memo = {}
    if n in memo:
        return memo[n]
    if n <= 1:
        return n
    memo[n] = fibonacci(n - 1, memo) + fibonacci(n - 2, memo)
    return memo[n]

# Example usage:
print(fibonacci(10))  # Output: 55
```
![[assets/image-54.png]]

### Rod cutting

**Entrées** : une metal rod de taille $n$, une table des prix $p_i$ pour des rod de tailles $i$
**Sortie** : décider comment couper la rod en pièces et maximiser le prix

![[assets/image-55.png]]
![[assets/image-56.png]]


Pour n = 1 : r(`X`) = 1
Pour n = 2 : r(`X X`) = 2, r (`XX`) = 5
Pour n = 3 : r(`XX X`) = 6, r( `X X X`) = 3, r(`XXX`) = 8

On sait que si on décide de couper la tige de longueur $n$ à l'indice $i$, on a :
$$ "Optimal"(n) = p (i) + "Optimal"(n - i) $$

Mais comment savoir si le $i$ est optiomal ?  On teste tout !

$$ r(n) = max_(i = 1, ..., n-1) {p(i) + r(n - i); p(n)} $$
- $r(n)$, représente le revenu maximal que l'on peut obtenir avec une tige de longueur $n$.
- $p(i)$ est le prix d'un morceau de longueur $i$ selon la table des prix donnée.
- $r(n−i)$ correspond au revenu maximal obtenu avec le reste de la tige (de longueur $n -i$)

```python
def rod_cut(n, prices):
    if n == 0:
        return 0
    max_value = -inf
    for i in range(1, n + 1):
        max_value = max(max_value, prices[i] + rod_cut(n - i, prices))
    return max_value

prices = [0, 1, 5, 8, 9]  # Indexation des prix (0 pour aligner)
print(rod_cut(4, prices))  # Devrait afficher 10
```
bad, it's slow

**top-down memoized**

```python
def rc_memo(n, prices, memo=None):
    if memo is None:
        memo = [-inf] * (n + 1)
    
    if n == 0:
        return 0
    if memo[n] >= 0:
        return memo[n]

    q = -inf
    for i in range(1, n + 1):
        q = max(q, prices[i] + rc_memo(n - i, prices, memo))

    memo[n] = q
    return q
```

**bottom-up memoized**

```python
def rc_bottom_up(n, prices):
    dp = [0] * (n + 1)
    for j in range(1, n + 1):
        q = -inf
        for i in range(1, j + 1):
            q = max(q, prices[i] + dp[j - i])
        dp[j] = q
    return dp[n]
```

### Équivalence de deux algos

$$ r_2(n) = max_(i = 1, ..., n-1) {r(n - i) + p(i); p(n)} $$
est équivalent à
$$ r_1(n) = max_(i = 1, ..., n-1) {r(n - i) + r(i); p(n)}  $$
on voit assez vite que $r_1 (n) >= r_2(n)$ (au lieu de vendre un chunk de taille $i$ on prend la meilleure façon de le vendre)

$$ i = arg max_i {r(n-i), r(i)} $$

### Change coin making

ça ressemble au problème du rod-cutting 


## Matrix-chain multiplication

Comment les faire plus rapidement quand ils sont chaînés ?

On veut multplier $A_1 (50 times 5), A_2 (5 times 100), A_3 (100 times 10)$ (ce ne sont pas des matrices carré).

Nombre d'opérations pour $A_1 A_2$ : $50 times 5 times 100$ 
pour $B A_3$ : $50 times 100 times 10$ 
somme : $75 000$

Sinon on peut faire $A_1(A_2 A_3)$ : $5 dot 100 dot 10 + 50 dot 5 dot 10 = 7500$ multuplications

![[assets/image-63.png]]

#### Algorithme

**Entrée** : une suite de $n$ matrices où $A_i$ a comme dimensions $p_(i -1) dot p_i$
**Sortie** : la meilleure façon de mettre les parenthèses pour minimiser les multiplications

On pourrait utiliser un algorithme récursif :

![[assets/image-64.png]]

puis l'améliorer en passant une map `solutions` :

![[assets/image-65.png]]
#### Algorithme dynamic programming (bottom up)

![[assets/image-66.png]]

on remplit une table comme ça. c'est facile de remplir quand on multplie deux matrices ensemble mais qu'est-ce qu'il se passe quand on multiplie 3 ensemble ? on doit prendre le minimum.

![[assets/image-67.png]]

![[assets/image-68.png]]

## Longest common sub-sequence

**Input** : 2 séquences $X = (x_1, ..., x_m)$ et $Y = (y_1, ..., y_n$.
**Output** : une sous-séquence commune aux deux sont la longeur est maximale.

La sous-séquence n'a pas besoin d'être consécutive, mais elle doit être dans l'ordre.

Approche naïve : tester toutes les sous-séquences possibles dans $X$ et vérifier si elle existe dans $Y$. On en aurait pour $2^n$ (nb de possibilités) $dot n$ (tester si elle existe dans $Y$).
#### On prend le problème entre deux variables $i, j$

$L C S (X_i, Y_j)$ ?
avec $X_i = <x_1, ..., x_i>$ et $Y_j = < y_1, ..., y_j >$

On compare la dernière lettre :

- case $x_i = y_j$ , on prend le maximum entre :
	- $L C S (x_(i - 1) , y_j)$
	- $L C S (x_i, x_(j - 1))$
	- $1 + L C S (x_(i - 1), y_(j - 1))$

- case $x_i eq.not y_j$, on prend le maximum entre :
	- $L C S (x_(i - 1), y_j)$
	- $L C S (x_i, y_(j - 1))$

- Si $Z = <z_1, ..., x_k>$ est la LCS des deux, alors si $x_i = y_j$ alors $z_k = x_i = y_j$ (sinon on pourrait améliorer la chaîne en rajoutant $x_i$ à la fin et ce serait tjrs une subsequence).
- Si $x_i eq.not y_j$ alors $z_k eq.not x_i$ et Z est un LCS de $X_(i - 1)$ et $Y_j$.
- Si $x_i eq.not y_j$ alors $z_k eq.not y_j$ et Z est un LCS de $X_i$ et $Y_(j -1)$.

#### Analyse de la complexité

- compter le nombre de cellules à remplir $m dot n$
- compter le temps de remplir une cellule $Theta(1)$.

$arrow Theta(m dot n)$

```python
LCS(X, Y, m, n):

	let b[0, ..., m][0, ..., n] and c [0, ..., m][0, ..., n] be new tables

	for i= 1...m:
		c [i][0] = 0

	for j=1...n:
		c [0][j] = 0

	for i =1..m:
		for j=1..n:
			if X[i] == Y[j]: # on comp les dernières lettres
				c[i][j] = c[i - 1][j - 1] + 1
				b[i][j] = "arrow_diago"
			else
				if c[i - i][j] >= c[i, j-1]
					c[i][j] = c[i - 1][j]
					b[i][j] = "arrow_up"
				else
					c[i][j] = c[i][j-1]
					b[i][j] = "arrow_left'
	return (c, b)
```

## Optimal binary search trees

**Entrée** : un ensemble de clefs triées, et une probabilité $p_i$ que la clef $k_i$ soit cherchée.
**Sortie** : un BST qui minimise le coût de recherche

## Graphs

$G = (V, E)$ avec un ensemble de vertices (points) $V$ et un ensemble de segments (edges) entre les deux $E$.
#### Undirected graph

Comment stocker un graph ? On peut les tocker dans une adjancy matrice $V times V$ où chaque élément est un 0 ou un 1 en fonction de si le lien entre les deux noeuds est fait. 

Espace : $Theta(V^2)$
Temps pour lister tous les noeuds adjacents à u : $Theta(V)$
Temps pour déterminer si $(u, v) in E$ : $Theta(1)$

$arrow$ pas efficace en termes d'espace

![[image-16.png|499x175]]
#### Directed graph

![[image-17.png]]


#### Adjacency list

![[image-18.png]]

1 est connecté à 2 et est connecté à 4.

Espace : $Theta(V + E)$
Temps pour lister tous les noeuds adjacents $Theta("degree"(u))$.
Temps pour déterminer si $(u, v) in E$ : $Theta("degree"(u))$

### Breadth-First search

**Entrée** : un graphe, un point $s$ et un point $v$
**Sortie** : la distance de $s$ à $v$, pour tous les $v in V$

![[image-19.png]]

**noir** : queued + processed
**gris** : queued

![[image-20.png]]

Runtime : $O(V + E)$

### Lemma : le nombre de personnes qui ont un nb d'amis impairs est pairs (undirected graph)

$sum_u "deg"(u) = 2 dot |E| => (sum_u "deg"(u))/2 = |E|$
car chaque arête touche deux sommets

![[image-21.png]]

### Depth-first search

**Idée** : on essaye d'aller le plus loin possible (contrairement au BFS où on découvre tous les sommets autour d'abord).

On part de $b$, on découvre $a$ puis de $a$ on découvre autant que possible, par exemple $h$ (si on garde un ordre alphabétique), puis $g$, puis on a plus rien à découvrir ! on revient à $h$ et on regarde ce qu'on peut découvrir. On ne peut plus rien découvrir, on revient à $a$, etc.

![[image-22.png|0x0]]

Comme pour le BFS, si il nous manque des sommets à explorer quand on a finit, on choisit un autre noeud au hasard et on part de lui.

![[image-25.png]]


## Optimal binary search trees

![[image-23.png]]

![[image-24.png]]

![[image-26.png]]

## Topological sorting

**Entrée :** un graphe acyclique (DAG) $G = (V, E)$
**Sortie** : un ordre linéaire de noeuds t.q $(u, v) in E$ si $u$ est plus petit que $v$

![[image-27.png|458x295]]

**Graph acylique** : pas de back edge après un DFS

![[image-28.png|447x257]]

### Trouver les SCC

- appeler `DFS` pour calculer les finishing times $u.f$ de tous les notes
- calculer $G^T$ (inverser tous les segments)
- appeler $G^T$ mais dans la boucle principale, considérer les noeuds dans un ordre descendant (en fonction des finishing times)
- afficher les noeuds de chaque tree

(en fait en inversant les flèches, on évite de partir du strongly connected component + à l'intérieur d'un strongly connected component échanger les flèches ne changent rien à la structure)

![[image-32.png|584x355]]

## Flow networks

On veut un graphe sans "parallel" edges (un qui va de `(u, v)`, un `(v, u)`).

![[image-29.png]]

On veut envoyer un flux d'une source à un puits. Le flux est une fonction qui satisfait :
- une contrainte de capacité (pour tout segment edge, $0 <= f(u, v) <= c(u, v)$)
- une contrainte de conservation (le flux qui rentre = flux qui sort), $sum_"for all v" f(v, u) = sum_"for all v" f(u, v)$

valeur d'un flux : flow qui sort de la source - flow qui en revient

**Braess Paradox** : 4000 people driving from s to t every day. Pour aller le plus vite, il faut que la moitié prenne la route du haut, et l'autre moitié la route du bas.

![[image-31.png|477x285]]

### Ford-Fulkerson

$Theta(E f)$

Initialiser les edges à 0 flow.

Répéter jusqu'à ce qu'il n'y ait plus de augmenting path:
1. trouver un augmenting path (avec depth first search), il doit respecter les conditions suivantes :
	1. être un non-full forward edge (un segment qui va vers le puits non déjà remplis)
	2. ou être un non-empty backward edge (on doit pouvoir reverse du flux)
2. calculer la bottleneck capacity (le minimum de capacité d'un edge dans le chemin trouvé)
3. augmenter le total flow out

> [!question] Qu'est-ce que ça veut dire "reverse le flux" ?
> 
> En fait là on voit qu'on a un edge qui va de A vers D avec une capacité de 8. Puis on trouve un chemin qui va dans l'autre sens (et qui pourrait utiliser 4 unités de flux). Le fait qu'on ait 6 qui arrive en bas et plus 2 nous permet d'avoir moins besoin de flux entrant en D, donc on "reverse" on en enlève de A vers D. Et comme on fait ça, on a aussi du flux entrant en A en + qu'on peut réutiliser.
> 
> ![[image-35.png]]

> [!question] Min-cut
> 
> Si on trouve le "min-cut" d'un flow on trouve aussi le maximum flow!
> 
> On compte tous les edges qui vont de avant notre cut jusqu'à après notre cut. On ignore les autres.
> 
> ![[image-36.png]]

## Edge-disjoint paths as flow network

- on met toutes les capacités de chaque route à 1
- on calcule le max flow
- 
The maximum flow value 'f' in this context represents the number of edge disjoint paths between the source and the sink because each path can carry exactly 1 unit of flow, given that each edge's capacity is set to 1. With a maximum flow of 'f', it implies that there are indeed 'f' paths from the source to the sink that do not share any edges, thus being edge disjoint.
## Disjoint-set data structures

On veut un représentant par ensemble pour lui donner un nom.
On ne peut pas avoir deux éléments dans le même ensemble.

- `make-set(x)` : créer un nouveau set $S_i = {x}$ et ajouter $S_i$ à $S$

- `union(x, y)`: si $x in S_x, y in S_y$ alors $S = S - S_x - S_y union {S_x union S_y}$ 
	- détruits $S_x$ et $S_y$ comme ils doivent être disjoints
	- le représentant du nouveau set est n'importe quel membre de $S_x union S_y$, souvent le représentant d'un des deux ensembles
	

- `find(x)` : renvoie le représentant du set dans lequel il y a `x`

### Stocker les sets dans une linked list :

![[image-50.png]]

make, créer une liste vide en $Theta(1)$
union:
	- on append toujours la petite liste à la grande
	- on a $n_1$, $n_2$ la taille des deux sets. on est en $Theta(n_2)$. (mais on peut opti en append la liste la courte à l'autre).
find: en $Theta(1)$ comme chaque noeud pointe vers le représentant
### Stocker les sets dans un forest of trees :

- `find`, on remonte les pointeurs jusqu'à la racine, le coût de find dépend de là où est l'élément dans l'arbre

Le rang est une borne supérieure à la hauteur de l'arbre.

![[image-51.png]]

On peut optimiser `find` en rendant tous les noeuds un enfant direct du représentant. (on remonte dans l'arbre et on connecte tous les éléments à la racine)

- `union by rank` : rendre la racine de l'arbre avec le rang le plus petit un enfant direct de la racine de l'arbre plus grand. l'objectif est de garder les arbres les plus horizontaux possibles pour accélérer find

### Minimum Spanning Trees

**Spanning tree :** un ensemble $T$ de segments qui touchent tous les noeuds et acyclique.

En entrée : un graph non dirigé $G = (V, E)$ avec des poids $w(u, v)$ pour chaque segment $(u, v) in E$.
En sortie : un spanning tree avec le coût le plus faible.

Un **cut** $(S, V backslash S)$ est une partition des noeuds en deux ensembles non vides disjoints $S$ et $V backslash S$.
Un **crossing-edge** est un segment qui connecte un noeud dans $S$ à un noeud dans $V backslash S$.

Si on considère un **cut** $(S, V backslash S)$ et :
- $T$ est un arbre sur $S$ qui est une partie d'un MST
- $e$ est un crossing-edge de poids minimal

Alors il y a un MST de $G$ qui contient $e$ et $T$.

![[image-52.png|572x293]]
Si $e$ est déjà dans le MST, on est bon.
Sinon, on ajoute $e$. Ça peut créer un cycle. Dans ce cas, il y a au moins un autre crossing edge dans le cycle $w(f) >= w(e)$. On remplace $f$ par $e$ dans le MST.
On en obtient un nouveau qui contient $e$ et $T$.
### Prim's algorithm

On commence par n'importe quel noeud $v$ et on l'ajoute à $T$. On a donc un cut induit par $T$ (les noeuds inclus dans $T$ et ceux non).

À chaque étape :
- on ajoute à $T$ un crossing edge de poids minimal par rapport au cut induit par $T$.

![[image-53.png]]

- $pi$ quel est le noeud voisin de $u$ dans $T$ qui est à une distance $u."key"$

Au début on dit que chaque vertices est à une distance infinie de $T$ et qu'il n'a pas de voisin.
Puis on prend un $r$ au hasard et on dit que sa distance à $T$ est 0. Puis, tant que $Q$ n'est plus vide, on boucle sur tous les vertices, on prend le minimum $m$.
Pour chaque noeud voisin à ce nouveau minimum, on met à jour sa distance à $T$ (peut-être que le voisin est plus près de $m$, ou pas, que le noeud précédent).
![[image-54.png]]

### Kruskal's algorithm

![[image-55.png]]


## Shortest paths

Entrée : 

On autorise les edges avec des valeurs négatives (par exemple des différences d'altitude).

### Bellman-Ford algorithm

Loop invariant: après `i` itérations de la boucle principale ($0 ≤ i < |V| - 1$), toute distance `dist[v]` correspond à la longueur d’un chemin le plus court composé d’au plus `i` arêtes.

### Dijkstra's algorithm

Si on essaye de lancer Prim's comme d'ha

## Probabilistic analysis and randomized algorithms

* utile pour ne pas toujours tomber dans le pire cas (et éviter les attaques)


#### The Hiring problem

On recrute une personne si elle est plus grande que la plus grande personne qu'on a déjà embauché. Le pire cas c'est s'ils arrivent tous en ordre croissant : on va tous les embaucher.

Quel est le nombre d'embauches qu'on va faire parmis toutes les permutations des candidats ?

![[assets/image-91.png|473x278]]

![[assets/image-92.png|421x385]]


## k smallest numbers in an array

$O(n log n)$ : on trie le tableau, puis on prend les k premiers.

- sélectionner un pivot aléatoire de la liste
- calculer $S, L$, les ensembles :
	- strictements inférieurs au pivot
	- égaux au pivot
	- strictement supérieurs au pivot
- si $|S| < k$, on sait que tous les éléments qu'on cherche sont dans $S$
- sinon ils sont dans $L$

![[assets/image-168.png]]