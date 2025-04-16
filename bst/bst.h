//  bst.h : partie interface d'un module polymorphe pour la spécification ABINR
//    du TDA ABinR(T).

#ifndef BST_H  // Protection contre les inclusions multiples
#define BST_H

#include <stdio.h>
#include <stdlib.h>

//  Fonctionnement général :
//  - la structure de données ne stocke pas d'objets mais des références vers
//      ces objets. Les références sont du type générique « void * » ;
//  - si des opérations d'allocation dynamique sont effectuées, elles le sont
//      pour la gestion propre de la structure de données, et en aucun cas pour
//      réaliser des copies ou des destructions d'objets ;
//  - les fonctions qui possèdent un paramètre de type « bst * » ou « bst ** »
//      ont un comportement indéterminé lorsque ce paramètre ou sa déréférence
//      n'est pas l'adresse d'un contrôleur préalablement renvoyée avec succès
//      par la fonction bst_empty et non révoquée depuis par la fonction
//      bst_dispose ;
//  - aucune fonction ne peut ajouter un pointeur nul à la structure de
//      données ;
//  - les fonctions de type de retour « void * » renvoient un pointeur nul en
//      cas d'échec. En cas de succès, elles renvoient une référence de valeur
//      actuellement ou auparavant stockée par la structure de données ;
//  - l'implantation des fonctions dont la spécification ne précise pas qu'elles
//      doivent gérer les cas de dépassement de capacité ne doivent avoir
//      affaire à aucun problème de la sorte.

//  struct bst, bst : type et nom de type d'un contrôleur regroupant les
//    informations nécessaires pour gérer un arbre binaire de recherche de
//    d'objets quelconques.
typedef struct bst bst;

//  bst_empty : tente d'allouer les ressources nécessaires pour gérer un nouvel
//    arbre binaire de recherche initialement vide. La fonction de comparaison
//    des objets via leurs références est pointée par compar. Renvoie un
//    pointeur nul en cas de dépassement de capacité. Renvoie sinon un pointeur
//    vers le contrôleur associé à l'arbre.
extern bst *bst_empty(int (*compar)(const void *, const void *));

//  bst_dispose : sans effet si *tptr vaut un pointeur nul. Libère sinon les
//    ressources allouées à la gestion de l'arbre binaire de recherche associé à
//    *tptr puis affecte un pointeur nul à *tptr.
extern void bst_dispose(bst **tptr);

//  bst_add_endofpath : renvoie un pointeur nul si ref vaut un pointeur nul.
//    Recherche sinon dans l'arbre binaire de recherche associé à t la référence
//    d'un objet égal à celui de référence ref au sens de la fonction de
//    comparaison. Si la recherche est positive, renvoie la référence trouvée.
//    Tente sinon d'ajouter la référence selon la méthode de l'ajout en bout de
//    chemin ; renvoie un pointeur nul en cas de dépassement de capacité ;
//    renvoie sinon ref.
extern void *bst_add_endofpath(bst *t, const void *ref);



//  bst_repr_graphic : affiche sur la sortie standard une représentation
//    graphique de l'arbre binaire de recherche associé à t. La fonction put est
//    utilisée pour l'affichage de chacune des valeurs dont les références sont
//    stockées dans l'arbre. La fonction bst_repr_graphic est libre d'afficher
//    des informations supplémentaires liées aux sous-arbres.
extern void bst_repr_graphic(bst *t, void (*put)(const void *ref));


//  bst_search : renvoie un pointeur nul si ref vaut un pointeur nul. Recherche
//    sinon dans l'arbre binaire de recherche associé à t la référence d'un
//    objet égal à celui de référence ref au sens de la fonction de comparaison.
//    Renvoie un pointeur nul si la recherche est négative, la référence trouvée
//    sinon.
extern void *bst_search(bst *t, const void *ref);

extern void *add_word(char *word, bst *root);

extern void *add_letter(char *word, bst *root);

extern int bst_common_word(bst *t1, bst* t2);

extern int bst_union_tree(bst *t1, bst* t2);

extern float bst_jaccard_tree(bst *t1, bst* t2);


#endif
