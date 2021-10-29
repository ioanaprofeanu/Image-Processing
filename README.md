Copyright @Profeanu Ioana, 313CA

Image Processing Implementation in C
-------------------------------------------------------------------------------
* Read commands from stdin:
  * in a while loop, read from stdin and store the commands in a string;
  * remove the newline at the end of the string and extract each token in a
 matrix of strings; verify the value of the first token of the command; if it
 valid, parse the next tokens;
  * if a command is incorect or there is no image loaded beforehand, print the
 specific messages;
-------------------------------------------------------------------------------
* LOAD command:
  * in a function, we first verify if the file given from stdin exists, and if
 it does, no matter the type of file, we read and store the magic number, size
 and maximum pixel value; the size is stored in an array;
  * in main, we keep a control variable to check if there is an image loaded
 or not; if there is, we free the matrix in which it is stored; we then check
 the magic word extracted from the file to know its type;
  * for each type of file, in two functions we read and dynamically store the
 pixels in a matrix; if the image is color, we multiply the size of columns by
 3 and store the rgb values; in this case, a pixel is represented by 3
 consecutive values;
  * if the given file doesn't exist and there is an already loaded image, we
 free the memory of the matrix and reinitialize the control value;
-------------------------------------------------------------------------------
* SAVE command:
  * if the number of tokens is equal to 1 or equal to 2 but the 3rd token is
 different than the word "ascii", we save the file binary, else, we save it in
 ascii format;
  * in two functions, we save the image matrix in a binary or ascii file,
 changing the magic number if switching from an initially binary saved image
 to an ascii one or vice versa;
-------------------------------------------------------------------------------
* SELECT command:
  * if the second token is "ALL", using a function we store the coordinates of
 the entire image
  * else, if there are 5 tokens in total and none of them is negative nor the
 last 4 are numbers, we convert the last 4 tokens in numbers;
  * in a function, we compare each value and store it in ascending order
  * in both cases, the selected coordinates are stored in an array
-------------------------------------------------------------------------------
* ROTATE command:
  * convert the second token to a number value; if the already selected area is
 the entire image, we rotate the entire picture; else, we rotate only the
 selected area;
  * Rotation algorithm:
   - by inverting the columns of the transposed image matrix, we obtain the
  image rotated by -90 degrees; for each angle, we repeat the process depending
  on the value: (-90, 270 -> once; 180, -180 -> twice; 90,-270 -> 3 times; 0,
  360 -> don't rotate at all :) );
   - in a dynamically stored auxiliary matrix, we store the transposed matrix
  and then reverse its columns; next, we free and resize the original matrix,
  then copy to it the values stored in the auxiliary matrix;
  * for full image rotation, a function checks if the angle is correct
 and returns the number of times the algorithm has to be applied; in another
 function, the algorithm is executed for both color or grayscale images;
  * for area rotation, a function checks if the angle is correct and the
 area is square; another function checks if the image is color or grayscale,
 and two other functions execute the rotation algorithm for each type of image;
-------------------------------------------------------------------------------
* CROP command:
  * in a function, we copy the selected size in a dynamically stored auxiliary
 matrix, then free and resize the original matrix and copy the elements from
 the auxiliary matrix back to the original one; renew the selected area;
-------------------------------------------------------------------------------
* GRAYSCALE AND SEPIA commands:
  * if the first token is SEPIA or GRAYSCALE, two functions verify if the image
 is color and change the rgb values for each case using the specific formula;
-------------------------------------------------------------------------------
* EXIT command:
  * we free the image matrix (if it exists) and gracefully end the program;
-------------------------------------------------------------------------------
