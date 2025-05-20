#ifndef LOOP_H
#define LOOP_H

#include "abrnois.h"
#include "fetch.h"
#include "list.h"
#include "graphics.h"

/**
 * @brief Processes files and inserts words into the tree.
 * 
 * @param tree Pointer to the ABR
 * @param word_count Pointer to the word counter
 * @param argc Number of arguments
 * @param argv Array of arguments
 * @param generate_graphics Flag to generate graphics
 * @param start_index Index of the first corpus file in argv
 * @return int 0 on success, 1 on error
 */
int loop_fetch_files(ABRnois *, int *, int , char *[], int , int);

/**
 * @brief Exports the list of words from the ABR to a list
 * 
 * @param tree Pointer to the ABR
 * @param export_filename Name of the export file
 * @return List The list of words
 */
List loop_arbre_list(ABRnois *, char *);

/**
 * @brief Recursively writes words in the descending order of their occurrence count to a file.
 *
 * @param export Pointer to the file to write to.
 * @param node_list Linked list of nodes containing words and their occurrence counts.
 * @param word_count Total number of words for percentage calculation.
 */
void write_list_file(FILE *, List, int);

/**
 * @brief Open a file and write the list of words contained in the linked list to a file.
 *
 * @param filename Name of the output file.
 * @param node_list Linked list of nodes containing words and their occurrence counts.
 * @param word_count Total number of words for percentage calculation.
 * @return 0 on success, 1 on error (invalid parameter or file open failure).
 */
int export_list_file(const char *, List, int);

#endif // LOOP_H