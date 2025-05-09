#include "graphics.h"

FILE *open_dot_file(char *file_path)
{
    FILE *f = fopen(file_path, "w");

    if (!f)
    {
        fprintf(stderr, "Error opening file\n");
        return NULL;
    }

    return f;
}

void write_start(FILE *file)
{
    fprintf(file, "digraph arbre {\n");
    fprintf(file, "    node [shape=record, height=.1]\n");
    fprintf(file, "    edge [tailclip=false, arrowtail=dot, dir=both];\n\n");
}

void draw_tree(FILE *file, ABRnois tree)
{
    if (!tree)
        return;

    fprintf(file, "    n%p [label=\"<fg> | {%s | %d} | <fd>\"];\n", tree, tree->mot, tree->nb_occ);
    draw_tree(file, tree->fg);
    draw_tree(file, tree->fd);

    if (tree->fg)
        fprintf(file, "    n%p:fg -> n%p;\n", tree, tree->fg);

    if (tree->fd)
        fprintf(file, "    n%p:fd -> n%p;\n", tree, tree->fd);
}

void write_end(FILE *file)
{
    fprintf(file, "}\n");
}

void generate_dot(FILE *file, ABRnois tree)
{
    write_start(file);
    draw_tree(file, tree);
    write_end(file);
}

int generate_pdf(char *filename, ABRnois tree)
{
    char dot_path[100];
    char pdf_path[100];
    char cmd[256];

    snprintf(dot_path, sizeof(dot_path), "data/dot/%s.dot", filename);
    snprintf(pdf_path, sizeof(pdf_path), "data/pdf/%s.pdf", filename);

    FILE *out = fopen(dot_path, "w");
    if (!out)
    {
        printf("Error opening DOT file for writing\n");
        return 1;
    }
    generate_dot(out, tree);
    fclose(out);

    snprintf(cmd, sizeof(cmd), "dot -Tpdf %s -o %s", dot_path, pdf_path);
    system(cmd);

    return 0;
}