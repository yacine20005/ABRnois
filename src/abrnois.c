#include "abrnois.h"

Node *allocate_node(char *word)
{
    Node *new_noeud = malloc(sizeof(Node));
    if (new_noeud == NULL)
    {
        return NULL;
    }
    new_noeud->word = strdup(word); // strdup allocates memory and copies the string
    if (new_noeud->word == NULL)
    {
        free(new_noeud);
        return NULL;
    }
    new_noeud->occurrence_count = 1;
    new_noeud->fd = NULL;
    new_noeud->fg = NULL;
    return new_noeud;
}

int free_node(Node *node)
{
    if (node == NULL)
    {
        return 1;
    }
    free(node->word);
    free(node);
    return 0;
}

int free_tree(ABRnois *tree)
{
    if (*tree == NULL)
    {
        return 1;
    }
    free_tree(&((*tree)->fg));
    free_tree(&((*tree)->fd));
    free_node(*tree);
    *tree = NULL;
    return 0;
}

void rotate_left(ABRnois *tree)
{
    if (*tree == NULL || (*tree)->fd == NULL)
    {
        return;
    }
    ABRnois pivot = (*tree)->fd;
    (*tree)->fd = pivot->fg;
    pivot->fg = *tree;
    *tree = pivot;
}

void rotate_right(ABRnois *tree)
{
    if (*tree == NULL || (*tree)->fg == NULL)
    {
        return;
    }
    ABRnois pivot = (*tree)->fg;
    (*tree)->fg = pivot->fd;
    pivot->fd = *tree;
    *tree = pivot;
}

void rotate_left_right(ABRnois *tree)
{
    rotate_left(&((*tree)->fg));
    rotate_right(tree);
}

void rotate_right_left(ABRnois *tree)
{
    rotate_right(&((*tree)->fd));
    rotate_left(tree);
}

int insert_ABRnois(ABRnois *tree, char *word)
{
    if (word == NULL)
    {
        return 1;
    }

    if (*tree == NULL)
    {
        *tree = allocate_node(word);
        if (*tree == NULL)
        {
            return 1;
        }
        return 0;
    }

    int cmp = strcmp(word, (*tree)->word); // strcmpt returns an int based on the lexicographical comparison

    if (cmp < 0) // The word is lexicographically smaller
    {
        int status = insert_ABRnois(&((*tree)->fg), word); // Insert in the left subtree
        if (status != 0)
        {
            return status;
        }
        if ((*tree)->fg != NULL && (*tree)->fg->occurrence_count > (*tree)->occurrence_count) // The priority of the inserted node is greater
        {
            rotate_right(tree);
        }
        return 0;
    }

    else if (cmp > 0) // The word is lexicographically larger
    {
        int status = insert_ABRnois(&((*tree)->fd), word); // Insert in the right subtree
        if (status != 0)
        {
            return status;
        }
        if ((*tree)->fd != NULL && (*tree)->fd->occurrence_count > (*tree)->occurrence_count) // The priority of the inserted node is greater
        {
            rotate_left(tree);
        }
        return 0;
    }
    else // The word is already present
    {
        (*tree)->occurrence_count++;
        return 0;
    }
}

int insert_ABRnois_multiple(ABRnois *tree, char *word, int occurrence_count)
{
    for (int i = 0; i < occurrence_count; i++)
    {
        int status = insert_ABRnois(tree, word);
        if (status != 0)
        {
            return status;
        }
    }
    return 0;
}