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
    ABRnois arbre = NULL;
    int word_count = 0;
    int error = 0;

    for (int i = 2; i < argc; i++)
    {
        FILE *text_file = fopen(argv[i], "r");
        if (!text_file)
        {
            fprintf(stderr, "Error opening file %s\n", argv[i]);
            continue;
        }
        char *buffer = init_buffer();
        int current_char;
        while ((current_char = fgetc(text_file)) != EOF)
        {
            if (is_char(current_char))
            {
                add_buffer(buffer, current_char);
            }
            else
            {
                if (is_valid_word(buffer))
                {
                    error = insert_ABRnois(&arbre, buffer);
                    if (error != 0)
                    {
                        fprintf(stderr, "Error inserting word %s\n", buffer);
                        free(buffer);
                        fclose(text_file);
                        free_tree(&arbre);
                        return 1;
                    }
                    word_count++;
                }
                clear_buffer(buffer);
            }
        }
        if (is_valid_word(buffer))
        {
            error = insert_ABRnois(&arbre, buffer);
            if (error != 0)
            {
                fprintf(stderr, "Error inserting word %s\n", buffer);
                free(buffer);
                fclose(text_file);
                free_tree(&arbre);
                return 1;
            }
            word_count++;
        }
        free(buffer);
        fclose(text_file);
    }

    FILE *export = fopen(export_filename, "w");
    if (!export)
    {
        fprintf(stderr, "Error opening output file %s\n", export_filename);
        free_tree(&arbre);
        return 1;
    }
    List node_list = NULL;
    while (arbre != NULL)
    {
        extract_maximum_priority(&arbre, &node_list);
    }
    sort_list(&node_list);
    Cell *cell = node_list;
    while (cell != NULL)
    {
        double pourcentage = (100.0 * cell->n->nb_occ / word_count);
        fprintf(export, "%s %.2f\n", cell->n->mot, pourcentage);
        cell = cell->suivant;
    }
    free_list(&node_list);
    free_tree(&arbre);
    fclose(export);
    return 0;
}