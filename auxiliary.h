// Profeanu Ioana, 313CA
// header linked to the auxiliary functions source file
#ifndef AUXILIARY_H
#define AUXILIARY_H

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

#define CMAX 70
#define CMIN 30
#define MINT 5

void remove_trailing_newline(char s[]);

int minim(int a, int b);

int get_tokens(char *command, char tokens[][CMAX]);

int **alloc_matrix(int n, int m);

void free_matrix(int n, int **a);

#endif
