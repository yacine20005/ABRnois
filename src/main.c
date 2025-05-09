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

    insert_ABRnois(&arbre, "vous");
    insert_ABRnois(&arbre, "bien");
    insert_ABRnois(&arbre, "zoo");
    insert_ABRnois(&arbre, "allez");
    insert_ABRnois(&arbre, "bonjour");
    for (int i = 0; i < 4; i++)
    {
        insert_ABRnois(&arbre, "comment");
    }

    generate_pdf("arbre", arbre);

    return 0;
}