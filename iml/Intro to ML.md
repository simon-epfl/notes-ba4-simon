## Norms

$L_1$ Manhattan distance : $sum |x_d - x_d|$.
$L_2$ Euclidean distance : $sqrt(sum (x_d - x quote.single_d))^2$

## KNNs (K Nearest Neighbors)

#### Un algo simple

On prend le voisin le plus proche et on le choisit comme résultat.

**Voronoi cells** : on créé des cellules autour de chaque point de telle sorte à ce qu'on puisse voir visuellement.
![[norms.png|596x466]]

#### K-nearest neighbors

- on trouve les k voisins les plus proches
- on prend la majorité parmis ces voisins pour décider
### Entraînements et ensemble de tests

On définit toujours un ensemble de test pour juger les performances du modèle, et un ensemble d'entraînement pour faire apprendre au classificateur.

On veut toujours choisir le bon degré de "conformisation aux données d'entraînement". On ne veut pas que le modèle ne puisse que reconnaisse que les données d'entraînement mais qu'il se rapproche de la courbe réelle.

![[overfitting.png|438x390]]
#### Améliorer son dataset

##### Data reduction

On veut absolument réduire le nombre de données de notre ensemble de données quand on applique les K-NN parce qu'on doit à chaque fois comparer avec **tous** les voisins. Pour ça on choisit des représentants (des **prototypes**). Mais il y a plusieurs techniques pour faire ça :
- avec le centre de gravité (mais ça ne marche pas tjrs, par exemple si on a un cercle rouge entouré par un cercle vert, ils ont le même centre de gravité !)
- avec l'algorithme des **condensed** nearest neighbors (de meilleurs frontières **et** plus rapide à exécuter car moins de comparaisons) :
	- on a un training set 1, 2, (bleu) 3, 4, (rouge) 5 (vert).
	- On initialise `P = {1}` (random).
	- Ensuite, on choisit p. ex. le 2. Le plus près de 2 dans P est 1, qui a la même classe, donc on jette le 2.
	- On choisit le 3. Quel est le plus près du 3 dans `P` ? C'est 1, qui a une classe différente, donc on garde C.
	- On choisit le 4. Quel est le plus près du 4 dans `P` ? C'est 3, qui a une classe indentique, donc on jette 4.
	- etc. cet algo n'a pas toujours de sens.
##### Normalisation

Vous appliquez le KNN à un dataset comme ceci : 
• Age: Ranges from 0 to 100
• Income: Ranges from $0 to $1,000,000
• Binary Gender: Encoded as 0 or 1

S'il y a une diff de $1000 entre A et B, le modèle va considérer ça plus important qu'une diff de 20 ans entre les deux ! On doit donc normaliser (garder la même distribution mais faire un rescaling).
##### Corriger unbalanced dataset

- on peut enlever des points pour rétablir l'équilibre
- on peut ajouter un poids plus fort aux points 
- on peut ajouter des points synthétiques pour compenser

### Greedy k-NN Graph construction

Idea: connect everyone to a few people (randomly) and look at friends of friends.
p. exemple :
- on connecte Alice à 3 étrangers.
- on regarde dans les amis des amis d'Alice et on compute leur similarity score.
- on prend les premiers et on créé un nouveau "voisinage" à partir de ça.
- et on répète tant que le nombre de changements est $>epsilon$.
## K-means

- un cluster est un ensemble de points ${x_(i_1^k), ..., x_(i_(n^k)^k)}$
- $mu_k$  est le centre de masse du cluster $k$

Nous voulons que les distances entre les points au sein d'un cluster soient petites et que les distances entre les clusters soient larges.

$$"on veut minimiser : " sum_(k = 1)^K sum_(j = 1)^(n_k) (x_(i_j)^k - mu_k)^2$$
**Comment trouver les centres de masse** ?

- on initialise les centres de masse à une position aléatoire
- jusqu'à ce que ça ne change plus
	- on assigne chaque point au centre de masse le plus proche (en calculant la distance euclidienne -- un point ne peut être associé qu'à un centre de masse)
	- on met à jour chaque $mu_k$ en fonction de la moyenne des points associés

$arrow$ ça ne marche pas toujours! on doit essayer avec plusieurs seeds (plusieurs positions aléatoires au début) et prendre celle qui à le meilleur résultat en termes de distance au carré


## lin mod / class

On veut classifier deux types de poisson à partir d'un vecteur $mat("lumière"; "taille")$

On décide d'utiliser une ligne droite $C$ et on cherche les constantes $w_x, w_y$ tel que donnés $b, l$ , on puisse trouver de bons $-1$ et $1$ en appliquant $y$.

![[image-8.png]]

**Rappel définition d'une ligne en 2D**:
![[image-10.png]]
On peut la normaliser en posant $a^2 + b^2 = 1$. Cela rend le vecteur normal plus simple.

![[image-11.png]]


### Perceptron

Nous voulons minimiser : $$ E(\tilde{w}) = - \sum_{n = 1}^{N} sign(\tilde{w} \cdot \tilde{x_n}) t_n $$
où $t_n$ est la vraie valeur.

**Comment ?**
- commencer par définir $\tilde{w}_1$ à 0.
- de façon itérative, choisir un indice $n$
	- si $x_n$ est correctement classifié, ne rien faire.
	- sinon, $\tilde{w}_{t + 1} = \tilde{w_t} + t_n \tilde{x_n}$

**Centered perceptron** : on shift tous nos points de telle sorte à ce que notre décision boundary passe par l'origine.

**Convergence Theorem** : dans un problème de classification, s'il existe une marge $gamma$ telle qu'on ait une classification parfaite, le perceptron algorithm fait au plus $R^2/gamma^2$ erreurs (avec $R = max(|x_n|)$ ).

Parfois, pour un $gamma$ très petit ou quand la classification ne peut pas être parfaite, on ne doit pas aller point par point dans l'ordre vérifier s'il est correctement classifié, mais les vérifier de façon **aléatoire**.

Un problème avec le perceptron, c'est qu'on dit que le résultat est $-1$ ou $1$. Donc l'algorithme considère que ces deux résultats sont équivalents, de même que la ligne en diagonale qui serait bien meilleure :

![[image-12.png|267x219]]

Ce qu'il faudrait, c'est avoir une fonction plus smooth :

![[image-13.png|416x225]]

On veut minimiser la cross-entropy :
$$ E(w) = - sum_n {t_n ln y_n + (1 - t_n) ln(1- y_n)} $$
avec $y_n = y(x_n; w)$.

![[image-14.png|385x294]]

![[image-15.png|396x263]]

Sensitive to outliers. We have to accept that some points get missclassified.
