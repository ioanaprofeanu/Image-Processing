// Profeanu Ioana, 313CA
// auxiliary functions source file
// it contains all functions needed for basic operations,
// used in solving the image editing process
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define CMAX 70
#define TRUE 1

// function which removes trailing newline out of a string
void remove_trailing_newline(char s[])
{
	int len = strlen(s);
	// verify if there is a trailing new line
	int verify = 0;
	for (int i = 0; i < len; i++) {
		if (s[i] == '\n')
			verify = 1;
	}
	// if there is, replace it with string terminator
	if (verify == 1) {
		if (len > 0)
			s[len - 1] = '\0';
	}
}

// function which returns the lower number
int minim(int a, int b)
{
	if (a > b)
		return b;
	else
		return a;
}

// function which counts and extracts the tokens out of a string
// and stores them in a matrix of strings
int get_tokens(char *command, char tokens[][CMAX])
{
	int no_tokens = 0, j = 0;
	// go through each character of the string and store it;
	// when encountering space, go to the next token
	for (int i = 0; TRUE; i++) {
		if (command[i] != ' ') {
			tokens[no_tokens][j++] = command[i];
		} else {
			tokens[no_tokens][j++] = '\0';
			no_tokens++;
			j = 0;
		}
		if (command[i] == '\0')
			break;
	}
	return no_tokens;
}

// function for dynamic allocation of a matrix
int **alloc_matrix(int lines, int columns)
{
	// alloc lines
	int **matrix = (int **)calloc(lines, sizeof(int *));
	// verify the allocation
	if (!matrix) {
		free(matrix);
		return NULL;
	}

	// alloc columns
	for (int i = 0; i < lines; i++) {
		matrix[i] = calloc(columns, sizeof(int));

		if (!matrix[i]) {
			while (--i >= 0)
				free(matrix[i]);
			free(matrix);
			return NULL;
		}
	}
	return matrix;
}

// function for freeing the memory used by a matrix
void free_matrix(int lines, int **matrix)
{
	for (int i = 0; i < lines; i++)
		free(matrix[i]);
	free(matrix);
}
