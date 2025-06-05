
On utilise une frontière linéaire $f(x) = w^\top x + b$  puis on passe ce score dans la sigmoïde pour obtenir une probabilité $\hat p = \sigma\bigl(f(x)\bigr) = \frac{1}{1 + e^{-\,f(x)}} \quad\in(0,1).$

On minimise la **cross-entropy** (log-loss) sur le jeu de données $\{(x_n,\,t_n)\}$, où $t_n\in\{0,1\}$ :  $$L_{\mathrm{CE}}(w) 
    = -\,\sum_{n=1}^N \Bigl[t_n\,\log\bigl(\hat p_n\bigr) 
    \;+\;(1 - t_n)\,\log\bigl(1 - \hat p_n\bigr)\Bigr].$$
On peut aussi exprimer cette perte en notant $y_n = 2\,t_n - 1 \in \{\,-1,\,+1\}$ :  
  $$L_{\mathrm{CE}}(w) 
    = \sum_{n=1}^N \log\bigl(1 + e^{-\,y_n\,f(x_n)}\bigr).$$
**Convexité** : La log-loss $\log\bigl(1 + e^{-\,y_n f(x_n)}\bigr)$ est une fonction convexe et différentiable partout.  On peut donc utiliser des méthodes de descente de gradient (batch, mini-batch, LBFGS, etc.) pour optimiser $w$ et $b$. 

**Sortie probabiliste** : Le modèle produit une probabilité $\hat p\in(0,1)$, utile pour calibrer des seuils ou mesurer l’incertitude.

**Convergence en cas de non-séparabilité** : Contrairement au perceptron, la régression logistique converge même si les données ne sont pas parfaitement séparables, les coefficients $w$ peuvent croître pour améliorer la valeur de $\hat p$ sur chaque exemple.  

**Régularisation** : On ajoute souvent un terme $\tfrac{\lambda}{2}\,\|w\|^2$ pour éviter le sur-apprentissage : $$L_{\mathrm{CE+reg}}(w) = L_{\mathrm{CE}}(w) \;+\;\frac{\lambda}{2}\,\|w\|^2.$$
