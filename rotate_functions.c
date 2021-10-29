// Profeanu Ioana, 313CA
// totate source file
// contains all commands used for rotating images
#include "auxiliary.h"

// functions for rotating a selected area 90 degrees to the left
// depending on the image type
void rotate_area_grayscale_90_left(int **image, int *selected)
{
	int selected_0 = selected[0], selected_1 = selected[1];
	int selected_2 = selected[2], selected_3 = selected[3];

	// dynamic allocation of auxiliary matrix
	int **aux_image;
	aux_image = alloc_matrix(selected_1 - selected_0, selected_3 - selected_2);

	// copy to auxiliary matrix the transpose of the image matrix
	for (int i = selected_0; i < selected_1; i++) {
		for (int j = selected_2; j < selected_3; j++)
			aux_image[j - selected_2][i - selected_0] = image[i][j];
	}
	// reverse each column of the auxiliary matrix
	int n = selected_1 - selected_0;
	for (int i = 0; i < n / 2; i++) {
		for (int j = 0; j < n; j++) {
			int aux = aux_image[i][j];
			aux_image[i][j] = aux_image[n - i - 1][j];
			aux_image[n - i - 1][j] = aux;
		}
	}

	// copy to image matrix the auxiliary matrix
	for (int i = selected_0; i < selected_1; i++)
		for (int j = selected_2; j < selected_3; j++)
			image[i][j] = aux_image[i - selected_0][j - selected_2];

	// free auxiliary matrix
	free_matrix(selected_1 - selected_0, aux_image);
}

void rotate_area_color_90_left(int **image, int *selected)
{
	int selected_0 = selected[0], selected_1 = selected[1];
	int selected_2 = selected[2] * 3, selected_3 = selected[3] * 3;

	// dynamic allocation of auxiliary matrix
	int **aux_image;
	aux_image = alloc_matrix(selected_1 - selected_0, selected_3 - selected_2);

	// copy to auxiliary matrix the image matrix
	for (int i = selected_0; i < selected_1; i++)
		for (int j = selected_2; j < selected_3; j++)
			aux_image[i - selected_0][j - selected_2] = image[i][j];

	int lines = selected[1] - selected[0];
	// get transpose of the auxiliary matrix, copying the rgb values 3 by 3
	for (int i = 0; i < lines; i++) {
		for (int j = i + 1; j < lines; j++) {
			int aux = aux_image[i][j * 3];
			aux_image[i][j * 3] = aux_image[j][i * 3];
			aux_image[j][i * 3] = aux;

			aux = aux_image[i][j * 3 + 1];
			aux_image[i][j * 3 + 1] = aux_image[j][i * 3 + 1];
			aux_image[j][i * 3 + 1] = aux;

			aux = aux_image[i][j * 3 + 2];
			aux_image[i][j * 3 + 2] = aux_image[j][i * 3 + 2];
			aux_image[j][i * 3 + 2] = aux;
		}
	}
	// reverse each column of the auxiliary matrix
	for (int i = 0; i < lines / 2; i++) {
		for (int j = 0; j < lines * 3; j++) {
			int aux = aux_image[i][j];
			aux_image[i][j] = aux_image[lines - i - 1][j];
			aux_image[lines - i - 1][j] = aux;
		}
	}

	// copy to image matrix the auxiliary matrix
	for (int i = selected_0; i < selected_1; i++)
		for (int j = selected_2; j < selected_3; j++)
			image[i][j] = aux_image[i - selected_0][j - selected_2];

	// free auxiliary matrix
	free_matrix(selected_1 - selected_0, aux_image);
}

// function which checks if the image is grayscale or color
void rotate_area_90_left(int **image, int *selected, char *type)
{
	if (strcmp(type, "P3") == 0 || strcmp(type, "P6") == 0)
		rotate_area_color_90_left(image, selected);
	else
		rotate_area_grayscale_90_left(image, selected);
}

// function which verifies the angle and rotates the area
// a specific number of times 90 degrees to the left
void rotate_area(int angle, int **image, int *selected, char *type)
{
	int multiply;
	// verify if angle is a multiple of 90
	if (abs(angle) % 90 == 0 && abs(angle) >= 0 && abs(angle) <= 360) {
		// verify if the area is square
		if (abs(selected[1] - selected[0]) == abs(selected[3] - selected[2])) {
			if (angle == 0 || angle == 360 || angle == -360) {
				printf("Rotated %d\n", angle);
				return;
			}
			if (angle == -90 || angle == 270)
				multiply = 1;
			if (angle == 180 || angle == -180)
				multiply = 2;
			if (angle == 90 || angle == -270)
				multiply = 3;

			for (int i = 0; i < multiply; i++)
				rotate_area_90_left(image, selected, type);

			printf("Rotated %d\n", angle);
		} else {
			printf("The selection must be square\n");
			return;
		}
	} else {
		printf("Unsupported rotation angle\n");
		return;
	}
}

// function for rotating the entire image 90 degrees to the left
int **rotate_all(int **image, int *size, int *selected, char *type)
{
	// check if the image is grayscale
	if (strcmp(type, "P2") == 0 || strcmp(type, "P5") == 0) {
		// dynamic allocation of auxiliary matrix
		int size_l = size[1], size_c = size[0];
		int **aux_image = alloc_matrix(size_l, size_c);

		// copy to auxiliary matrix the transpose of the image matrix
		for (int i = 0; i < size_l; i++)
			for (int j = 0; j < size_c; j++)
				aux_image[i][j] = image[j][i];
		// reverse each column of the auxiliary matrix
		for (int i = 0; i < size_l / 2; i++) {
			for (int j = 0; j < size_c; j++) {
				int aux = aux_image[i][j];
				aux_image[i][j] = aux_image[size_l - i - 1][j];
				aux_image[size_l - i - 1][j] = aux;
			}
		}
		// free and realloc the image matrix according to
		// the new dimensions and copy each element from
		// the auxiliry matrix back to the original one
		free_matrix(size[2], image);
		size[0] = size_l;
		size[1] = size_c;
		size[2] = size_l;
		image = alloc_matrix(size[0], size[1]);
		for (int i = 0; i < size[0]; i++)
			for (int j = 0; j < size[1]; j++)
				image[i][j] = aux_image[i][j];

		// free the auxiliary matrix and renew the selected area
		free_matrix(size_l, aux_image);
		selected[0] = 0; selected[1] = size[0];
		selected[2] = 0; selected[3] = size[1];
		return image;
	}

	// check if the image is color
	if (strcmp(type, "P3") == 0 || strcmp(type, "P6") == 0) {
		// dynamic allocation of auxiliary matrix
		int size_l = size[1], size_c = size[0];
		int **aux_image = alloc_matrix(size_l, size_c * 3);

		// copy to auxiliary matrix the transpose of the image matrix
		for (int i = 0; i < size_l; i++) {
			for (int j = 0; j < size_c; j++) {
				aux_image[i][j * 3] = image[j][i * 3];
				aux_image[i][j * 3 + 1] = image[j][i * 3 + 1];
				aux_image[i][j * 3 + 2] = image[j][i * 3 + 2];
			}
		}
		// reverse each column of the auxiliary matrix
		for (int i = 0; i < size_l / 2; i++) {
			for (int j = 0; j < size_c * 3; j++) {
				int aux = aux_image[i][j];
				aux_image[i][j] = aux_image[size_l - i - 1][j];
				aux_image[size_l - i - 1][j] = aux;
			}
		}

		// free and realloc the image matrix according to
		// the new dimensions and copy each element from
		// the auxiliry matrix back to the original one
		free_matrix(size[2], image);
		size[0] = size_l;
		size[1] = size_c;
		size[2] = size_l;
		image = alloc_matrix(size[0], size[1] * 3);
		for (int i = 0; i < size[0]; i++)
			for (int j = 0; j < size[1] * 3; j++)
				image[i][j] = aux_image[i][j];

		// free the auxiliary matrix and renew the selected area
		free_matrix(size_l, aux_image);
		selected[0] = 0; selected[1] = size[0];
		selected[2] = 0; selected[3] = size[1];
		return image;
	}
	return image;
}

// function which verifies the angle and returns the number of
// times the entire image has to be rotated by 90 degrees to the left
int verify_angle_all(int angle)
{
	// verify if angle is a multiple of 90
	if (abs(angle) % 90 == 0 && abs(angle) >= 0 && abs(angle) <= 360) {
		printf("Rotated %d\n", angle);

		if (angle == 0 || angle == 360 || angle == -360)
			return 0;
		if (angle == -90 || angle == 270)
			return 1;
		if (angle == 180 || angle == -180)
			return 2;
		if (angle == 90 || angle == -270)
			return 3;
	} else {
		printf("Unsupported rotation angle\n");
		return 0;
	}
	return 0;
}
