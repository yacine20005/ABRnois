#ifndef ABRNOIS_H
#define ABRNOIS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
Node *allocate_node(char *);

/**
 * @brief Free the given node.
 *
 * @param n the node to free
 * @return int 0 on success, 1 on failure
 */
int free_node(Node *);

/**
 * @brief Perform a left rotation on the given tree.
 *
 * @param A the tree to rotate
 */
void rotate_left(ABRnois *);

/**
 * @brief Perform a right rotation on the given tree.
 *
 * @param A the tree to rotate
 */
void rotate_right(ABRnois *);

/**
 * @brief Perform a left-right rotation on the given tree.
 *
 * @param A the tree to rotate
 */
void rotate_left_right(ABRnois *);

/**
 * @brief Perform a right-left rotation on the given tree.
 *
 * @param A the tree to rotate
 */
void rotate_right_left(ABRnois *);

/**
 * @brief Perform an ABR insertion of a word.
 *
 * @param A the tree to insert into
 * @param mot the word to insert
 *
 * @return int 0 on success, 1 on failure
 */
int insert_ABRnois(ABRnois *, char *);

/**
 * @brief Perform an ABR insertion of a word multiple times.
 *
 * @param A the tree to insert into
 * @param mot the word to insert
 * @param nb_occ the number of occurrences to insert
 *
 * @return int 0 on success, 1 on failure
 */
int insert_ABRnois_multiple(ABRnois *, char *, int);

#endif // ABRNOIS_H