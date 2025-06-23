### Définition

- on a une fonction de loss, mais on ne peut pas trouver son minimum directement
- on dérive, puis on calcule $"step_size" = "dérivée" * "learning rate"$
- on se déplace dans cette direction

Comme ça, on fait des "baby step" quand on est proche de la solution, puis de grosses steps quand la dérivée est élevée. On s'arrête quand la step size est très proche de zéro.

![[image-56.png|379x182]]

![[image-95.png|527x277]]

exemple d'une cost function avec 2 weights, on essaye de trouver le minimum
la cost function est donc une fonction qui prend les weights en entrées, la run sur le modele et donne un nombre (l'erreur) pour chaque paire.

> [!tip] Hyperparamètre à bien choisir : le learning rate
> 
> si trop petit, ça va prendre trop de temps, si trop grand, ça va diverger
> 
> ![[image-57.png|340x153]]
> ![[image-58.png|347x179]]
> 
> Pour trouver la bonne learning rate, on utilise Grid search.

> [!danger] La descente de gradient ne donne pas toujours la bonne solution!
> 
> ![[image-58.png|347x179]]
> 
> Dans certains cas, on ne va jamais converger vers la bonne solution! Heureusement, la fonction de loss pour une linear regression est convexe (comme $x^2$)! donc on trouvera la bonne solution.

> [!tip] Normaliser les features pour gagner du temps!
> ![[image-60.png]]
> 
> En fonction du scaling des features, on peut arriver plus ou moins vite au résultat (voir l'image).

La fonction n'a pas besoin d'être différentiable partout, juste la ou on veut l'optimiser.
#### Batch (or full) gradient descent

> [!question] Comment l'implémenter ?
> 
> ![[image-61.png]]
> 
> $$ y_\text{pred}^{(i)} = a_0 + \sum_{j=1}^{d} a_j x_{ij} $$
$$ \text{MSE} = \frac{1}{m} \sum_{i=1}^{m} \left( y_\text{pred}^{(i)} - y_\text{true}^{(i)} \right)^2 $$
$$ \varepsilon^{(i)} = y_\text{pred}^{(i)} - y_\text{true}^{(i)} $$
$$ \text{MSE}(a_0, \dots, a_d) = \frac{1}{m} \sum_{i=1}^{m} \left( \varepsilon^{(i)} \right)^2 $$
$$ \frac{\partial \text{MSE}}{\partial a_k} = \frac{1}{m} \sum_{i=1}^{m} \frac{\partial}{\partial a_k} \left[ \left( \varepsilon^{(i)} \right)^2 \right] $$
$$ = \frac{1}{m} \sum_{i=1}^{m} \left[ 2 \varepsilon^{(i)} \cdot \frac{\partial \varepsilon^{(i)}}{\partial a_k} \right] $$
$$ = \frac{1}{m} \sum_{i=1}^{m} \left( 2 \varepsilon^{(i)} \cdot x_{ik} \right) $$
$$ = \frac{1}{m} \sum_{i=1}^{m} \left( 2 \left( y_\text{pred}^{(i)} - y_\text{true}^{(i)} \right) x_{ik} \right) $$
> 
> On calcule la dérivée partielle par rapport a chaque parametre $theta$. (la formule vient de la dérivée de MSE).
> 
> C'est lent ! on doit multiplier une matrice de la taille des samples de training
> ![[image-62.png]]

#### Conjugate Gradient Method

> [!question] Comment ça marche ?
> 
> **Le problème :**
> - on veut minimiser une fonction $f(x)$
> - la plupart du temps, $f$ est une fonction quadratique, de la forme $f(x) = 1/2 x^T A x - b^T x$, où $A$ est une matrice symétrique.
> - minimiser $f$ revient à résoudre le système linéaire $A x = b$.
>   
> **L'idée** :
> On ne peut pas calculer directement $A^(-1)$, on préfère un procédé itératif notamment quand $A$ est de grande dimension. La conjugate gradient method fait deux choses :
> - elle suit la pente, comme le gradient descent, pour trouver le minimum
> - elle évite de rebondir inutilement entre les bords de l'ellipse
>   
>**En pratique** :
>
>On définit $g_0 = - nabla f(x_0)$ et  $g_(k + 1) = - nabla f(x_(k + 1)) + beta_k g_k$ pour garder en mémoire d'où on vient et ne pas prendre une direction orthogonale.
>
>$$
> \beta_k \;=\; \frac{\|\nabla f(x_{k+1})\|_2^2}{\|\nabla f(x_k)\|_2^2}, 
>\quad
>\text{avec }
>\|\nabla f(x)\|_2^2 \;=\; (\nabla f(x))^T\,(\nabla f(x)).
>$$
>$$
>\alpha_k \;=\; \underset{\alpha}{\arg\min}\;f\bigl(x_k + \alpha\,g_k\bigr)
>\;=\; \frac{(\nabla f(x_k))^T\,\nabla f(x_k)}{\,g_k^T\,A\,g_k\,}.
>$$
>$$
>x_{k+1} \;=\; x_k \;+\; \alpha_k \, g_k.
>$$
>
>Preuve:
>![[image-167.png|445x448]]

![[image-166.png|232x335]]

#### Lagrangian optimization

> [!question] Comment ça marche ?
> 
> On veut trouver le $x$ qui minimise $f(x)$.
> 
> On a des contraintes $g_i (x) <= 0$, pour $i = 1,...,M$.
> Et des contraintes $h_i (x) = 0$, pour $i = 1, ..., P$.
> 
> On calcule le lagrangien : 
> $$ L(x, lambda, nu) = f(x) + sum_(i = 1)^M lambda_i g_i (x) + sum_(i = 1)^P nu_i h_i (x) $$
> avec $lambda_i >= 0$ et $nu_j in RR$.
> 
> On utilise le Lagrangien pour construire les conditions de Karush-Kuhn-Tucker (KKT):
> - $nabla_x​ L(x^∗,lambda^∗,nu^∗)=0$  car on veut avoir $nabla f (x) = - lambda_1 nabla g_1 + ...$ etc. (comme toujours le gradient de la fonction et de la contrainte doivent être paralleles au min/max -- penser a rejoindre le soleil sous un lac gelé)
> - $g_i (x^*) <= 0$ (dans tous les cas, c'est notre contrainte de base)
> - $h_i (x^*) = 0$ (pareil)
> - $lambda_i^* >= 0$ (seulement les $lambda$ pas les $nu$)
> > [!question] Pourquoi ?
> > en fait cette contrainte vient du fait qu'on veut que le gradient de $f$ et des $g$ soient non seulement paralleles, mais plus précisément **opposés** (par exemple si le gradient de $f$ est vers le haut, on veut minimiser $f$ et donc aller vers le bas, mais le gradient de $g$ est vers le bas, donc si on descend plus on ne satisfait plus la contrainte $g >= 0$!). Si ce n'était pas le cas, on pourrait trouver un meilleur minimum!
> - $lambda_i^* g_i (x^*) = 0$
> > [!question] Pourquoi ?
> > 
> > Voir plus haut. Soit on est dans le cas ou effectivement cette contrainte $g$ est active, on la pousse au bout du bout jusqu'a ce que le gradient de $f$ soit égale a quelque chose fois le gradient de $g$ soit la contrainte n'est pas active (car une autre est plus forte par exemple).
> > ![[telegram-cloud-photo-size-4-5915969657129518304-y.jpg|349x432]]
>   
> **Version duale :**
> 
> On résout $max_(lambda >=0) min_w L(w, lambda)$
> 
> > [!tip] En attendant d'avoir + d'intuition
> > 
> > Il faut comprendre que si une contrainte est active (nous empêche d'aller plus loin pour faire diminuer $f$, alors son coefficient $lambda$ sera supérieur à 0, sinon il sera égal à $0$ et la contrainte sera inactive).
