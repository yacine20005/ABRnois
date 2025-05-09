#ifndef ABRNOIS_H
#define ABRNOIS_H

typedef struct _node
{
    char *mot;
    int nb_occ;
    struct _node *fg, *fd;
} Node, *ABRnois;

/**
 * @brief Allocate a new node with the given word.
 *
 * @param mot the word to store in the node
 * @return Node* the allocated node
 */
Node *alloue_noeud(char *);

/**
 * @brief Perform a left rotation on the given tree.
 *
 * @param A the tree to rotate
 */
void rotation_gauche(ABRnois *);

/**
 * @brief Perform a right rotation on the given tree.
 *
 * @param A the tree to rotate
 */
void rotation_droite(ABRnois *);

/**
 * @brief Perform a left-right rotation on the given tree.
 *
 * @param A the tree to rotate
 */
void rotation_gauche_droite(ABRnois *);

/**
 * @brief Perform a right-left rotation on the given tree.
 *
 * @param A the tree to rotate
 */
void rotation_droite_gauche(ABRnois *);

/**
 * @brief Perform an ABR insertion of a word.
 *
 * @param A the tree to insert into
 * @param mot the word to insert
 *
 * @return int 0 on success, 1 on failure
 */
int insert_ABRnois(ABRnois *, char *);

#endif // ABRNOIS_H