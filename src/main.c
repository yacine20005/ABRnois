#include "abrnois.h"
#include "extraction.h"
#include "graphics.h"
#include "list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
    ABRnois arbre = NULL;

    printf("Test de alloue_noeud:\n");
    insert_abr(&arbre, "motC");
    insert_abr(&arbre, "motA");
    insert_abr(&arbre, "motE");
    insert_abr(&arbre, "motB");
    insert_abr(&arbre, "motD");

    generate_pdf("arbre_initial", arbre);

    rotation_gauche(&arbre);
    generate_pdf("arbre_apres_rotation_gauche", arbre);

    rotation_droite(&arbre);
    generate_pdf("arbre_apres_rotation_droite", arbre);
   
    return 0;
}