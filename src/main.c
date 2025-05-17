#include "abrnois.h"
#include "graphics.h"
#include "list.h"
#include "fetch.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        fprintf(stderr, "Usage: %s frequents.txt corpus_1.txt [corpus_2.txt ... corpus_n.txt]\n", argv[0]);
        return 1;
    }
    char *export_filename = argv[1];
    ABRnois *arbre = NULL;
    int total_mots = 0;
    int error = 0;

    for (int i = 2; i < argc; i++)
    {
        FILE *f = fopen(argv[i], "r");
        if (!f)
        {
            fprintf(stderr, "Error opening file %s\n", argv[i]);
            continue;
        }
        char *buffer = init_buffer();
        int c;
        while ((c = fgetc(f)) != EOF)
        {
            if (is_char(c))
            {
                add_buffer(buffer, c);
            }
            else
            {
                if (is_valid_word(buffer))
                {
                    error = insert_ABRnois(arbre, buffer);
                    if (error != 0)
                    {
                        fprintf(stderr, "Error inserting word %s\n", buffer);
                        free(buffer);
                        fclose(f);
                        liberer_ABRnois(arbre);
                        return 1;
                    }
                    total_mots++;
                }
                clear_buffer(buffer);
            }
        }
        if (is_valid_word(buffer))
        {
            error = insert_ABRnois(arbre, buffer);
            if (error != 0)
            {
                fprintf(stderr, "Error inserting word %s\n", buffer);
                free(buffer);
                fclose(f);
                liberer_ABRnois(arbre);
                return 1;
            }
            total_mots++;
        }
        free(buffer);
        fclose(f);
    }

    FILE *out = fopen(export_filename, "w");
    if (!out)
    {
        fprintf(stderr, "Error opening output file %s\n", export_filename);
        liberer_ABRnois(arbre);
        return 1;
    }
    List liste = NULL;
    while (arbre != NULL)
    {
        int nb = extract_maximum_priority(arbre, &liste);
        sort_list(&liste);
        Cell *cell = liste;
        while (cell != NULL)
        {
            double pourcentage = (100.0 * cell->n->nb_occ / total_mots);
            fprintf(out, "%s %.2f\n", cell->n->mot, pourcentage);
            cell = cell->suivant;
        }
        while (liste != NULL)
        {
            Cell *tmp = liste;
            liste = liste->suivant;
            free_node(tmp->n);
            free_cell(tmp);
        }
    }
    fclose(out);
    return 0;
}