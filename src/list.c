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

int print_list(List L)
{
    if (L == NULL)
    {
        return 1;
    }

    Cell *current = L;
    while (current != NULL)
    {
        printf("%s = %d", current->n->mot, current->n->nb_occ);
        current = current->suivant;
        if (current != NULL)
        {
            printf(" -> \n");
        }
    }
    printf("\n");
    printf("\n");
    return 0;
}

Node *make_node_leaf(ABRnois *current_node_ptr)
{
    // current_node_ptr is a pointer to a pointer to the current node
    if (current_node_ptr == NULL || *current_node_ptr == NULL)
    {
        return NULL;
    }

    Node *node = *current_node_ptr; // Dereference to get the current node

    if (node->fg == NULL && node->fd == NULL)
    {
        *current_node_ptr = NULL; // Detach the node from the tree
        return node;              // Return the node as a leaf
    }

    // if the node is not a leaf, we need to make it a leaf by rotating the tree

    // If only right child exists, rotate left and follow left child
    if (node->fg == NULL && node->fd != NULL)
    {
        rotate_left(current_node_ptr);
        return make_node_leaf(&((*current_node_ptr)->fg));
    }

    // If only left child exists, rotate right and follow right child
    else if (node->fd == NULL && node->fg != NULL)
    {
        rotate_right(current_node_ptr);
        return make_node_leaf(&((*current_node_ptr)->fd));
    }

    // If both children exist
    else if (node->fg != NULL && node->fd != NULL)
    {

        // If the left child has a higher occurrence,
        if (node->fg->nb_occ > node->fd->nb_occ)
        {
            rotate_right(current_node_ptr);
            return make_node_leaf(&((*current_node_ptr)->fd));
        }
        // If the right child has a higher occurrence or they are equal
        else
        {
            rotate_left(current_node_ptr);
            return make_node_leaf(&((*current_node_ptr)->fg));
        }
    }
    return NULL;
}

int sort_list(List *L)
{
    if (L == NULL || *L == NULL)
    {
        return 1;
    }

    Cell *current = *L;
    Cell *next = NULL;

    while (current != NULL)
    {
        next = current->suivant;
        while (next != NULL && next->n->nb_occ == current->n->nb_occ)
        {
            if (strcmp(current->n->mot, next->n->mot) > 0)
            {
                Node *temp = current->n;
                current->n = next->n;
                next->n = temp;
            }
            next = next->suivant;
        }
        current = current->suivant;
    }
    return 0;
}

int extract_maximum_priority(ABRnois *A, List *L)
{
    if (A == NULL || *A == NULL)
    {
        return 0;
    }

    int max_occ = (*A)->nb_occ;
    int count = 0;

    while ((*A) != NULL && (*A)->nb_occ == max_occ)
    {
        Node *node = make_node_leaf(A);
        if (node == NULL)
        {
            return 0;
        }

        Cell *new_cell = allocate_cell(node);
        if (new_cell == NULL)
        {
            free_node(node);
            return 0;
        }

        new_cell->suivant = *L;
        *L = new_cell;
        count++;
    }
    return count;
}