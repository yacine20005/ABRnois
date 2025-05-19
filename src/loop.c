#include "loop.h"

int loop_fetch_files(ABRnois *arbre, int *word_count, int argc, char *argv[], int generate_graphics, int start_index)
{
    int error = 0;
    char filename[FILENAME_SIZE];
    for (int i = start_index; i < argc; i++)
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
                    error = insert_ABRnois(arbre, buffer);
                    if (generate_graphics)
                    {
                        snprintf(filename, sizeof(filename), "insert_%d.pdf", *word_count);
                        generate_pdf(filename, *arbre);
                    }
                    if (error != 0)
                    {
                        fprintf(stderr, "Error inserting word %s\n", buffer);
                        free(buffer);
                        fclose(text_file);
                        free_tree(arbre);
                        return 1;
                    }
                    (*word_count)++;
                }
                clear_buffer(buffer);
            }
        }
        if (is_valid_word(buffer))
        {
            error = insert_ABRnois(arbre, buffer);
            if (generate_graphics)
            {
                snprintf(filename, sizeof(filename), "insert_%d.pdf", *word_count);
                generate_pdf(filename, *arbre);
            }
            if (error != 0)
            {
                fprintf(stderr, "Error inserting word %s\n", buffer);
                free(buffer);
                fclose(text_file);
                free_tree(arbre);
                return 1;
            }
            (*word_count)++;
        }
        free(buffer);
        fclose(text_file);
    }
    return 0;
}

void write_list_file(FILE *export, List node_list, int word_count)
{
    if (!node_list)
    {
        return;
    }
    write_list_file(export, node_list->suivant, word_count);
    double pourcentage = (100.0 * node_list->n->occurrence_count / word_count);
    fprintf(export, "%s %.2f%%\n", node_list->n->word, pourcentage);
}

int export_list_file(const char *filename, List node_list, int word_count)
{
    if (!filename || !node_list || word_count == 0)
    {
        return 1;
    }

    FILE *export = fopen(filename, "w");
    if (!export)
    {
        return 1;
    }

    write_list_file(export, node_list, word_count);
    fclose(export);
    return 0;
}
