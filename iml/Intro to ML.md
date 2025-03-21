## Norms

$L_1$ Manhattan distance : $sum |x_d - x_d|$.
$L_2$ Euclidean distance : $sqrt(sum (x_d - x quote.single_d))^2$

## KNNs (K Nearest Neighbors)

#### Un algo simple

On prend le voisin le plus proche et on le choisit comme résultat.

**Voronoi cells** : on créé des cellules autour de chaque point de telle sorte à ce qu'on puisse voir visuellement.
![[assets/norms.png]]

#### K-nearest neighbors

- on trouve les k voisins les plus proches
- on prend la majorité parmis ces voisins pour décider
### Entraînements et ensemble de tests

On définit toujours un ensemble de test pour juger les performances du modèle, et un ensemble d'entraînement pour faire apprendre au classificateur.

On veut toujours choisir le bon degré de "conformisation aux données d'entraînement". On ne veut pas que le modèle ne puisse que reconnaisse que les données d'entraînement mais qu'il se rapproche de la courbe réelle.

![[assets/overfitting.png]]
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


## Modèles linéaires

On a deux types de modèles linéaires.
### Modèle de régression linéaire (le plus simple)

Utilisés pour prédire une valeur continue, par exemple pour prédire le prix d'une maison en fonction de ses caractéristiques.

$$ y = a_0 + a_1 x_1 + ... + a_i x_i$$
$y$ est la valeur de sortie, $x_i$ est la $i$ème feature, $a_i$ est le poids associé à la $i$-ème feature.

**Comment déterminer les paramètres du modèle ?**

Notre fonction de loss est une fonction de distance entre le $y_"pred"$ trouvé et le $y_"ground"$ :
$$ "Loss"_"MSE" = 1/m sum_(i = 1)^m (y_i - y_(i, "pred"))^2 $$
### Modèle de logistic régression binaire

Utilisés pour des problèmes de classification binaire. Par exemple,  si on veut classifier deux types de poisson à partir d'un vecteur de features comme $mat("lumière"; "taille")$.

On applique la fonction sigmoïde :
$$ p(y = 1|x_1, x_2, ..., x_i) = 1/(1 + e^(-(a_0 + a_1 x_1 + ... + a_i x_i)) $$
Et on détermine $$ y_"pred" = cases(1 "si" p(y = 1|x) >= 0.5, 0 "sinon")$$
**Comment déterminer les paramètres du modèle ?**

Ici on utilise la fonction de loss d'entropie croisée ! En fait, elle vient de ce qu'on a vu en probabilités et statistiques avec la méthode du likelihood :

> [!question] d'où vient la cross entropy loss ?
> 
> On a donc deux coins, deux distributions :
> - le vrai coin **1**, avec comme distribution $1/2$, $1/2$
> - notre coin modélisé **2**, qui cherche à se rapprocher de la distribution du coin 1 (parce qu'on ne connaît pas la distribution du coin **1** bien sûr, on cherche à s'en rapprocher à partir de ce qu'on observe). On définit au début nos poids à $0.55$, $0.45$ par exemple.
>  
>  Avec des données d'entraînement, comme l'observation `H H T H T`, on peut calculer :
>  $$ t = P("observation" | "vrai coin")/P("observation" | "coin modélisé") = P_"v"/P_"c" = (p_1^(N_H) dot p_2^(N_T))/(q_1^(N_H) dot q_2^(N_T)) $$
>  avec $p_1, q_1$ la probabilité d'avoir un head avec le coin 1 et le coin 2 respectivement et même chose pour $p_2, q_2$ pour tail, puis $N_H, N_T$ le nombre de head et tail observés respectivement.
>  
>  On normalise $T = (P_"v"/P_"c")^(1/n)$ puis on applique le log : $T_"log" = 1/n log(P_"v"/P_"c")$, puis les prop du log :
>  $$ T_"log" = N_H/N log(p_1) + N_T/N log(p_2) - N_H/N log(q_1) - N_T/N log(q_2) $$
>  
>  Là, on peut faire la simplification suivante : avec $N$ qui va à l'infini $N_H/N$, va être très près de la vraie probabilité d'avoir un head, et pareil pour $N_T/N$ donc :
>  $$ lim_((N, N_H, N_T) -> infinity) T_"log" = p_1 log(p_1) + p_2 log(p_2) - p_1 log(q_1) - p_2 log(q_2) $$
>  Et en réarrageant les termes :
>  $$ lim_((N, N_H, N_T) -> infinity) T_"log" = p_1 log(p_1/q_1) + p_2 log(p_2/q_2) = D_(K L) (P | | Q) = sum_i P(i) log(P(i)/Q(i)) $$
> 
> > [!question] Pourquoi $D_(K L )$ est une bonne mesure de la distance ?
> > C'est une bonne mesure de la distance entre les deux distributions $P$ et $Q$.
> > - Si les deux sont exactement égales, le ratio sera de **1** et le log sera égal à zéro.
> > - Si $Q$ est très différent de $P$, alors forcément, certains $q_i$ seront plus petits que
> >   certains $p_i$, ce qui fera augmenter très fortement la somme (en effet les termes de $q_i$ un peu plus grand que ceux de $p_i$, eux, diminuent moins la somme à cause de la forme du $log$). c'est pour ça d'ailleurs que $D_(K L) >= 0$ !
> >   
> >   $$ D_(K L) (P | | Q) = sum_i ​P(i)log(Q(i)/P(i)) ​>= log (sum_i ​P(i) dot Q(i)/P(i))​ \ = log sum_i P(i)= log 1 = 0 $$
> >   
 > ![[image-35.png|198x71]]
>  
>  > [!info] tout ce à quoi on vient d'arriver tient aussi avec plus de deux classes !
> 
> Nous on veut donc minimiser cette distance $D_(K L)$.
> 
> $$ D_(K L) (P_"true" | P_"pred") = sum_y P_"true" (y | x_i) log((P_"true" (y | x_i))/(P_"pred"(y | x_i ; " " theta))) \ = sum_y P_"true" (y | x_i) log(P_"true" (y | x_i)) - P_"true" (y | x_i) log(P_"pred" (y | x_i ; " " theta)) $$
> 
> Or ici tout le premier terme est inutile, il ne dépend pas de $theta$ !
> 
> On retrouve donc $$ "argmin"_theta D_(K L) (P_"true" | | P_"pred") = "argmin"_theta - sum_y P_"true" (y | x_i) log(P_"pred" (y | x_i; " " theta)) $$
> 
> La formule de l'entropie croisée ! 
#### Revenir à l'idée de base

On décide d'utiliser une ligne droite $C$ et on cherche les constantes $w_x, w_y$ telles que donnés $b, l$ , on puisse trouver de bons $-1$ et $1$ en appliquant $y$. Plus tard, on va utiliser une sigmoid pour prédire une probabilité et non plus seulement $-1$ et $1$.

![[image-8.png]]

**Rappel définition d'une ligne en 2D**:
![[image-10.png|499x255]]
On peut la normaliser en posant $a^2 + b^2 = 1$. Cela rend le vecteur normal plus simple.

![[image-11.png|511x392]]

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


![[image-14.png|385x294]]

![[image-15.png|396x263]]

Sensitive to outliers. We have to accept that some points get missclassified.
On préfère la sélection du bas !

![[image-43.png|409x251]]

On définit la marge comme ceci. On veut maximiser la marge, quitte à ignorer quelques outliers. La regression logistique ne garantie pas du tout ça.

#### Un problème + simple : supposons pas d'outliers, maximisons la marge

Étant donné un training set $$ {(x_n, t_n)} " avec" t_n in {-1, 1}$$ et une solution telle que $$ forall n, t_n (w dot x_n) >= 0 $$On peut écrire la distance à la décision boundary non signée :
$$ d_n = t_n (w dot x_n)/(||omega||) $$
$$w* = "argmax"_w min(t_n dot (w dot x)/(||w||))$$

Un problème équivalent est : (preuve dans le cours ?)
$$ w* = "argmin"_w 1/2 ||w||^2 $$

![[image-44.png]]

![[image-45.png]]

Avec un grand C on pénalise les miss classifications.

![[image-46.png]]
### Modèle de logistic regression multiclass

On peut soit utiliser $D_(K L)$ soit softmax. 

## Que faire quand on a des données non séparables linéairement ?

On peut combiner des classifiers linéaires.

![[image-47.png]]
![[image-49.png]]
![[image-52.png]]
![[image-53.png]]


## Mesurer les performances d'un modèle

### Matrice de confusion

C'est un tableau qui compare les prédictions par rapport aux valeurs réelles.

|              | **Prédit : 0**          | **Prédit : 1**          |
| ------------ | ----------------------- | ----------------------- |
| **Réel : 0** | **TN** (Vrais Négatifs) | **FP** (Faux Positifs)  |
| **Réel : 1** | **FN** (Faux Négatifs)  | **TP** (Vrais Positifs) |
### Précision

Répond à la question : **"Parmi les prédictions positives du modèle, combien sont correctes ?"**

$$ "Précision = " = "# true positive"/("# true positive" + "# true negative") $$

### Accuracy

Le **recall** (ou **sensibilité**) est une métrique qui mesure la capacité d’un modèle à identifier correctement les **cas positifs**.

$$ "exactitude" = "# vraies prédictions"/"# total des prédictions"$$|**Métrique**|**Formule**|**Question qu'elle répond**|**Quand l'utiliser ?**|
|---|---|---|---|

|               |                                                            |                                                             |                                                                                             |
| ------------- | ---------------------------------------------------------- | ----------------------------------------------------------- | ------------------------------------------------------------------------------------------- |
| **Précision** | $$(T P)/(T P + F P)$$​                                     | "Parmi les prédictions positives, combien sont correctes ?" | Quand les **faux positifs** sont coûteux (ex : filtrage de spam, faux diagnostics médicaux) |
| **Accuracy**  | $$"# prédictions correctes"/("# total des prédictions")$$​ | "Globalement, combien de prédictions sont correctes ?"      | Si les classes sont **équilibrées** (ex : reconnaissance faciale)                           |
| **Recall**    | $$(T P)/(T P + F N)$$​                                     | "Parmi tous les vrais positifs, combien ont été détectés ?" | Quand les **faux négatifs** sont critiques (ex : détection de maladies, sécurité)           |
Le **F1 Score** est une moyenne harmonique entre la précision et le recall, ce qui signifie qu’un modèle avec une précision très élevée mais un recall faible (ou inversement) aura un **F1-score faible**. 

$$ F_1 = 2 dot ("Précision" dot "Recall")/("Précision + Recall") $$

### MSE Loss function

$$ "MSE" = 1/N sum_(i = 1)^(N_t) (y_"pred-i" - y_i)^2 $$
Comment le dériver ?
$$ L = 1/N sum_i (X W - Y)_i^2 \ = 1/N sum_i (X W - Y)_i^T (X W - Y)_i \ => nabla_W L = 1/N X^T (X W - Y) $$