#ifndef LOOP_H
#define LOOP_H

#include "abrnois.h"
#include "fetch.h"
#include "list.h"
#include "graphics.h"

/**
 * @brief Processes corpus files and inserts words into the ABR
 * @param arbre Pointer to the ABR
 * @param word_count Pointer to the word counter
 * @param argc Number of arguments
 * @param argv Array of arguments
 * @param generate_graphics Flag to generate graphics
 * @param start_index Index of the first corpus file in argv
 * @return int 0 on success, 1 on error
 */
int loop_fetch_files(ABRnois *arbre, int *word_count, int argc, char *argv[], int generate_graphics, int start_index);

/**
 * @brief Exports the list of words from the ABR to a list
 * @param arbre Pointer to the ABR
 * @param export_filename Name of the export file
 * @return List The list of words
 */
List loop_arbre_list(ABRnois *arbre, char *export_filename);

/**
 * @brief Recursively writes words and their occurrence percentage to a file.
 *
 * @param export Pointer to the file to write to.
 * @param node_list Linked list of nodes containing words and their occurrence counts.
 * @param word_count Total number of words for percentage calculation.
 */
void write_list_file(FILE *export, List node_list, int word_count);

/**
 * @brief Exports a list of words and their occurrence percentage to a file.
 *
 * @param filename Name of the output file.
 * @param node_list Linked list of nodes containing words and their occurrence counts.
 * @param word_count Total number of words for percentage calculation.
 * @return 0 on success, 1 on error (invalid parameter or file open failure).
 */
int export_list_file(const char *filename, List node_list, int word_count);

#endif // LOOP_H