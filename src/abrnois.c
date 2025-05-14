#include "abrnois.h"

Node *allocate_node(char *mot)
{
    Node *new_noeud = malloc(sizeof(Node));
    if (new_noeud == NULL)
    {
        return NULL;
    }
    new_noeud->mot = strdup(mot);
    if (new_noeud->mot == NULL)
    {
        free(new_noeud);
        return NULL;
    }
    new_noeud->nb_occ = 1;
    new_noeud->fd = NULL;
    new_noeud->fg = NULL;
    return new_noeud;
}

int free_node(Node *n)
{
    if (n == NULL)
    {
        return 1;
    }
    free(n->mot);
    free(n);
    return 0;
}

void rotation_gauche(ABRnois *A)
{
    if (*A == NULL || (*A)->fd == NULL)
    {
        return;
    }
    ABRnois pivot = (*A)->fd;
    (*A)->fd = pivot->fg;
    pivot->fg = *A;
    *A = pivot;
}

void rotation_droite(ABRnois *A)
{
    if (*A == NULL || (*A)->fg == NULL)
    {
        return;
    }
    ABRnois pivot = (*A)->fg;
    (*A)->fg = pivot->fd;
    pivot->fd = *A;
    *A = pivot;
}

void rotation_gauche_droite(ABRnois *A)
{
    rotation_gauche(&((*A)->fg));
    rotation_droite(A);
}

void rotation_droite_gauche(ABRnois *A)
{
    rotation_droite(&((*A)->fd));
    rotation_gauche(A);
}

int insert_ABRnois(ABRnois *A, char *mot)
{
    if (mot == NULL) // Check if the word is NULL
    {
        return 1;
    }

    if (*A == NULL) // If the tree is empty, create a new node
    {
        *A = allocate_node(mot);
        if (*A == NULL)
        {
            return 1;
        }
        return 0;
    }

    int cmp = strcmp(mot, (*A)->mot);

    if (cmp < 0) // The word is lexicographically smaller
    {
        int status = insert_ABRnois(&((*A)->fg), mot); // Insert in the left subtree
        if (status != 0)
        {
            return status;
        }
        if ((*A)->fg != NULL && (*A)->fg->nb_occ > (*A)->nb_occ) // The priority of the inserted node is greater
        {
            rotation_droite(A);
        }
        return 0;
    }

    else if (cmp > 0) // The word is lexicographically larger
    {
        int status = insert_ABRnois(&((*A)->fd), mot); // Insert in the right subtree
        if (status != 0)
        {
            return status;
        }
        if ((*A)->fd != NULL && (*A)->fd->nb_occ > (*A)->nb_occ) // The priority of the inserted node is greater
        {
            rotation_gauche(A);
        }
        return 0;
    }
    else // The word is already present
    {
        (*A)->nb_occ++;
        return 0;
    }
}

int insert_ABRnois_multiple(ABRnois *A, char *mot, int nb_occ)
{
    for (int i = 0; i < nb_occ; i++)
    {
        int status = insert_ABRnois(A, mot);
        if (status != 0)
        {
            return status;
        }
    }
    return 0;
}