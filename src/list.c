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

int extract_priorite_max(ABRnois *A, List *L)
{
    if (A == NULL) // If the tree is empty nothing to extract
    {
        printf("Tree is empty\n");
        return 0;
    }
    if (L == NULL) // If the list is NULL can't store the extracted nodes
    {
        printf("List is NULL\n");
        return 0;
    }
    int max_priority = (*A)->nb_occ;
    int count = 0;
    ABRnois current_extraction;
    while (*A != NULL && (*A)->nb_occ == max_priority) // While the current node has the maximum priority and exists
    {
        current_extraction = *A;

        while (current_extraction->fg != NULL || current_extraction->fd != NULL) // if the current node has children
        {
            if (current_extraction->fg == NULL && current_extraction->fd != NULL) // if the current node has only a right child

            {
                rotation_gauche(A);
                current_extraction = current_extraction->fg;
            }
            else if (current_extraction->fd == NULL && current_extraction->fg != NULL) // if the current node has only a left child
            {
                rotation_droite(A);
                current_extraction = current_extraction->fd;
            }
            else if (current_extraction->fg != NULL && current_extraction->fd != NULL) // if the current node has both children
            {
                if (current_extraction->fg->nb_occ > current_extraction->fd->nb_occ) // if the left child has a greater priority
                {
                    rotation_droite(A);
                    current_extraction = current_extraction->fd;
                }
                else // if the right child has a greater priority or the same priority
                {
                    rotation_gauche(A);
                    current_extraction = current_extraction->fg;
                }
            }
        }
        Cell *new_cell = allocate_cell((current_extraction)); // Allocate a new cell with the current node
        if (new_cell == NULL)
        {
            return 0;
        }
        else
        {
            new_cell->suivant = *L; // The new cell is the new head of the list
            *L = new_cell;          // Update the list head
            count++;
            free_node(current_extraction); // Free the current node
            current_extraction = NULL;     // Set the current node to NULL
        }
    }
    return count; // Return the number of nodes extracted
}

int extract_priorite_max_recursive(ABRnois *A, List *L, int max_priority){
    if (*A == NULL){
        return 0;
    }
    int count = 0;
    count += extract_priorite_max_recursive(&(*A)->fg, L, max_priority);
    count += extract_priorite_max_recursive(&(*A)->fd, L, max_priority); 
    if ((*A)->nb_occ == max_priority){
        Cell *new_cell = allocate_cell(*A);
        if (new_cell == NULL)
            return count;
        new_cell->suivant = *L;
        *L = new_cell;
        free(*A);
        *A = NULL;
        return count + 1;
    }
    return count;
}

int extract_priorite_max2(ABRnois *A, List *L){
    if (A == NULL || *A == NULL){
        printf("Tree is empty\n");
        return 0;
    }
    if (L == NULL){
        printf("List is NULL\n");
        return 0;
    }
    int max_priority = (*A)->nb_occ;
    return extract_priorite_max_recursive(A, L, max_priority);
}
