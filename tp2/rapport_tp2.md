# IN210 - test et validation
### Elfie Molina--Bonnefoy

## Tests unitaires - 21/02/2025

### Question 1 : _pourquoi a-t-on besoin d'un epsilon lors de la comparaison de deux flottants ?_

Les nombres flottants étant écrits sur un nombre de bits limités (32 bits), il peut arriver des erreurs d'arrondis lors de calculs sur des types flottants. 

Concrètement ici, le prix est souvent le résultat d'un calcul (multiplication ou division par 2) qui n'est pas exact. La fonction `computePrice` renvoit donc une approximation du prix flottant qui peut ne pas être parfaitement égal à la valeur donnée en comparaison. 

Il est alors préférable de vérifier que la distance entre les deux flottants est négligeables. C'est la raison pour laquelle est introduit un espilon dans la vérification l'assert.


### Question 2 : _que vaut-il mieux utiliser comme type d'assertion ?_

Les assertions qui utilisent la fonction `assert_float_equal()` sont préférables aux assertions `assert_true(condition)`. En effet - bien que les deux fonctions soient capables de tester la condition d'égalité sur des flottans à epsilon près - lors d'une erreur, la fonction usant de `assert_true(condition)` ne précise pas l'erreur exacte qui a eu lieu. 

Dans le cas de cet exercice, l'erreur de la fonction `assertTrue` ne précise que la condition fausse : [ERROR] --- computePrice(11,0)==0.6.

### Question 3 : _pourquoi est-il préférable de faire un test pour chaque cas plutôt qu'un test avec plusieurs assertions ?_

Avoir un test unique pour chaque cas à traiter permet une meilleure couverture et une meilleure précision des tests. Lors d'un seul test avec plusieurs assertions, si l'une des assertion échoue alors le test échoue et les assertions suivantes ne seront pas traitées. Il faudrait donc régler les erreurs unes à unes pour voir apparaître les autres problèmes ce qui peut créer des problèmes de regression puisque le correcteur n'aurait pas une vue globale sur les problèmes testés.

Une multitude de test permet aussi de différencier les cas traités notamment ici, les test sur la condition `age` et `touriste` pourraient être tester séparemment et indépendemment.

### Question 4 : _implémentation de la couverture en modifiant le makefile_

La couverture du code - description du taux de code source exécuté à la suite de tests - se calcule automatiquement grâce à l'outil `gcov` de `gcc` et notamment aux options suivantes dans le makefile : 

```
LDFLAGS = -lgcov --coverage
OPTION = -Wall -fexceptions -fprofile-arcs -ftest-coverage
```
Pour interpréter et visualiser les résultats de la couverture, il est préférable de créer un fichier html (module python `gcovr`) :

```
gcov -b -c ratp.c (fichier résultat ratp.c.gcov)
gcovr --html-details result.html (fichier résultat html)
```

### Question 5 : _créationd d'un mock pour simuler l'utilisation d'une fonction extérieure dans notre test_

Dans cette dernière partie, la fonction qui donne le prix dépend d'un paramètre extérieur qui est l'âge limite à partir duquel une réduction s'applique. Pour faire des tests unitaires et non d'intégration, il faut donc tester la fonction de prix indépendemment du retour de cette deuxième fonction. Le mock permet donc cette simulation et s'écrit comme telle :

```
void recupAge(int* ageLimit){
    function_called();
    *ageLimit = (int)mock();
}
static void inflim_tourist(void **state){
    (void) state;
    expect_function_calls(recupAge, 1);
    will_return(recupAge, 14);
    assert_float_equal(0.6, computePriceLim(10,0), 0.001);
}
```

Grâce aux fonctions `function_called()` et `expect_function_calls(recupAge, 1)`, le test est assuré de n'appeler qu'une seule fois le mock (sinon, le test est noté comme échouant).
