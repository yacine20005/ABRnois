#ifndef ABRNOIS_H
#define ABRNOIS_H

typedef struct _node
{
    char *mot;
    int nb_occ;
    struct _node *fg, *fd;
} Node, *ABRnois ;

#endif // ABRNOIS_H