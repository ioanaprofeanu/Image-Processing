// Profeanu Ioana, 313CA
// crop & select source file
// contains all commands used for selecting areas and cropping images
#include "auxiliary.h"

// function for selecting the entire area of the image
void selecting_all(int *selected, int *size)
{
	// save the selected coordinates in an array
	// lines
	// selected[0] < selected[1]
	selected[0] = 0;
	selected[1] = size[0];

	// columns
	// selected[2] < selected[3]
	selected[2] = 0;
	selected[3] = size[1];
	printf("Selected ALL\n");
}

// function for selecting a given area of the image
void selecting_area(int *selected, int *size, int x1,
					int y1, int x2, int y2)
{
	int col_0, col_1, lin_2, lin_3;
	// order coordinates by the ascending order of lines and columns
	if (x1 < x2) {
		col_0 = x1;
		col_1 = x2;
	} else {
		col_0 = x2;
		col_1 = x1;
	}

	if (y1 < y2) {
		lin_2 = y1;
		lin_3 = y2;
	} else {
		lin_2 = y2;
		lin_3 = y1;
	}

	// verify if the coordinates are valid
	if (col_0 < 0) {
		printf("Invalid set of coordinates\n");
		return;
	}
	if (lin_2 < 0) {
		printf("Invalid set of coordinates\n");
		return;
	}
	if (col_1 > size[1]) {
		printf("Invalid set of coordinates\n");
		return;
	}
	if (lin_3 > size[0]) {
		printf("Invalid set of coordinates\n");
		return;
	}
	if (col_0 == col_1 || lin_2 == lin_3) {
		printf("Invalid set of coordinates\n");
		return;
	}

	// save the selected area in an array

	// lines
	// selected[0] < selected[1]
	selected[0] = lin_2;
	selected[1] = lin_3;

	// columns
	// selected[2] < selected[3]
	selected[2] = col_0;
	selected[3] = col_1;

	if (lin_2 == col_0 && lin_3 == col_1) {
		printf("Selected %d %d %d %d\n", lin_2, col_0, lin_3, col_1);
		return;
	}
	printf("Selected %d %d %d %d\n", x1, y1, x2, y2);
}

// funtion for cropping the image
int **crop(int **image, int *selected, int *size, char *type)
{
	int size_c = size[1];
	int selected_0 = selected[0], selected_1 = selected[1];
	int selected_2 = selected[2], selected_3 = selected[3];

	// if the image is color, multiply the columns by 3
	if (strcmp(type, "P3") == 0 || strcmp(type, "P6") == 0) {
		size_c *= 3;
		selected_2 *= 3; selected_3 *= 3;
	}

	// dynamic allocation of auxiliary matrix
	int **aux_image;
	aux_image = alloc_matrix(selected_1 - selected_0, selected_3 - selected_2);
	// copy each element of the selected area to the auxiliary matrix
	for (int i = selected_0; i < selected_1; i++)
		for (int j = selected_2; j < selected_3; j++)
			aux_image[i - selected_0][j - selected_2] = image[i][j];

	// free and realloc the image matrix according to the new dimensions
	// and copy each element from the auxiliry matrix back to the original one
	free_matrix(size[2], image);
	image = alloc_matrix(selected_1 - selected_0, selected_3 - selected_2);
	for (int i = 0; i < selected_1 - selected_0; i++)
		for (int j = 0; j < selected_3 - selected_2; j++)
			image[i][j] = aux_image[i][j];

	free_matrix(selected_1 - selected_0, aux_image);

	// change the size of the original matrix and the selected area
	if (strcmp(type, "P3") == 0 || strcmp(type, "P6") == 0) {
		size[0] = selected_1 - selected_0;
		size[1] = (int)((selected_3 - selected_2) / 3);
	} else {
		size[0] = selected_1 - selected_0;
		size[1] = selected_3 - selected_2;
	}
	printf("Image cropped\n");

	// renew the selected area
	selected[0] = 0; selected[1] = size[0];
	selected[2] = 0; selected[3] = size[1];
	size[2] = size[0];
	return image;
}
