#ifndef LIST_H
#define LIST_H

#include "abrnois.h"

typedef struct _cell {
    Node * n;
    struct _cell * suivant;
} Cell , * List;

#endif // LIST_H