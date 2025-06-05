Utilisés pour prédire une valeur continue, par exemple pour prédire le prix d'une maison en fonction de ses caractéristiques.

$$ y = a_0 + a_1 x_1 + ... + a_i x_i$$
$y$ est la valeur de sortie, $x_i$ est la $i$ème feature, $a_i$ est le poids associé à la $i$-ème feature.

**Comment déterminer les paramètres du modèle ?**

Notre fonction de loss est une fonction de distance entre le $y_"pred"$ trouvé et le $y_"ground"$ :
$$ "Loss"_"MSE" = 1/m sum_(i = 1)^m (y_i - y_(i, "pred"))^2 $$
Pour ça, on peut utiliser une descente de gradient.