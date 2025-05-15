#ifndef LIST_H
#define LIST_H

#include <stdio.h>
#include <stdlib.h>
#include "abrnois.h"

typedef struct _cell {
    Node * n;
    struct _cell * suivant;
} Cell , * List;

/**
 * @brief Create a new cell.
 *
 * @return Cell* the new cell
 */
Cell *allocate_cell(Node *);

/**
 * @brief Free a cell.
 * 
 * @param C the cell to free
 * @return int 0 on success, 1 on failure
 */
int free_cell(Cell *);

/**
 * @brief Print the list of cells.
 * 
 * @param L the list to print
 * @return int 0 on success, 1 on failure
 */
int print_list(List L);

/**
 * @brief Recursive function to get a node to be a leaf.
 * 
 * @param current_node_ptr pointer to the current node to move
 * @return Node* The node which is now a leaf and detached from the tree
 */
Node* make_node_leaf(ABRnois *current_node_ptr);

/**
 * @brief Sort a list of cells in ascending order based on the node's word.
 *
 * @param L the list to sort
 * @return int 0 on success, 1 on failure
 */
int sort_list(List *L);

/**
 * @brief Extract all the nodes from the tree that has the same maximum priority.
 * 
 * @param A the tree to extract from
 * @param L the list to store the extracted nodes
 * 
 * @return int number of nodes extracted
 */
int extract_priorite_max(ABRnois *, List *);

#endif // LIST_H