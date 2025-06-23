## Supervisé vs Non Supervisé

Supervised : on donne à l'algo une série d'input / output attendus

## Fonctions

Sigmoid: $RR -> [0, 1]$
$$ 1 / (1 + e^(-x)) $$
Softmax c'est la même chose mais ça généralise l'idée quand on veut que $K$ classes, sommées, donnent 1.

Chaque $"softmax(z)"_i in [0, 1]$ et $sum_(i = 1)^k "softmax"(z)_i = 1$.
$$ exp(z_i)/(sum_(j = 1)^K exp(z_j)) $$
## Différentes normes

$L_1$ Manhattan distance : $sum |x_d - x quote.single_d|$.
$L_2$ Euclidean distance : $sqrt(sum (x_d - x quote.single_d)^2)$

$$L_p "distance" = (sum_(k = 1)^K |x_i^((k)) - x_j^((k))|^p)^(1/p) $$

## Entraînements et ensemble de tests

On définit toujours un ensemble de test pour juger les performances du modèle, et un ensemble d'entraînement pour faire apprendre au classificateur.

On veut toujours choisir le bon degré de "conformisation aux données d'entraînement". On ne veut pas que le modèle ne puisse que reconnaisse que les données d'entraînement mais qu'il se rapproche de la courbe réelle.

![[overfitting.png|291x259]]
## Cross-validation

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

