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
 > ![[assets/image-35.png|198x71]]
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

![[assets/image-8.png]]

**Rappel définition d'une ligne en 2D**:
![[assets/image-10.png|499x255]]
On peut la normaliser en posant $a^2 + b^2 = 1$. Cela rend le vecteur normal plus simple.

![[assets/image-11.png|511x392]]

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

![[assets/image-12.png|267x219]]

Ce qu'il faudrait, c'est avoir une fonction plus smooth :

![[assets/image-13.png|416x225]]


![[assets/image-14.png|385x294]]

![[assets/image-15.png|396x263]]

Sensitive to outliers. We have to accept that some points get missclassified.
On préfère la sélection du bas !

![[assets/image-43.png|409x251]]

On définit la marge comme ceci. On veut maximiser la marge, quitte à ignorer quelques outliers. La regression logistique ne garantie pas du tout ça.

#### Un problème + simple : supposons pas d'outliers, maximisons la marge

Étant donné un training set $$ {(x_n, t_n)} " avec" t_n in {-1, 1}$$ et une solution telle que $$ forall n, t_n (w dot x_n) >= 0 $$On peut écrire la distance à la décision boundary non signée :
$$ d_n = t_n (w dot x_n)/(||omega||) $$
$$w* = "argmax"_w min(t_n dot (w dot x)/(||w||))$$

Un problème équivalent est : (preuve dans le cours ?)
$$ w* = "argmin"_w 1/2 ||w||^2 $$

![[assets/image-44.png]]

![[assets/image-45.png]]

Avec un grand C on pénalise les miss classifications.

![[assets/image-46.png]]
### Modèle de logistic regression multiclass

On peut soit utiliser $D_(K L)$ soit softmax. 

## Que faire quand on a des données non séparables linéairement ?

On peut combiner des classifiers linéaires.

![[assets/image-47.png]]
![[assets/image-49.png]]
![[assets/image-52.png]]
![[assets/image-53.png]]


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

## Arbres de décisions

- **root node** : représente la population entière et se divise en sous-ensembles
- **splitting** : diviser un noeud en plusieurs autres noeuds en se basant sur un critère
- **decision node** : quand un noeud a plusieurs enfants
- **leaf/terminal node** : quand il n'a pas d'enfants
- **pruning** : quand on enlève un decision node de l'arbre


La difficulté est de choisir les décisions rules. Pour ça, on va itérer sur toutes les décisions rules possibles, et voir l'information gagnée.

**Comment mesurer l'information gagnée ?** On peut utiliser une mesure comme Gini impurity qui va mesurer à quel point notre groupe est composée d'une classe unique (est pur).
Information gagnée : impurity du parent - impurity des enfants (weighted)

On a souvent de l'over fitting : on définit souvent un max depth.

## 🌲 2. **Random Forests**

### 🧠 Idée

Un **ensemble d’arbres de décision** construits sur des **sous-échantillons aléatoires** des données (avec remplacement, c’est le **bagging**).

![[image-33.png]]

Arrention à bien sélectionner **avec replacement**, sinon tous les arbres se ressembleraient et on ne gagnerait pas beaucoup.

Chaque arbre est différent car :
- Il est entraîné sur un jeu de données différent. (**bootstrapped dataset**)
- À chaque nœud, on ne considère qu’un **sous-ensemble aléatoire de features**.
### ✅ Avantages

- **Moins d’overfitting** que les arbres seuls.
- **Robuste** aux bruits.
- Peut estimer la probabilité d'appartenance à une classe.

Pour classifier, on demande à chaque tree de classifier et on prend le plus de votes. On aggrege les données. **Bootstrapped dataset + aggregation = bagging**.

Les données qui ne finissent dans aucun arbre s'appellent des **Out-of-Bag Datasets**. On peut mesurer l'accuracy de notre modèle en utilisant les out-of-bags dataset (on fait prédire à notre arbre les valeurs de out of bags).

---

## 🚀 3. **Gradient Boosted Trees (GBT, ou XGBoost, LightGBM)**

### 🧠 Idée

On ajoute **des arbres faibles un par un** pour corriger les erreurs du modèle précédent. C’est une approche **séquentielle**.

- À chaque étape, on construit un nouvel arbre pour prédire **les résidus (erreurs)** du modèle courant.
    
- On **ajuste progressivement**, un peu comme un apprentissage par descente de gradient.
    

### 🔧 Détails :

- On utilise un **taux d’apprentissage (shrinkage)** pour éviter l’overfitting.
    
- Très puissant, souvent **top 1 sur Kaggle**, mais plus sensible aux réglages.


## Descente de gradient

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
> On calcule la dérivée partielle par rapport a chaque parametre $theta$. (la formule vient de la dérivée de MSE).
> 
> C'est lent ! on doit multiplier une matrice de la taille des samples de training
> ![[image-62.png]]

#### Conjugate Gradient Method

> [!question] Comment ça marche ?
> 
> La méthode du gradient conjugué est une **alternative plus rapide au gradient classique** pour résoudre des **systèmes linéaires** du type $A x = b$.
> 
> Contrairement à la descente de gradient simple, elle utilise l’idée de **"directions conjuguées"**, qui sont meilleures que les directions de gradient pour atteindre le minimum en moins d’itérations. Cela garantit qu'on ne "revient jamais en arrière" sur une direction déjà optimisée.
> 

#### Lagrangian optimization

> [!question] Comment ça marche ?
> 
> Quand on optimise une fonction sous contraintes (par exemple, respecter un budget, une limite physique, etc.), certaines contraintes sont **actives** (juste au bord de ce qui est permis), et d’autres **non actives** (elles ne sont pas tendues).
> 
> par pas tendues, on veut dire qu'elle ne respecte pas exactement l'égalité, alors que si c'est le cas, pour trouver la contrainte on est obligés de se déplacer le long de la droite.
> 
> pas active => coefficients zéro.

## Multi layer perceptron MLPS

> [!tip] Activation functions
> 
>![[image-93.png|512x252]]
>
> Permet de passer d'une valeur numérique (liée a une somme d'entrées multipliées par des poids, a une valeur entre deux bornes).

> [!tip] Transition d'un layer a un autre
> 
> ![[image-94.png|598x352]]
> 
> $equiv a^(1) = sigma(W a^(0) + b)$
> etc. en boucle

> [!tip] Comment entraîner le modele ? TODO: backpropagation
> 
> https://www.youtube.com/watch?v=tIeHLnjs5U8

## CNN Convolutional Neural Networks

On utilise les CNN pour des tâches difficiles comme reconnaître une photo de maison.

> [!danger] Mais pourquoi ne pas simplement le faire avec un Artificial Neural Network ?
> 
> On aurait besoin de trop de poids, c'est juste limite pour le MNIST.

![[image-121.png|518x240]]

> [!tip] L'idée du CNN
>  
>  Contrairement au MLP, les layers des CNN ne sont pas tous connectés a chaque pixel de l'image mais qu'a une partie. Chaque neurone de la deuxième couche convolutionnelle est connecté à une petite région de la couche précédente, ce qui permet au réseau de détecter d’abord des caractéristiques simples, puis de les combiner progressivement en motifs plus complexes. Cette structure hiérarchique, similaire à celle des images réelles, rend les CNN particulièrement efficaces pour la reconnaissance d’images.

> [!tip] Filtres et feature maps
> 
> Les poids d’un neurone dans une couche convolutionnelle peuvent être vus comme une petite image (matrice) de la même taille que son **champ réceptif** (receptive field).
> 
> Par exemple un filtre de **7×7** avec **des 1 au centre vertical** détectera uniquement les **lignes verticales**.
> 
> Dans une couche convolutionnelle, tous les neurones appliquent plusieurs filtres en parallees. mais elles partagent **tous** les mêmes poids pour chaque filtre ! Chaque neurone, pour chaque filtre :
>- Regarde une petite région de l’image (le **champ réceptif**),
>- Applique **le même filtre** (les mêmes poids),
>- Produit **une valeur** qui dit : _« est-ce que le motif que je cherche est présent ici ? »_ 
>  
>Ce partage des poids rend le modele beaucoup plus petit.
> 
>Le résultat est appelé une **carte de caractéristiques** (_feature map_), qui montre les endroits de l’image où le filtre détecte quelque chose d’important.

Pas besoin de programmer manuellement ces filtres :
- Pendant **l’entraînement**, le réseau apprend **tout seul** quels filtres sont les plus utiles pour la tâche (comme la reconnaissance d’image).
- Les couches supérieures du réseau vont alors combiner ces filtres simples (lignes, bords...) pour reconnaître des motifs plus complexes (formes, objets...).

![[image-122.png]]

Formule de la convolution (sur les)
![[image-123.png]]

![[image-125.png|546x299]]

- **Stride** $s$ : nombre de pixels à sauter entre chaque application du filtre
- **Padding** $p$ : nombre de pixels à ajouter autour de l’image pour gérer les bords

![[image-126.png]]

Les 2p c'est parce qu'on ajoute p pixels en haut, et p pixel en bas. H_in - H_k parce que plus le filtre est grand plus on doit commencer loin du bord pour être dans une plage valide.

> [!question] Calculer le nombre d'opérations ?
> 
> Chaque output pixel est le résultat d'une convolution (c'est-a-dire du dot product entre une région de taille $H_K​ dot W_K​ dot C_"in"$ et un noyau de la même taille), et il faut le faire pour chaque pixel de sortie soit $H_K​ dot W_K​ dot C_"in" dot H_"out"​ dot W_"out" dot C_"out"$ multiplications.
> 
> Si on veut comparer avec un fully-connected layer, ou la taille du kernel est la taille de l'image, on voit que c'est bien plus petit.

> [!tip] average pooling
> 
> L'**Average pooling** consiste à **diviser l'image en petites régions (souvent carrées)** et à **calculer la moyenne des valeurs** dans chacune de ces régions.
> 
> **Max pooling** divise une image (ou carte de caractéristiques) en petits blocs (ex. 2×2) et **retient uniquement la valeur maximale** de chaque bloc.

# Transformers

![[image-151.png]]

### Étape 1 : séparer en chunks "flattening" et transformer ces chunks (tokens) en embeddings

Prendre une image, une phrase, etc. ou autre et "l'aplatir", la transformer en petits chunks (généralement des syllables, mots, etc. ou petites parties d'images).

texte : chunks sont appelés tokens
image : chuncks sont appelés patches

Ensuite, on prend chaque chunk, et on obtient un vecteur à partir de la **embedding matrix** (qui contient déjà un mapping 1-1 entre chaque token et son embedding, c'est une look-up table).

Cette matrice contient donc $n_"dimensions" * n_"mots"$ paramètres.

Context size : le nombre de tokens, chunks, que peut prendre le transformer.

![[image-152.png|618x342]]

Une **direction** dans l'espace correspond à un genre, à la pluralité du mot, la taille par exemple, etc.  On parle bien de **direction** et non pas de **dimension**, il n'y a pas une dimension liée à chaque critère !

> [!danger] aux vecteurs d'embeddings sont ajoutés des informations à propos de la position des éléments dans la phrase.
> 
> en fait on a des embeddings pour chaque position et on fait embedding mot + embedding position. De même que pour les critères de genre, pluralité, etc., on a une direction pour la position du mot dans la phrase.

> [!tip] Exemple de positional embedding
> 
> ```python
> def get_positional_embeddings(sequence_length, d):
>  result = torch.zeros(sequence_length, d)
>  for i in range(sequence_length):
>     for j in range(d // 2):
>         angle = i / (10000 ** (2 * j / d))
>         result[i, 2 * j] = torch.sin(torch.tensor(angle))
>         result[i, 2 * j + 1] = torch.cos(torch.tensor(angle))
> return result
>```
>
>`sequence_length` c'est le nombre de tokens et `d` c'est le nombre de dimensions. Pour chaque embedding, on remplit les dimensions paires avec 

### Étape 2 : phase d'attention, partage de contexte entre les différents tokens

On veut une façon d'ajuster l'embedding des mots en fonction des autres mots à côté. Par exemple il y a sans doute une position dans l'espace qui correspond exactement à "tour eiffel", et "tour" est mal positionné au début.

**Q**ueries : les questions que le token se pose. pour la calculer, on a une matrice $W_Q$ qu'on multiplie à l'embedding. 
**K**eys : une sorte de FAQ proposée par le token. de même, on multiplie $W_K$ avec l'embedding.
**V**alues : les réponses à chaque question mise dans la FAQ (parce que les réponses ne sont pas forcément proches de la question !)

le nombre de dimensions de $W_K$ et $W_Q$ est bien plus petit que celui le nombre de dimensions des embeddings.

![[image-153.png|589x345]]

On va faire le dot product entre la query de chaque embedding et les keys des autres mots, et si on a un grand nombre alors ces mots sont sans doute intéressant.

On va donc mapper tous ces dot-products alors entre 0 et infinity entre 0 et 1 avec une fonction de softmax (qui s'applique sur chaque colonne parce que la somme de chaque **colonne** doit faire 1), puis les mutiplier par leur $V$ pour obtenir une weighted sums des réponses les plus intéressantes.
Ensuite, on ajoute ce vecteur $"softmax"(K^T Q) V$ à notre embedding original.

![[image-154.png|671x394]]

> [!tip] masking
> 
> Quand on donne une séquence de tokens à notre GPT, et qu'on lui demande de prédire le suivant, en fait il va quand même essayer de prédire chaque token qu'on lui déjà donné (ce qui fait que quand on l'entraîne en lui disant "une créature verte mange une X", il va essayer de prédire "une créature verte X"). pour ça, on veut éviter que le modèle ait accès aux mots suivants "une créature verte" pour éviter qu'on lui spoile la réponse.
> 
> C'est pour ça qu'on "masque" les mots suivants, en modifiant, avant d'appliquer softmax sur chaque colonne, le résultat de leur dot product et en le mettant à -infinity (comme ça ça donnera 0).

> [!tip] cross attention
> 
> Ce qu'on a vu jusque-là c'était du self attention, le cross attention c'est quand on a deux types de données (par exemple une phrase source en anglais et une traduction en cours en français, ou alors un speech audio, et une transcription en cours). Les queries viennent donc de la transcription, traduction en français, et les keys/values viennent de l'audio ou de la phrase source.

> [!tip] multi-head attention
> 
> GPT 3 utilise 96 sets de queries, keys and values entraînés pour détecter et prêter attention de façon différentes aux mots autour. Chacun de ces heads proposent une update de l'embedding de base $Delta E$, et pour calculer l'embedding final on additionne tous ces changements.
### Étape 3 : multi layer perceptron

Dans cette étape, les vecteurs ne se parlent pas entre eux. On peut donc faire cette étape en parallèle pour chaque embedding.

- on multiplie notre embedding avec une matrice qui contient des paramètres (étape **linéaire**). on ajoute aussi un bias, typiquement utile pour que le résultat soit positif si la réponse est oui et négatif sinon. Chaque ligne pose une question sur l'embedding par exemple "est-ce que c'est du code ?", "est-ce que c'est de l'anglais ?", etc. 
- le problème c'est que c'est linéaire pour le moment, nous on veut une réponse "oui" ou "non". on applique donc la fonction ReLU (Rectified Linear Unit).
- ensuite, on reconstruit l'embedding en ajoutant ou non des informations en fonction de si le neurone est actif

![[image-156.png]]

par exemple ici, si le neurone $n_0$ est 1 (c'est celui qui a demandé "est-ce que l'embedding parle de Michael Jordan"), alors on ajoute à notre embedding $C_0$ qui contient les informations à propos de basketball, des chicago bulls, du numéro de maillot de Michael Jordan, etc.

![[image-157.png|635x266]]
### Étape y : on récupère une liste de probabilités pour chaque mot

On prend le dernier vecteur et on utilise un unembedding matrix + softmax pour générer les probabilités pour les mots. 
La unembedding matrix est l'inverse de la embedding matrix ?

## Primary Component Analysis

Imagine qu'on ait une liste de pays avec différentes valeurs pour le PIB, les services sociaux, l'espérence de vie, etc. On ne peut pas tout représenter sur un unique graphe. On utilise PCA pour obtenir 1, 2, ou 3 axes qui nous permettent d'obtenir une visualisation qui sépare les pays selon des critères fusionnés (par exemple, les pays "très bonne espérance de vie et très bons services sociaux" et les autres). Chaque axe suit un ordre d'importance (on fait une première séparation avec le premier axe, puis on divise en sous-groupe avec les autres axes), et est décorrelé des autres.

> [!tip] Intuitivement: la matrice de covariance
> 
> - "Quand le PIB augmente, est-ce que l’espérance de vie augmente aussi ?" → Covariance positive
> - "Quand un augmente, l’autre baisse ?" → Covariance négative
> - "Pas de lien ?" → Covariance proche de 0

> [!question] Pourquoi la matrice de covariance est utile ?
> 
> Pour cela, on veut arriver à savoir quelles variables varient ensemble, pour les rattacher à un même axe.
> 
> Au début, on veut donc prendre l'axe qui nous fait perdre le moins d'information. Quand on projete un point, $x$ sur un vecteur $\vec{u}$ on obtient un nouveau vecteur $x'= (\vec{x}^T {u})\vec{u}$.
> 
> On peut mesurer l'information préservée avec $(x^T u )^2$.
> Au début, on veut donc prendre le vecteur qui maximise l'information préservée.
> $$max "information" = max 1/n sum_i (x_i^T u)^2 = max 1/n sum_i (x_i^T u)(x_i^T u) $$
> $$ = max 1/n u^T sum_i x_i x_i^T u = max u^T C u$$
> où $C = 1/n sum_i x_i x_i^T$ est la matrice de covariance.
> 
> Cela revient à résoudre le problème (car $u^T u - 1 = 0$):
> $$ max u^T C u - lambda (u^T u  - 1) $$
> puis en différenciant :
> $$ 2 C u - 2 lambda u = 0 <=> C u  = - lambda u$$
> donc le vecteur $u$ qui préserve le plus d'information est un vecteur propre de la matrice de covariance !
> 
> Et on voit que la quantité d'information préservée ($u^T C u$) est égale à $lambda$! donc on va prendre le vecteur avec la plus grande valeur propre. Une fois qu'on a trouvé le vecteur propre (par exemple $u = [0.5, 0.6, 0.4]$), ça nous donne les poids de chaque colonne pour le graphe.

> [!question] Quelles étapes ?
> 
> 1. **Centrer les données**
>    
> On centre chaque colonne, on soustrait la moyenne de chaque variable à toutes les valeurs de cette variable. On obtient une matrice centrée de taille $n times d$.
> 
> 2. Calcul de la **matrice de covariance**
>  
> $$"Cov"(X)= 1/(n − 1) X^T_"centered" ​X_"centered"$$
> 
> Résultat : une matrice $d times d$ (une case pour chaque paire de variables).
> 
> 3. On calcule les vecteurs propres de la matrice.
>    
>    Chaque vecteur propre pointe vers une **direction importante** dans l’espace des variables (ex. une direction combinant PIB + espérance de vie).
>    Les valeurs propres disent **quelle proportion de la variance totale** est expliquée par chaque axe.



