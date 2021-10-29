// Profeanu Ioana, 313CA
// filters source file
// contains all functions used for applying filters on images
#include "auxiliary.h"

// function for applying the grayscale filter
void grayscale_filter(int **image, int *selected, char *type, int loaded)
{
	// verify if an image is loaded
	if (loaded == 0) {
		printf("No image loaded\n");
		return;
	}

	// verify if the image is color
	if (strcmp(type, "P2") == 0 || strcmp(type, "P5") == 0) {
		printf("Grayscale filter not available\n");
		return;
	}

	// for the selected area, change the rgb values of each pixel
	// according to the grayscale formula
	if (strcmp(type, "P3") == 0 || strcmp(type, "P6") == 0) {
		for (int i = selected[0]; i < selected[1]; i++)
			for (int j = selected[2] * 3; j < selected[3] * 3; j += 3) {
				int sum = (double)(image[i][j] + image[i][j + 1]
								+ image[i][j + 2]);
				sum = (double)(sum / 3);
				image[i][j] = round(sum);
				image[i][j + 1] = round(sum);
				image[i][j + 2] = round(sum);
			}
	}
	printf("Grayscale filter applied\n");
}

// function for applying the sepia filter
void sepia_filter(int **image, int *selected, char *type,
				  int *max_value, int loaded)
{
	// verify if an image is loaded
	if (loaded == 0) {
		printf("No image loaded\n");
		return;
	}

	// verify if the image is color
	if (strcmp(type, "P2") == 0 || strcmp(type, "P5") == 0) {
		printf("Sepia filter not available\n");
		return;
	}

	// for the selected area, change the rgb values of each pixel
	// according to the sepia formula
	if (strcmp(type, "P3") == 0 || strcmp(type, "P6") == 0) {
		for (int i = selected[0]; i < selected[1]; i++)
			for (int j = selected[2] * 3; j < selected[3] * 3; j += 3) {
				double sum_r = (double)(0.393 * image[i][j] + 0.769
						* image[i][j + 1] + 0.189 * image[i][j + 2]);
				double sum_g = (double)(0.349 * image[i][j] + 0.686
							* image[i][j + 1] + 0.168 * image[i][j + 2]);
				double sum_b = (double)(0.272 * image[i][j] + 0.534
							* image[i][j + 1] + 0.131 * image[i][j + 2]);
				// ensure the new value doesn't exceed the maximum value
				image[i][j] = minim(max_value[0], round(sum_r));
				image[i][j + 1] = minim(max_value[0], round(sum_g));
				image[i][j + 2] = minim(max_value[0], round(sum_b));
			}
	}
	printf("Sepia filter applied\n");
}
