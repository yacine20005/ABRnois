#include "list.h"

Cell *allocate_cell(Node *node)
{
    Cell *new_cell = malloc(sizeof(Cell));
    if (new_cell == NULL)
    {
        return NULL;
    }
    new_cell->n = node;
    new_cell->next = NULL;
    return new_cell;
}

int free_cell(Cell *cell)
{
    if (cell != NULL)
    {
        free(cell);
        return 0;
    }
    return 1;
}

int free_list(List *L)
{
    if (L == NULL || *L == NULL)
    {
        return 1;
    }

    Cell *current = *L;
    Cell *next = NULL;

    while (current != NULL)
    {
        next = current->next;
        free_cell(current);
        current = next;
    }
    *L = NULL;
    return 0;
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
        printf("%s = %d", current->n->word, current->n->occurrence_count);
        current = current->next;
        if (current != NULL)
        {
            printf(" -> \n");
        }
    }
    printf("\n");
    printf("\n");
    return 0;
}

Node *make_node_leaf(ABRnois *node_pointer)
{
    if (node_pointer == NULL || *node_pointer == NULL)
    {
        return NULL;
    }

    Node *node = *node_pointer; // Generate a new pointer to the node

    if (node->fg == NULL && node->fd == NULL)
    {
        *node_pointer = NULL; // Detach the node from the tree
        return node;          // Return the node as a leaf
    }

    // if the node is not a leaf, we need to make it a leaf by rotating the tree

    // If only right child exists, rotate left and follow left child
    if (node->fg == NULL && node->fd != NULL)
    {
        rotate_left(node_pointer);
        return make_node_leaf(&((*node_pointer)->fg));
    }

    // If only left child exists, rotate right and follow right child
    else if (node->fd == NULL && node->fg != NULL)
    {
        rotate_right(node_pointer);
        return make_node_leaf(&((*node_pointer)->fd));
    }

    // If both children exist
    else if (node->fg != NULL && node->fd != NULL)
    {

        // If the left child has a higher occurrence
        if (node->fg->occurrence_count > node->fd->occurrence_count)
        {
            rotate_right(node_pointer);
            return make_node_leaf(&((*node_pointer)->fd));
        }
        // If the right child has a higher occurrence or they are equal
        else
        {
            rotate_left(node_pointer);
            return make_node_leaf(&((*node_pointer)->fg));
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
        next = current->next;
        while (next != NULL && next->n->occurrence_count == current->n->occurrence_count) // Sort by occurrence group
        {
            if (strcmp(current->n->word, next->n->word) > 0) 
            {
                Node *temp = current->n;
                current->n = next->n;
                next->n = temp;
            }
            next = next->next;
        }
        current = current->next;
    }
    return 0;
}

int extract_maximum_priority(ABRnois *tree, List *L)
{
    if (tree == NULL || *tree == NULL)
    {
        return 0;
    }

    int max_occ = (*tree)->occurrence_count;
    int count = 0;

    while ((*tree) != NULL && (*tree)->occurrence_count == max_occ) // While the current node has the maximum occurrence 
    {
        Node *node = make_node_leaf(tree);
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

        new_cell->next = *L;
        *L = new_cell;
        count++;
    }
    return count;
}