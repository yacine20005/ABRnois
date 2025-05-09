#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "abrnois.h"

Node *alloue_noeud(char *mot)
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

int insert_abr(ABRnois *A, char *mot)
{
    if (mot == NULL)
    {
        return 1;
    }
    if (*A == NULL)
    {
        *A = alloue_noeud(mot);
        return 0;
    }
    if (strcmp(mot, (*A)->mot) < 0) // The word is lexicographically smaller
    {
        insert_abr(&((*A)->fg), mot);
        return 0;
    }
    else if (strcmp(mot, (*A)->mot) > 0) // The word is lexicographically greater
    {
        insert_abr(&((*A)->fd), mot);
        return 0;
    }
    else // The word is already present, so we increment the counter
    {
        (*A)->nb_occ++;
    }
    return 0;
}