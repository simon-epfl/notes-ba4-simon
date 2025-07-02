### Cross-entropy

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


### Supervisé vs non supervisé

Supervised : on donne à l'algo une série d'input / output attendus
### Fonctions

Sigmoid: $RR -> [0, 1]$
$$ 1 / (1 + e^(-x)) $$
Softmax c'est la même chose mais ça généralise l'idée quand on veut que $K$ classes, sommées, donnent 1.

Chaque $"softmax(z)"_i in [0, 1]$ et $sum_(i = 1)^k "softmax"(z)_i = 1$.
$$ exp(z_i)/(sum_(j = 1)^K exp(z_j)) $$
### Différentes normes

$L_1$ Manhattan distance : $sum |x_d - x quote.single_d|$.
$L_2$ Euclidean distance : $sqrt(sum (x_d - x quote.single_d)^2)$

$$L_p "distance" = (sum_(k = 1)^K |x_i^((k)) - x_j^((k))|^p)^(1/p) $$

### Entraînements et ensemble de tests

On définit toujours un ensemble de test pour juger les performances du modèle, et un ensemble d'entraînement pour faire apprendre au classificateur.

On veut toujours choisir le bon degré de "conformisation aux données d'entraînement". On ne veut pas que le modèle ne puisse que reconnaisse que les données d'entraînement mais qu'il se rapproche de la courbe réelle.

![[overfitting.png|291x259]]
### Cross-validation

1. On divise le dataset en **k sous-ensembles** (appelés _folds_).
2. Pour chaque itération :
    - On prend **k−1 folds pour entraîner** le modèle.
    - On utilise le **fold restant pour tester**.
3. On répète cela **k fois** (chaque fold sert une fois de test).
4. On **moyenne les scores** obtenus (accuracy, F1-score, etc.).

> [!tip] Avantages
> 
> - Donne une **meilleure estimation** de la performance du modèle.
> - Réduit le **risque de surajustement à un seul jeu de test**.
> - Utile quand on a **peu de données**.

> [!danger] Inconvénients
> 
> - **Coût computationnel élevé** (surtout pour grands modèles).
> - Plus complexe à implémenter que juste train/test split.

### Mesurer les performances d'un modèle

#### Matrice de confusion

C'est un tableau qui compare les prédictions par rapport aux valeurs réelles.

|              | **Prédit : 0**          | **Prédit : 1**          |
| ------------ | ----------------------- | ----------------------- |
| **Réel : 0** | **TN** (Vrais Négatifs) | **FP** (Faux Positifs)  |
| **Réel : 1** | **FN** (Faux Négatifs)  | **TP** (Vrais Positifs) |
### Précision

Répond à la question : **"Parmi les prédictions positives du modèle, combien sont correctes ?"**

$$ "Précision = " = "# vrais positifs"/("# vrais positifs" + "# faux négatifs") $$
![[assets/image-164.png|254x447]]
#### Accuracy

Le **recall** (ou **sensibilité**) est une métrique qui mesure la capacité d’un modèle à identifier correctement les **cas positifs**.

$$ "exactitude" = "# vraies prédictions"/"# total des prédictions"$$

|               |                                                            |                                                             |                                                                                             |
| ------------- | ---------------------------------------------------------- | ----------------------------------------------------------- | ------------------------------------------------------------------------------------------- |
| **Précision** | $$(T P)/(T P + F P)$$​                                     | "Parmi les prédictions positives, combien sont correctes ?" | Quand les **faux positifs** sont coûteux (ex : filtrage de spam, faux diagnostics médicaux) |
| **Accuracy**  | $$"# prédictions correctes"/("# total des prédictions")$$​ | "Globalement, combien de prédictions sont correctes ?"      | Si les classes sont **équilibrées** (ex : reconnaissance faciale)                           |
| **Recall**    | $$(T P)/(T P + F N)$$​                                     | "Parmi tous les vrais positifs, combien ont été détectés ?" | Quand les **faux négatifs** sont critiques (ex : détection de maladies, sécurité)           |
Le **F1 Score** est une moyenne harmonique entre la précision et le recall, ce qui signifie qu’un modèle avec une précision très élevée mais un recall faible (ou inversement) aura un **F1-score faible**. 

$$ F_1 = 2 dot ("Précision" dot "Recall")/("Précision + Recall") $$
