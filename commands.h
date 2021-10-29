// Profeanu Ioana, 313CA
// header linked to the sources of the commands files
#ifndef COMMANDS_H
#define COMMANDS_H

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>
#include "auxiliary.h"

#define CMAX 70
#define CMIN 30
#define MINT 5

int **load_ascii(char *file_name, int *size, char *type, int *selected);

int **load_binary(char *file_name, int *size, char *type, int *selected);

int load(char *file_name, int *size, char *type, int *max_value);

void save_binary(char *save_name, int **image, int *size,
				 char *type, int *max_value);

void save_ascii(char *save_name, int **image, int *size,
				char *type, int *max_value);

void selecting_all(int *selected, int *size);

void selecting_area(int *selected, int *size, int x1,
					int y1, int x2, int y2);

void rotate_area_grayscale_90_left(int **image, int *selected);

void rotate_area_color_90_left(int **image, int *selected);

void rotate_area_90_left(int **image, int *selected, char *type);

void rotate_area(int angle, int **image, int *selected, char *type);

int **rotate_all(int **image, int *size, int *selected, char *type);

int verify_angle_all(int angle);

int **crop(int **image, int *selected, int *size, char *type);

void grayscale_filter(int **image, int *selected, char *type, int loaded);

void sepia_filter(int **image, int *selected, char *type,
				  int *max_value, int loaded);

#endif
