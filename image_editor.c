// Profeanu Ioana, 313CA
// main source file
#include "commands.h"

// in main, we read the command from stdin, store it in a string,
// get each token of the command and verify the value of the first token;
// depending on this value, we further evaluate each of the next tokens
int main(void)
{
	int **image, loaded = 0, max_value[MINT], selected[MINT], size[MINT];
	char type[CMIN], command[CMAX], tokens[CMIN][CMAX];
	while (1) { // read command from stdin, process and parse it
		fgets(command, CMAX, stdin); remove_trailing_newline(command);
		int no_tokens = get_tokens(command, tokens);
		if (strcmp(tokens[0], "LOAD") == 0) {
			if (load(tokens[1], size, type, max_value)) { // if the file exists
				if (loaded == 1 && size[2] != 0)
					free_matrix(size[2], image); // free if already loaded
				if (strcmp(type, "P2") == 0 || strcmp(type, "P3") == 0)
					image = load_ascii(tokens[1], size, type, selected);
				else if (strcmp(type, "P5") == 0 || strcmp(type, "P6") == 0)
					image = load_binary(tokens[1], size, type, selected);
				loaded = 1; // control variable for verifying the load state
			} else { // if the file doesn't exist
				if (loaded == 1 && size[2] != 0)
					free_matrix(size[2], image); // free if already loaded
				loaded = 0;
			}
		} else if (strcmp(tokens[0], "SAVE") == 0) {
			if (loaded == 0) {
				printf("No image loaded\n");
			} else { // check if the file should be saved binary or ascii
				if (no_tokens == 1 ||
					(no_tokens == 2 && strcmp(tokens[2], "ascii") != 0)) {
					save_binary(tokens[1], image, size, type, max_value);
				} else {
					save_ascii(tokens[1], image, size, type, max_value);
				}
			}
		} else if (strcmp(tokens[0], "SELECT") == 0) {
			if (loaded == 0) {
				printf("No image loaded\n");
			} else { //check the selection type
				if (strcmp(tokens[1], "ALL") == 0) {
					selecting_all(selected, size);
				} else if (no_tokens == 4 && tokens[1][0] == '-') {
					printf("Invalid set of coordinates\n");
				} else if (no_tokens == 4 && isdigit(tokens[4][0]) != 0) {
					int x1 = atoi(tokens[1]); int y1 = atoi(tokens[2]);
					int x2 = atoi(tokens[3]); int y2 = atoi(tokens[4]);
					selecting_area(selected, size, x1, y1, x2, y2);
				} else if (no_tokens != 4 || no_tokens != 1) {
					printf("Invalid command\n");
				}
			}
		} else if (strcmp(tokens[0], "ROTATE") == 0) {
			if (loaded == 0) {
				printf("No image loaded\n");
			} else { // get angle value as a number
				int angle = atoi(tokens[1]);
				if (selected[0] == 0 && selected[1] == size[0] &&
					selected[2] == 0 && selected[3] == size[1]) { // if ALL
					int k = verify_angle_all(angle);
					for (int i = 0; i < k; i++)
						image = rotate_all(image, size, selected, type);
				} else { // if only an area
					rotate_area(angle, image, selected, type);
				}
			}
		} else if (strcmp(tokens[0], "CROP") == 0) {
			if (loaded == 0)
				printf("No image loaded\n");
			else
				image = crop(image, selected, size, type); // crop image
		} else if (strcmp(tokens[0], "GRAYSCALE") == 0) {
			grayscale_filter(image, selected, type, loaded); // apply filter
		} else if (strcmp(tokens[0], "SEPIA") == 0) {
			sepia_filter(image, selected, type, max_value, loaded); //apply
		} else if (strcmp(tokens[0], "EXIT") == 0) {
			if (loaded == 0) {
				printf("No image loaded"); return 0;
			}
			free_matrix(size[2], image); return 0; // free if already loaded
		} else {
			printf("Invalid command\n");
		}
	}
}
