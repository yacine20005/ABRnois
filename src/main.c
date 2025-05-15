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
    insert_ABRnois_multiple(&arbre, "yacine", 4);

    generate_pdf("arbre", arbre);

    List extracted = NULL;
    int count = extract_priorite_max(&arbre, &extracted);
    count += extract_priorite_max(&arbre, &extracted);
    count += extract_priorite_max(&arbre, &extracted);
    printf("Extracted %d nodes.\n", count);
    print_list(extracted);
    sort_list(&extracted);
    printf("Sorted list:\n");
    print_list(extracted);
    generate_pdf("extracted", arbre);
    return 0;
}