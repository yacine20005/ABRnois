#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "abrnois.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/**
 * @brief Open or create a DOT file for writing.
 *
 * @param filename the name of the file to open
 * @return FILE* the file pointer
 */
FILE *open_dot_file(char *);

/**
 * @brief Write the start of the DOT file.
 *
 * @param f the file pointer to write the DOT format to
 *
 */
void write_start(FILE *);

/**
 * @brief Draw a tree in DOT format by recursively traversing it.
 *
 * @param f the file pointer to write the DOT format to
 * @param tree the tree to draw
 */
void draw_tree(FILE *, ABRnois);

/**
 * @brief Write the end of the DOT file.
 *
 * @param f the file pointer to write the end of the DOT format to
 *
 */
void write_end(FILE *);

/**
 * @brief Generate a DOT file for the given tree.
 *
 * @param out the file pointer to write the DOT format to
 * @param a the tree to draw
 */
void generate_dot(FILE *, ABRnois);

/**
 * @brief Generate a PDF file from the DOT file.
 *
 * @param filename the name of the output PDF file and of the DOT file
 * @param a the tree to draw
 *
 * @return int 0 on success, 1 on failure
 */
int generate_pdf(char *, ABRnois);

#endif // ABRNOIS_H