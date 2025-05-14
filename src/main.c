#include "abrnois.h"
#include "extraction.h"
#include "graphics.h"
#include "list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    ABRnois arbre = NULL;

    insert_ABRnois_multiple(&arbre, "vous", 3);
    insert_ABRnois_multiple(&arbre, "bien", 2);
    insert_ABRnois_multiple(&arbre, "zoo", 2);
    insert_ABRnois_multiple(&arbre, "allez", 1);
    insert_ABRnois_multiple(&arbre, "bonjour", 1);
    insert_ABRnois_multiple(&arbre, "comment", 4);

    generate_pdf("arbre", arbre);

    Node *extracted_node = make_node_leaf(&arbre);
    printf("Extracted node: %s\n", extracted_node->mot);
    generate_pdf("extracted", arbre);
    return 0;
}