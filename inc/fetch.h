#ifndef FETCH_H
#define FETCH_H

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

#define BUFFER_SIZE 256
#define FILENAME_SIZE 256

/**
 * @brief Permet de vérifier si un caractère est valide pour un mot
 *
 * @param c Le caractère à vérifier
 * @return int 1 si le caractère est valide, 0 sinon
 */
int is_char(char);

/**
 * @brief Convertit un caractère en minuscule
 *
 * @param c Le caractère à convertir
 * @return char Le caractère converti
 */
char lower(char);

/**
 * @brief Initialise un buffer
 *
 * @return char* buffer initialisé
 */
char *init_buffer();

/**
 * @brief Ajoute un caractère à un buffer
 * @param char* Buffer à modifier
 * @param char Caractère à ajouter
 *
 * @return char* Buffer modifié
 */
char *add_buffer(char *, char);

/**
 * @brief Vide le buffer
 * @param char* Buffer à vider
 *
 * @return char* Buffer vidé
 */
char *clear_buffer(char *);

/**
 * @brief Vérifie si un mot est valide (ne contient que des lettres)
 * @param char* Mot à vérifier
 *
 * @return int 1 si valide, 0 sinon
 */
int is_valid_word(char *);

#endif // FETCH_H