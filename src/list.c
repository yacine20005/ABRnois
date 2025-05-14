#include "list.h"

Cell *allocate_cell(Node *n)
{
    Cell *new_cell = malloc(sizeof(Cell));
    if (new_cell == NULL)
    {
        return NULL;
    }
    new_cell->n = n;
    new_cell->suivant = NULL;
    return new_cell;
}

int free_cell(Cell *C)
{
    if (C != NULL)
    {
        free(C);
        return 0;
    }
    return 1;
}

Node* make_node_leaf(ABRnois *current_node_ptr)
{
    // current_node_ptr is a pointer to a pointer to the current node
    if (current_node_ptr == NULL || *current_node_ptr == NULL)
    {
        return NULL;
    }

    printf("The word is: %s\n", (*current_node_ptr)->mot);
    Node *node = *current_node_ptr; // Dereference to get the current node

    if (node->fg == NULL && node->fd == NULL)
    {
        *current_node_ptr = NULL; // Detach the node from the tree
        return node; // Return the node as a leaf
    }

    // if the node is not a leaf, we need to make it a leaf by rotating the tree

// If only right child exists, rotate left and follow left child
    if (node->fg == NULL && node->fd != NULL) {
        rotation_gauche(current_node_ptr);
        return make_node_leaf(&((*current_node_ptr)->fg));
    }

    // If only left child exists, rotate right and follow right child
    else if (node->fd == NULL && node->fg != NULL) {
        rotation_droite(current_node_ptr);
        return make_node_leaf(&((*current_node_ptr)->fd));
    }

    // If both children exist
    else if (node->fg != NULL && node->fd != NULL) {

        if (node->fg->nb_occ > node->fd->nb_occ) {
            rotation_droite(current_node_ptr);
            return make_node_leaf(&((*current_node_ptr)->fd));

        } else {
            rotation_gauche(current_node_ptr);
            return make_node_leaf(&((*current_node_ptr)->fg));
        }
    }
    return NULL;
}