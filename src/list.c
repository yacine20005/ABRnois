#include "list.h"

Cell *alloue_cell(Node *n)
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