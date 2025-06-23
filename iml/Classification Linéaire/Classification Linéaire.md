## Données linéairement séparables, Perceptron

Essaye de créer un hyperplane qui sépare les données.

On minimise :
$$ E(w) = sum_(n = 1)^N L(y(x_n; w), t_n)$$
Algorithme :
-  On définit $w_(t = 1)$ à un vecteur de zéro.
- Itérativement :
	- si $x_n$ est correctement classifié, on ne fait rien.
	- sinon, $w_(t = t+1) = w_(t) + t_n x_n$, $b_(t+1) = b_t + t_n$

> [!question] Une fois qu'on a $w$, comment décider ?
> 
> Une fois qu'on a l'équation du plan $\vec{w} \cdot \vec{x} + b = 0$ , avec $\vec{w}$ le vecteur perpendiculaire au plan, $\vec{x}$ notre point. Ensuite $f(x) = \text{sign}(\vec{w} \cdot \vec{x} + b)$ soit $\hat{y} = +1$ si $\vec{w} \cdot \vec{x} + b > 0$ sinon $\hat{y} = -1$.
> 
> On obtient donc une fonction de décision $f(x) = \vec{w} \cdot \vec{x} + b$ donc on regarde le signe pour classifier. C'est une **step function** (elle passe de 0 à 1 d'un coup).

> [!danger] 1er problème : pas d'optimisation de la marge
> 
> ![[image-170.png|494x203]]
> 
> Le perceptron n'a aucune idée de qui est le meilleur.
## Régression Logistique

Un autre problème avec le perceptron est qu'on a aucune façon de dire si on est proche ou pas de la frontière de décision.

- on remplace la step function par une sigmoïde, le modèle produit une probabilité $\hat p\in(0,1)$.
- maintenant, on minimise la **cross-entropy** (log-loss) sur le jeu de données $\{(x_n,\,t_n)\}$, où $t_n\in\{0,1\}$ :  $$L_{\mathrm{CE}}(w) 
    = -\,\sum_{n=1}^N \Bigl[t_n\,\log\bigl(\hat p_n\bigr) 
    \;+\;(1 - t_n)\,\log\bigl(1 - \hat p_n\bigr)\Bigr].$$
**(plus stable, deux fois différentiable, etc.)**

![[image-171.png|390x223]]

- comme on utilise cette cross-entropy loss, si le plan passe très près de certains points, leur probabilité d'appartenir à une classe ou l'autre va être p. exemple 60/40 du coup le modèle va être loin de la **vraie** prédiction (100/0), ce qui va quand même pénaliser le modèle, alors que le perceptron aurait été content. cela pousse le modèle à augmenter la taille de la marge.

> [!danger] Un autre problème : les outliers
> 
> On n'a pas introduit de slack variables, les outliers pénalisent beaucoup la logistic regression sur le test set.

> [!tip] Vers le multi-class
> 
> On passe de la sigmoid vers la softmax, la même chose mais généralise l'idée quand on veut que $K$ classes, sommées, donnent 1.
## Max Margin Classifier

> [!tip] On cherche à maximiser la marge, calcul de la distance d'un point à un hyperplan
> 
> La marge est définie comme $$ "marge" = min_i ("distance de" x_i "à l'hyperplan") dot I(x_i " bien classé") $$
> 
> Comment calculer la distance d'un point $\vec{x}$ à un hyperplan de vecteur normal $\vec{w}$ et de biais $b$ ?
> 
> On projette donc $\vec{x}$ sur $\frac{\vec{w}}{||\vec{w}||}$ pour obtenir sa composante selon $\vec{w}$  unitaire : $\vec{x} \cdot \frac{\vec{w}}{||\vec{w}||}$. On doit aussi ajouter le bias :
> 
> $$ d(x, "plan") = | ((w dot x + b)/(norm(w))) | $$
> 
> ![[image-161.png]]
> 
> Pour trouver $b$, si on sait que notre plan passe par le point $(3, 3, 3)$, on fait $w^T (3, 3, 3) + b = 0$, comme le point vérifie l'équation, et ainsi on trouve $b$.
> 
> On veut donc : $$\max (\text{"marge"}) = \max_{w, b} \left( \min_i \frac{y_i(w^\top x_i + b)}{\|w\|} \right)$$
> 
> Pour simplifier ce problème d'optimisation avec min-max :
> On introduit la marge **fonctionnelle** : 
> $$gamma_i^(f) = y_i (w dot x_i + b)$$
> si $gamma_i^(f) > 0$ le point est bien classé ($y_i$ étant le vrai label $+1$ ou $-1$), et plus $gamma_i^(f)$ est grand, plus la certitude est grande.
> 
> Et la marge **géométrique** réelle :
> $$gamma_i^(g) = gamma_i^(f)/norm(w)$$
> C’est la distance signée au plan (positive si point bien classé), et la marge du classifieur est typiquement $min_i gamma_i^(g)$.
> 
> Lorsque l'on fixe la marge fonctionnelle a 1 par la contrainte, alors la marge géométrique minimale vaut $1/norm(w)$ (et la totale, des deux côtés $2/norm(w)$. D'ou l'idée de maximiser $1/norm(w)$, ou de minimiser $1/2 ||w||^2$ (plus simple pour les calculs).
> 
> ![[image-160.png|208x155]]
> 
> Le problème, c'est qu'on veut toujours que certains points puissent violer la marge (le problème ne doit pas être parfait). Pour ça, on ne dit plus que $y_i (w^⊤ x_i ​ + b ) >= 1$ mais que $y_i (w^⊤ x_i ​ + b ) >= 1 - xi_i$ et veut minimiser :
> 
> $"Loss" = 1/2 ||w||^2 + C sum_i xi_i$
> 
> ![[image-159.png|492x245]]
> 
> Pour que le modèle prenne à la fois en compte le fait qu'on ne doit pas missclassifier des points, mais qu'on doit aussi ​que ceux bien classifiés doivent être le plus possibles.
> 
> ![[image-162.png]]
> 
> - Si $xi_i = 0$, le point est bien classifié et en dehors de la marge.
> - Si $0 <= xi_i <= 1$, le sample est classifié et dans la marge
> - Si $xi_i >= 1$, alors le sample est mal classifié.
>   
> Avec un grand $C$, on empêche donc les mauvaises classifications.

> [!question] Et comment faire l'entraînement ?
> 
> On obtient donc cette fonction à minimiser  $"Loss" (w) = 1/2 ||w||^2 + C sum_i xi_i$ sous la contrainte $y_i (w^⊤ x_i ​ + b ) >= 1 - xi_i$.
> 
> Simplifions-là en enlevant les slack variables et calculons le Lagrangien ($cal(L)(x, y, lambda) = f(x, y) - lambda g(x, y)$, puis $cal(L)_(x, y) (x, y, lambda) = 0$). On obtient donc :
> $$ cal(L)(w, b, alpha) = 1/2||w||^2 - sum_(i = 1)^N alpha_i [y_i (w^T x_i + b) - 1] $$
> 
> On dérive par rapport à $w, b$: $$(delta cal(L))/(delta w) = 0 => w = sum_i alpha_i y_i x_i "et" (delta cal(L))/(delta b) = 0 => sum_i alpha_i y_i = 0$$
>
> On a trouvé la forme de notre $w$ !
> 
> $$ f(x) = w^T x + b = sum_(i in "support vectors") alpha_i y_i x_i x + b$$
> 
> (maintenant toute l'optimisation que font les libs python c'est de trouver les coefficients alpha)
> 
> a l'inférence avec les variables slack :
> $$ f(x) = sum_(i in "support vectors") alpha_i y_i k(x, x_i) + b "avec" 0 <= alpha_i <= C, forall i $$

Classification non linéaire, comment on fait ? parfois les données ne sont pas séparables 
## Données non linéairement séparables

> [!tip] L'idée : augmenter les dimensions
> 
> Ce qu'on fait donc, c'est de choisir une fonction non linéaire, de l'appliquer à nos données (en fait au lieu d'avoir juste une série de points $(x, y)$ on va avoir $(x, y, f(x, y))$, et d'espérer qu'elles soient séparables.

> [!tip] Polynomial expansion
> 
> On ne donne plus uniquement $x$ mais $x, x^2, x^3, ..$, etc. pour permettre une approximation de notre fonction avec un polynôme.

**Régularisation** : On ajoute souvent un terme $\tfrac{\lambda}{2}\,\|w\|^2$ pour éviter le sur-apprentissage : $$L_{\mathrm{CE+reg}}(w) = L_{\mathrm{CE}}(w) \;+\;\frac{\lambda}{2}\,\|w\|^2.$$
On peut trouver le $lambda$ idéal avec la cross-validation.
## SVM / Kernel trick

> [!danger] Le problème sans le Kernel Trick
> Ça marche bien, mais c'est très long, d'autant plus que dans certains cas on a besoin d'énormément de dimensions pour séparer les données. Et c'est aussi difficile de trouver cette fonction $Phi$ qui fait un bon mapping (il faut en tester plusieurs -- pas de recette magique).

> [!tip] Le kernel trick
> 
> Soit $Phi$ notre fonction de mapping.
> En fait, comme on le voit plus haut, notre fonction ressemble à ça :
> $$ f(x) = w^T Phi(x) + b = sum_(i = 1)^N alpha_i y_i Phi(x_i) Phi(x) + b $$ 
> 
> donc en fait on a juste besoin de connaître une fonction $K(x, x_i) = angle.l x, x_i angle.r$ ! et c'est beaucoup plus simple.

> [!example] Un exemple
> 
> $$ \phi(x_1, x_2) = \left(1,\; \sqrt{2}x_1,\; \sqrt{2}x_2,\; x_1^2,\; \sqrt{2}x_1 x_2,\; x_2^2 \right) $$
> $$ \langle \phi(\mathbf{x}), \phi(\mathbf{y}) \rangle = 1 \cdot 1 + \sqrt{2}x_1 \cdot \sqrt{2}y_1 + \sqrt{2}x_2 \cdot \sqrt{2}y_2 + x_1^2 \cdot y_1^2 + \sqrt{2}x_1x_2 \cdot \sqrt{2}y_1y_2 + x_2^2 \cdot y_2^2 $$
> $$ \langle \phi(\mathbf{x}), \phi(\mathbf{y}) \rangle = 1 + 2x_1y_1 + 2x_2y_2 + x_1^2 y_1^2 + 2x_1x_2y_1y_2 + x_2^2 y_2^2 $$
> $$ \langle \phi(\mathbf{x}), \phi(\mathbf{y}) \rangle = 1 + 2\mathbf{x}^T \mathbf{y} + (\mathbf{x}^T \mathbf{y})^2 = (1 + \mathbf{x}^T \mathbf{y})^2 $$
> 
> On obtient une fonction beaucoup plus simple !

> [!danger] Limite des SVMs
> 
>- **Grande quantité de données** : la complexité d’entraînement est souvent $O(n^2)$ ou $O(n^3)$ selon l’algorithme, ce qui peut devenir prohibitif si on a des centaines de milliers d’exemples.
>  
>  - **Choix de kernel non trivial** : il n’existe pas de recette magique pour savoir quel kernel convient le mieux à un problème donné.

