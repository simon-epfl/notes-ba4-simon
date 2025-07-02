## Modèles linéaires

On a deux types de modèles linéaires.
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

$$ "Précision = " = "# vrais positifs"/("# vrais positifs" + "# faux négatifs") $$
![[assets/image-164.png|254x447]]
### Accuracy

Le **recall** (ou **sensibilité**) est une métrique qui mesure la capacité d’un modèle à identifier correctement les **cas positifs**.

$$ "exactitude" = "# vraies prédictions"/"# total des prédictions"$$

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

![[assets/image-33.png]]

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


