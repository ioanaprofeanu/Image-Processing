// Profeanu Ioana, 313CA
// load & save source file
// contains all functions used for loading and saving images
#include "auxiliary.h"

// function for loading an image from an ascii file
int **load_ascii(char *file_name, int *size, char *type, int *selected)
{
	FILE *in = fopen(file_name, "rt");
	if (!in) {
		printf("Failed to load %s\n", file_name);
		return NULL;
	}

	// with a char, skip the first 3 lines of the file,
	// as the data has already been stored from funcion load
	char enter;
	int new_lines = 0;
	while (new_lines < 3) {
		fscanf(in, "%c", &enter);
		if (enter == '\n')
			new_lines++;
	}

	// if the image is color, multiply the columns number by 3
	// in order to store the rgb pixels
	int lines = size[0], columns = size[1];
	if (strcmp(type, "P3") == 0)
		columns *= 3;

	// read and store the pixels in the dinamically allocated
	// image matrix
	int **image = alloc_matrix(lines, columns);
	for (int i = 0; i < lines; i++)
		for (int j = 0; j < columns; j++)
			fscanf(in, "%d", &image[i][j]);

	fclose(in);
	// renew the selected area to be the entire image
	selected[0] = 0; selected[1] = size[0];
	selected[2] = 0; selected[3] = size[1];
	// set a back-up variable for the lines number
	// to make sure we will free the matrix corectly when needed
	size[2] = size[0];
	printf("Loaded %s\n", file_name);
	return image;
}

// function for loading an image from a binary file
int **load_binary(char *file_name, int *size, char *type, int *selected)
{
	FILE *in = fopen(file_name, "rb");
	if (!in) {
		printf("Failed to load %s\n", file_name);
		return NULL;
	}

	// with a char, skip the first 3 lines of the file,
	// as the data has already been stored from function load
	char enter;
	int new_lines = 0;
	while (new_lines < 3) {
		fread(&enter, sizeof(char), 1, in);
		if (enter == '\n')
			new_lines++;
	}

	int lines = size[0], columns = size[1];
	// if the image is color, multiply the columns number by 3
	// in order to store the rgb pixels
	if (strcmp(type, "P6") == 0)
		columns *= 3;

	// as the file is binary, read each number using a char
	// and store it in the dynamically allocated image matrix
	unsigned char c;
	int **image = alloc_matrix(lines, columns);
	for (int i = 0; i < lines; i++)
		for (int j = 0; j < columns; j++) {
			fread(&c, sizeof(unsigned char), 1, in);
			image[i][j] = (int)c;
		}

	fclose(in);
	// renew the selected area to be the entire image
	selected[0] = 0; selected[1] = size[0];
	selected[2] = 0; selected[3] = size[1];
	// set a back-up variable for the lines number
	// to make sure we will free the matrix corectly when needed
	size[2] = size[0];
	size[2] = size[0];
	printf("Loaded %s\n", file_name);
	return image;
}

// function for reading the information about the image
// it returns 1 if the file exists, 0 if it doesn't
int load(char *file_name, int *size, char *type, int *max_value)
{
	FILE *in = fopen(file_name, "rt");
	if (!in) {
		printf("Failed to load %s\n", file_name);
		return 0;
	}

	// read and store the magic number of the image,
	// the size of the image and the maximum value of pixels
	// size[0] -> lines, size[1] -> columns
	fscanf(in, "%s %d %d %d", type, &size[1], &size[0], &max_value[0]);
	fclose(in);
	return 1;
}

// function for saving the image as a binary file
void save_binary(char *save_name, int **image, int *size,
				 char *type, int *max_value)
{
	int lines = size[0], columns = size[1];
	if (strcmp(type, "P3") == 0 || strcmp(type, "P6") == 0)
		columns *= 3;

	// if the image originally has the magic number for ascii file,
	// change its magic number to the binary one
	if (strcmp(type, "P3") == 0)
		strcpy(type, "P6");

	if (strcmp(type, "P2") == 0)
		strcpy(type, "P5");

	FILE *out = fopen(save_name, "wb");
	if (!out) {
		printf("No image loaded\n");
		return;
	}

	// write the image details and the matrix in the file
	fprintf(out, "%s\n%d %d\n%d\n", type, size[1], size[0], max_value[0]);

	// write the elements of the image with a char, as the file is binary
	unsigned char c;
	for (int i = 0; i < lines; i++)
		for (int j = 0; j < columns; j++) {
			c = (unsigned char)image[i][j];
			fwrite(&c, sizeof(unsigned char), 1, out);
		}

	fclose(out);
	printf("Saved %s\n", save_name);
}

// function for saving the image as an ascii file
void save_ascii(char *save_name, int **image, int *size,
				char *type, int *max_value)
{
	int lines = size[0], columns = size[1];
	if (strcmp(type, "P3") == 0 || strcmp(type, "P6") == 0)
		columns *= 3;

	// if the image originally has the magic number for binary file,
	// change its magic number to the ascii one
	if (strcmp(type, "P6") == 0)
		strcpy(type, "P3");

	if (strcmp(type, "P5") == 0)
		strcpy(type, "P2");

	FILE *out = fopen(save_name, "wt");
	if (!out) {
		printf("No image loaded\n");
		return;
	}

	// write the image details and the matrix in the file
	fprintf(out, "%s\n%d %d\n%d\n", type, size[1], size[0], max_value[0]);

	for (int i = 0; i < lines; i++) {
		for (int j = 0; j < columns; j++)
			fprintf(out, "%d ", image[i][j]);
		fprintf(out, "\n");
	}

	fclose(out);
	printf("Saved %s\n", save_name);
}
