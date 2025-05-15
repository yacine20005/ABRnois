# TODO List - DM2 ABRnois

## I. Configuration et Structures de Base (abrnois.c)

- [x] Copier/coller les définitions des structures `_noeud` (et `Noeud`, `ABRnois`), `_cell` (et `Cell`, `Liste`) fournies dans `abrnois.c`.

- [x] **Implémenter `Noeud * alloue_noeud(char * mot)`**
  - Allouer dynamiquement la mémoire pour un `Noeud`.
  - Allouer dynamiquement la mémoire pour le champ `mot` et copier la chaîne `mot` passée en argument (utiliser `strdup` ou `malloc` + `strcpy`). Attention à la gestion d'erreur.
  - Initialiser `nb_occ` à 1.
  - Initialiser `fg` et `fd` à `NULL`.
  - Retourner le pointeur vers le nœud créé ou `NULL` en cas d'erreur.

## II. Exportation Graphique (-g) (abrnois.c)

- [x] **Implémenter `int exporte_arbre(char * nom_pdf, ABRnois A)` | `void generate_pdf(char *filename, ABRnois a)`**
  - Choisir une méthode (génération de fichier `.dot` + appel `system("dot ...")` recommandé).
  - Implémenter la fonction récursive pour parcourir l'arbre et générer le contenu `.dot`.
  - Gérer la création du fichier `.dot`, l'appel à `dot` pour créer le PDF, et la suppression du `.dot`.
  - Retourner un code de succès/échec.

## III. Opérations Fondamentales sur l'ABRnois (abrnois.c)

- [x] **Implémenter `void rotation_gauche(ABRnois * A)`**
  - Vérifier que `*A` et son fils droit (`(*A)->fd`) ne sont pas `NULL`.
  - Effectuer la rotation gauche standard (pivot = fils droit).
  - Mettre à jour correctement le pointeur `*A`.

- [x] **Implémenter `void rotation_droite(ABRnois * A)`**
  - Vérifier que `*A` et son fils gauche (`(*A)->fg`) ne sont pas `NULL`.
  - Effectuer la rotation droite standard (pivot = fils gauche).
  - Mettre à jour correctement le pointeur `*A`.
  - _Note : Les fonctions prennent `ABRnois *A` (pointeur vers pointeur de Noeud) pour pouvoir modifier la racine du sous-arbre._

- [x] **Implémenter `void rotation_gauche_droite(ABRnois * A)`**
  - Vérifier que `*A` et son fils gauche (`(*A)->fg`) ne sont pas `NULL`.
  - Effectuer la rotation gauche sur le fils gauche, puis la rotation droite sur `*A`.
  - Mettre à jour correctement le pointeur `*A`.

- [x] **Implémenter `void rotation_droite_gauche(ABRnois * A)`**
  - Vérifier que `*A` et son fils droit (`(*A)->fd`) ne sont pas `NULL`.
  - Effectuer la rotation droite sur le fils droit, puis la rotation gauche sur `*A`.
  - Mettre à jour correctement le pointeur `*A`.

- [x] **Implémenter `int insert_ABRnois(ABRnois * A, char * mot)`**
  - **Partie 1 : Insertion type ABR**
    - Parcourir l'arbre pour trouver l'emplacement d'insertion basé sur l'ordre lexicographique (`strcmp`).
    - Si le mot existe déjà : incrémenter `nb_occ` du nœud existant et ne pas insérer.
    - Si le mot n'existe pas : créer un nouveau nœud avec `alloue_noeud(mot)` et l'insérer.
    - Retourner 1 (ou >0) en cas de succès, 0 en cas d'échec.

  - **Partie 2 : Rétablissement de la propriété de tas (remontée)**
    - Après l'insertion/modification, remonter le chemin vers la racine.
    - Si la propriété de tas (`noeud->nb_occ >= enfant->nb_occ`) est violée, effectuer la rotation appropriée (`rotation_droite` ou `rotation_gauche`) pour la rétablir.

## IV. Extraction du Maximum (abrnois.c)

- [x] **Implémenter `int extrait_priorite_max(ABRnois * A, Liste * lst)`**
  - Vérifier si l'arbre `*A` est vide.
  - Récupérer la priorité maximale `p_max = (*A)->nb_occ`.
  - Initialiser `*lst` à `NULL` et un compteur `count` à 0.

  - **Boucle d'extraction :** Tant que l'arbre `*A` n'est pas vide ET que `(*A)->nb_occ == p_max`:
    - Sauvegarder le nœud racine actuel (`Noeud *noeud_a_extraire = *A`).

    - **Partie 1 : Descente du nœud racine**
      - Utiliser des rotations successives (gauche ou droite selon la priorité des enfants, gauche par défaut si égales) pour faire descendre `noeud_a_extraire` jusqu'à ce qu'il devienne une feuille (ou soit déconnecté). Gérer correctement les pointeurs `A`.

    - **Partie 2 : Suppression et ajout à la liste**
      - Ajouter `noeud_a_extraire` (maintenant déconnecté) à la liste chaînée `*lst` (créer une `Cell`).
      - Incrémenter `count`.
      - S'assurer que l'arbre `*A` est mis à jour correctement après les rotations et la "suppression" logique du nœud.

  - **Partie 3 : Tri de la liste extraite**
    - Trier la liste chaînée `*lst` par ordre alphabétique des `mot`.
  - Retourner `count`.

## V. Programme Principal (main dans abrnois.c)

- [ ] **Analyse des arguments de la ligne de commande (`argc`, `argv`)**
  - Identifier le fichier de sortie, les fichiers corpus.
  - Détecter et traiter les options `-g` et `-n p`.

- [ ] **Initialisation**
  - `ABRnois A = NULL`.
  - Compteurs (`total_mots`, `pdf_counter_*`).

- [ ] **Lecture des Corpus et Construction de l'Arbre**
  - Boucler sur les fichiers corpus.
  - Ouvrir, lire mot par mot (gérer casse, ponctuation simple).
  - Pour chaque mot : appeler `insert_ABRnois(&A, mot)`, incrémenter `total_mots`.
  - Si `-g`, appeler `exporte_arbre` après chaque insertion.
  - Fermer les fichiers.

- [ ] **Extraction des mots et Écriture du Fichier de Fréquence**
  - Ouvrir le fichier `frequents.txt` en écriture.
  - Initialiser une liste pour les résultats complets.
  - Définir la limite d'extraction (`p` ou tous).

  - **Boucle d'extraction principale :** Tant que l'arbre n'est pas vide et limite non atteinte:
    - Appeler `extrait_priorite_max(&A, &batch_extrait)`.
    - Ajouter `batch_extrait` (triée) à la liste des résultats complets.
    - Mettre à jour le compteur de mots extraits.
    - Gérer le cas `-n p` avec égalités de priorité.
    - Si `-g`, appeler `exporte_arbre` après chaque extraction de lot.

  - **Écriture des résultats :**
    - Parcourir la liste des résultats complets.
    - Calculer et écrire `mot pourcentage%` dans le fichier de sortie.
  - Fermer le fichier de sortie.

- [ ] **Nettoyage**
  - Libérer toute la mémoire allouée (nœuds, cellules, chaînes de caractères des mots).

## VI. Tests et Débogage

- [ ] Vérifier la gestion des cas limites (arbre vide, mot déjà présent, égalités de priorité).
- [ ] Utiliser `valgrind` ou `gdb` pour détecter les fuites mémoire.

## VII. Rédaction du Rapport (rapport.pdf)

- [ ] Rédiger une introduction.
- [ ] Décrire les fonctions implémentées (algorithmes, choix).
  - Expliquer que j'ai fait le choix de modifier la déclaration de la fonction qui génère le PDF pour qu'elle soit de type `void` à la place de `int` car aucune gestion d'erreur n'est nécessaire le seul problème pouvant survenir étant que le fichier PDF soit vide ce qui n'est pas un problème bloquant pour le programme.
- [ ] Lister les difficultés rencontrées et solutions.
- [ ] Indiquer la répartition du travail.
- [ ] Répondre à la section "Comparaison des méthodes" (si applicable/demandé).
- [ ] Ajouter une conclusion.
- [ ] Inclure les **noms et prénoms complets** du binôme.
- [ ] Mettre en forme le rapport.

## VIII. Finalisation et Soumission

- [ ] Relire le sujet et vérifier la conformité.
- [ ] Nettoyer le code (`abrnois.c`).
- [ ] Compiler sans warning.
- [ ] Effectuer un test final complet.
- [ ] Créer l'archive `nom1_nom2.zip` contenant `abrnois.c` et `rapport.pdf`.
- [ ] Soumettre avant la deadline.
