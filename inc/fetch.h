#ifndef FETCH_H
#define FETCH_H

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

#define BUFFER_SIZE 256
#define FILENAME_SIZE 256

/**
 * @brief Checks if a character is valid for a word
 *
 * @param c The character to check
 * @return int 1 if the character is valid, 0 otherwise
 */
int is_char(char);

/**
 * @brief Converts a character to lowercase
 *
 * @param c The character to convert
 * @return char The converted character
 */
char lower(char);

/**
 * @brief Initializes a buffer
 *
 * @return char* Initialized buffer
 */
char *init_buffer();

/**
 * @brief Adds a character to a buffer
 * @param char* Buffer to modify
 * @param char Character to add
 *
 * @return char* Modified buffer
 */
char *add_buffer(char *, char);

/**
 * @brief Clears the buffer
 * @param char* Buffer to clear
 *
 * @return char* Cleared buffer
 */
char *clear_buffer(char *);

/**
 * @brief Checks if a word is valid (contains only letters)
 * @param char* Word to check
 *
 * @return int 1 if valid, 0 otherwise
 */
int is_valid_word(char *);

#endif // FETCH_H