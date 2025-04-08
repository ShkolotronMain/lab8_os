#include <stdio.h>
#include <stdlib.h>
#include "veclib.h"

void print_vec(int* vec, int size)
{
    fputs("[", stdout);
    for (int i=0; i<size; i++)
    {
        printf("%-3.d", vec[i]);
        if (i<size-1)
            fputs(", ", stdout);
    }
    fputs("]\n", stdout);
}

void print_matrix(int** mat, int lines, int cols)
{
    fputs("[\n", stdout);
    for (int i=0; i<lines; i++)
    {
        fputs(" ", stdout);
        print_vec(mat[i], cols);
    }
    fputs("]\n", stdout);
}

void free_matrix(int** mat, int lines)
{
    for (int i=0; i<lines; i++)
        free(mat[i]);
    free(mat);
}