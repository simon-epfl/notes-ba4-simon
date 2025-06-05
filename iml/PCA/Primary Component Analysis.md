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
