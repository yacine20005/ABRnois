#include "abrnois.h"
#include "graphics.h"
#include "list.h"
#include "fetch.h"
#include "loop.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(int argc, char *argv[])
{
    int generate_graphics = 0;
    int words_limit = -1;
    int arg_index = 1;
    char filename[FILENAME_SIZE];
    int delete_count = 0;
    int word_count = 0;
    int word_extracted = 0;

    while (arg_index < argc && argv[arg_index][0] == '-')
    {
        if (strcmp(argv[arg_index], "-g") == 0)
        {
            generate_graphics = 1;
            arg_index++;
        }

        else if (strcmp(argv[arg_index], "-n") == 0 && arg_index + 1 < argc)
        {
            words_limit = atoi(argv[arg_index + 1]);
            arg_index += 2;
        }

        else
        {
            fprintf(stderr, "Option inconnue : %s\n", argv[arg_index]);
            return 1;
        }
    }

    if (argc - arg_index < 2)
    {
        fprintf(stderr, "Usage: %s [-g] [-n p] frequents.txt corpus_1.txt [corpus_2.txt ... corpus_n.txt]\n", argv[0]);
        return 1;
    }

    char *export_filename = argv[arg_index];
    ABRnois arbre = NULL;

    if (loop_fetch_files(&arbre, &word_count, argc, argv, generate_graphics, arg_index + 1) != 0)
    {
        return 1;
    }

    FILE *export = fopen(export_filename, "w");
    if (!export)
    {
        fprintf(stderr, "Error opening output file %s\n", export_filename);
        free_tree(&arbre);
        return 1;
    }
    List node_list = NULL;
    while (arbre != NULL && (words_limit < 0 || word_extracted < words_limit))
    {
        word_extracted += extract_maximum_priority(&arbre, &node_list);
        if (generate_graphics)
        {
            snprintf(filename, sizeof(filename), "delete_%d.pdf", delete_count);
            generate_pdf(filename, arbre);
        }
        delete_count++;
    }
    sort_list(&node_list);
    if (export_list_file(export, node_list, word_extracted) != 0)
    {
        fprintf(stderr, "Error exporting list to file\n");
        fclose(export);
        free_tree(&arbre);
        return 1;
    }
    fclose(export);
    return 0;
}