#include "fetch.h"

int is_char(char c)
{
    return isalpha((unsigned char)c);
}

char lower(char c)
{
    return tolower((unsigned char)c);
}

char *init_buffer()
{
    char *buffer = calloc(BUFFER_SIZE, sizeof(char));
    if (buffer == NULL)
    {
        fprintf(stderr, "Erreur d'allocation du buffer\n");
        return NULL;
    }
    return buffer;
}

char *add_buffer(char *buffer, char c)
{
    size_t len = strlen(buffer);
    if (len >= BUFFER_SIZE - 1)
    {
        fprintf(stderr, "Buffer plein\n");
        return buffer;
    }
    buffer[len] = lower(c);
    buffer[len + 1] = '\0';
    return buffer;
}

char *clear_buffer(char *buffer)
{
    buffer[0] = '\0';
    return buffer;
}

int is_valid_word(char *word)
{
    if (word == NULL || *word == '\0')
        return 0;

    for (int i = 0; word[i] != '\0'; i++)
    {
        if (!is_char(word[i]))
            return 0;
    }
    return 1;
}