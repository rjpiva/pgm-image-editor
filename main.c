
/***************************************************************/
/**                                                           **/
/**   Renan de Jesus Piva           6886688                   **/
/**   Exercício-Programa 04                                   **/
/**   Professor: Nina S. T. Hitara                            **/
/**   Turma: 07                                               **/
/**                                                           **/
/***************************************************************/

/*/////////////////////////////////////////////////////////////////
//                                                               //
//  The code is divided into three parts                         //
//                                                               //
//     Part I.   Function prototypes                             //
//     Part II.  Main program (main)                             //
//     Part III. Function declarations                           //
//                 mandatory functions                           //
//                 auxiliary functions                           //
//                 given functions                               //
//                                                               //
//////////////////////////////////////////////////////////////// */

#include <stdio.h>
#include <string.h>


/** CONSTANTS **/ 

/*
 * Maximum filename length
 */
#define MAX_NAME    256

/*
 * Boundaries of the matrix that represents the image
 */
#define MAX_ROW      400
#define MAX_COLUMN   400


/*
 * Return codes from file read and write functions
 */
#define FAILURE    0
#define SUCCESS    1

/*
 * Maximum "window" size
 */
#define WINDOW_MAX  50

/*
 * Maximum size of the vector that stores the executed commands
 */
#define MAX_COMMANDS 100

/* 
 * Maximum size of the vector that stores the values ​​of the filter functions 
 */
#define MAX 2500


/*
 * CLI options
 */
#define EDGE1                 '1'
#define EDGE2                 '2'
#define EDGE3                 '3'
#define COMPARE               'C'
#define CROP                  'x'
#define DILATION              'd'
#define EROSION               'e'
#define EXIT                  'E'
#define HELP                  'H'
#define HORIZONTAL_FLIP       'h'
#define LOAD                  'l'
#define MEAN                  'M'
#define MEDIAN                'm'
#define NEGATIVE              'n'
#define PRINT                 'p'
#define ROTATE                'r'
#define SAVE                  's'
#define VERTICAL_FLIP         'v'


/*
 * Characters that may appear in user input and will be ignored
 */
#define SPACE     ' '
#define TAB       '\t'
#define ENTER     '\n'
#define HYPHEN    "-"

/* ////////////////////////////////////////////////////////////////
//                                                               //
//  PART I. FUNCTION PROTOTYPES                                  //
//                                                               //
//                                                               //
//////////////////////////////////////////////////////////////// */


/*/////////////////////////////////////////////////////////////////
//                                                               //
//  MANDATORY FUNCTIONS: you must implement the following        //
//                       functions                               //
//                                                               //
//////////////////////////////////////////////////////////////// */

void crop(int image[MAX_ROW][MAX_COLUMN], int *rows, int *columns,
	    int xsup, int ysup, int xinf, int yinf);

void filterEdge1(int image[MAX_ROW][MAX_COLUMN], int rows, int columns,
	    int windowSize);

void filterEdge2(int image[MAX_ROW][MAX_COLUMN], int rows, int columns,
		int windowSize);

void filterEdge3(int image[MAX_ROW][MAX_COLUMN], int rows, int columns,
		int windowSize);

void filterDilation(int image[MAX_ROW][MAX_COLUMN], int rows, int columns,
		int windowSize);

void filterErosion(int image[MAX_ROW][MAX_COLUMN], int rows, int columns,
		int windowSize);

void filterMean(int image[MAX_ROW][MAX_COLUMN], int rows, int columns,
		int windowSize);

void filterMedian(int image[MAX_ROW][MAX_COLUMN], int rows, int columns,
		int windowSize);

void thresholding(int image[MAX_ROW][MAX_COLUMN], int rows, int columns, int k);

void negative(int image[MAX_ROW][MAX_COLUMN], int rows, int columns);

void flipVertical(int image[MAX_ROW][MAX_COLUMN], int rows, int columns);

void flipHorizontal(int image[MAX_ROW][MAX_COLUMN], int rows, int columns);

void rotate(int image[MAX_ROW][MAX_COLUMN], int *rows, int *columns);

void compare(char fileName[MAX_NAME], int image[MAX_ROW][MAX_COLUMN], int rows, int columns);



/* ////////////////////////////////////////////////////////////////
//                                                               //
//  GIVEN FUNCTIONS: you don't need to implement the following   //
/                    functions. They are already coded.          //
//                                                               //
//////////////////////////////////////////////////////////////// */

void help();

char readCommand();

void load(char fileName[MAX_NAME], int image[MAX_ROW][MAX_COLUMN],
	    int *rows, int *columns, int *highestValue);

int readPgm(char name_prefix[MAX_NAME], int image[MAX_ROW][MAX_COLUMN],
	    int *rows, int* columns, int* highestValue);

int writePgm(char name_prefix[MAX_NAME], int image[MAX_ROW][MAX_COLUMN],
	    int rows, int columns, int highestValue);

int readWindowSize();

int getHighestValue(int image[MAX_ROW][MAX_COLUMN],
		int rows, int columns);

void logCommand(char commands[MAX_COMMANDS], int *numOfCommands,
        char command);

void insertionSort(int n, int v[MAX]);


/*/////////////////////////////////////////////////////////////////
//                                                               //
//  PART II. MAIN PROGRAM                                        //
//                                                               //
//                                                               //
//////////////////////////////////////////////////////////////// */


int main() {

  int image[MAX_ROW][MAX_COLUMN];

  int rows;              // maximum number of rows in the image

  int columns;           // maximum number of columns in the image

  int highestValue;      // highest level of grey color in the image

  int win;               // window size

  char fileName[MAX_NAME], outputFileName[MAX_NAME], compFileName[MAX_NAME];    // input and output filenames

  char command;                     // helper variable for reading user commands

  char commands[MAX_COMMANDS];      // stores the performed commands

  int numOfCommands = 0; // number of commands performed

  int xsup, ysup;        // coordinates of the upper left corner of the window

  int xinf, yinf;        // coordinates of the lower right corner of the window

  int r, c;              // row and column variables for traversing matrices. Used in the "PRINT" command

  int k;                 // thresholding height. Used in Edge filters 1, 2 and 3


  /* The command in the line below is only for the skeleton,
   * AS IS, to compile without warning
   * Later this line can be removed.
   */
  xsup = ysup = xinf = yinf = -1;


  load(fileName, image, &rows, &columns, &highestValue);

  help();

  command = readCommand();

  while (command != EXIT) {

    if (command == HELP) {
      help();
    }

    else if (command == LOAD) {
        load(fileName, image, &rows, &columns, &highestValue);
        numOfCommands = 0;
        commands[0] = '\0';
    }

    else if (command == COMPARE) {
        printf("Enter the file to be compared to: ");
        scanf("%d", &compFileName);
        compare(compFileName, image, rows, columns);

    }

    else if (command == CROP) {
        printf("Upper left corner x coordinate: ");
        scanf("%d", &xsup);
        printf("Upper left corner y coordinate: ");
        scanf("%d", &ysup);
        printf("Lower right corner x coordinate: ");
        scanf("%d", &xinf);
        printf("Lower right corner y coordinate: ");
        scanf("%d", &yinf);
        crop(image, &rows, &columns, xsup, ysup, xinf, yinf);
        printf("Image successfully cropped.");


        logCommand(commands, &numOfCommands, command);
    }

    else if (command == PRINT) {
        for(r = 0; r < rows; r++){
            printf("\n");
            for(c = 0; c < columns; c++)
                printf("%4d", image[r][c]);
        }


    }

    else if (command == EDGE1) {
        win = readWindowSize();
        printf("Enter the value of k: ");
        scanf("%d", &k);
        filterEdge1(image, rows, columns, win);
        thresholding(image, rows, columns, k);
        printf("Edge filter #1 successfully applied.");


        logCommand(commands, &numOfCommands, command);
    }

    else if (command == EDGE2) {
        win = readWindowSize();
        printf("Enter the value of k: ");
        scanf("%d", &k);
        filterEdge2(image, rows, columns, win);
        thresholding(image, rows, columns, k);
        printf("Edge filter #2 successfully applied.");


        logCommand(commands, &numOfCommands, command);
    }

    else if (command == EDGE3) {
        win = readWindowSize();
        printf("Enter the value of k: ");
        scanf("%d", &k);
        filterEdge3(image, rows, columns, win);
        thresholding(image, rows, columns, k);
        printf("Edge filter #3 successfully applied.");


        logCommand(commands, &numOfCommands, command);
    }

    else if (command == DILATION) {
        win = readWindowSize();
        filterDilation(image, rows, columns, win);
        printf("Dilation filter successfully applied.");


        logCommand(commands, &numOfCommands, command);
    }

    else if (command == EROSION) {
        win = readWindowSize();
        filterErosion(image, rows, columns, win);
        printf("Erosion filter successfully applied.");


        logCommand(commands, &numOfCommands, command);
    }

    else if (command == MEAN) {
        win = readWindowSize();
        filterMean(image, rows, columns, win);
        printf("Mean filter successfully applied.");


        logCommand(commands, &numOfCommands, command);
    }

    else if (command == MEDIAN) {
        win = readWindowSize();
        filterMedian(image, rows, columns, win);
        printf("Median filter successfully applied.");


        logCommand(commands, &numOfCommands, command);
    }

    else if (command == SAVE) {
      // Updates the highest value
      highestValue = getHighestValue(image, rows, columns);

      strcpy(outputFileName, fileName);

      // Concatenates the executed commands
      if (numOfCommands > 0) {
	    strcat(outputFileName,HYPHEN);
	    strcat(outputFileName, commands);
      }
      writePgm (outputFileName, image, rows, columns, highestValue);
    }

    else if (command == NEGATIVE) {
        negative(image, rows, columns);
        printf("Negative successfully applied.");


        logCommand(commands, &numOfCommands, command);
    }

    else if (command == HORIZONTAL_FLIP) {
        flipHorizontal(image, rows, columns);
        printf("Horizontal flip successfully applied.");


        logCommand(commands, &numOfCommands, command);
    }

    else if (command == VERTICAL_FLIP) {
        flipVertical(image, rows, columns);
        printf("Vertical flip successfully applied.");


        logCommand(commands, &numOfCommands, command);
    }

    else if (command == ROTATE) {
        rotate(image, &rows, &columns);
        printf("Rotation successfully applied.");


        logCommand(commands, &numOfCommands, command);
    }

    else {
      printf("Invalid command\n");
    }

    command = readCommand();
  }

  return 0;
}


/* ////////////////////////////////////////////////////////////////
//                                                               //
//  PART III. FUNCTIONS                                          //
//                                                               //
//////////////////////////////////////////////////////////////// */



/* ////////////////////////////////////////////////////////////////
//                                                               //
//  MANDATORY FUNCTIONS: you must implement the following        //
//                       functions                               //
//////////////////////////////////////////////////////////////// */


/***********************************************************/
/**              IMAGE MANIPULATION FUNCTIONS             **/
/***********************************************************/

/**
 * Inverts image colors
 */
void negative(int image[MAX_ROW][MAX_COLUMN], int rows, int columns){

    int r,c;

    for(r = 0; r < rows; r++)
        for(c = 0; c < columns; c++)
            image[r][c] = 255 - image[r][c];

}

/**
 * Flips the image horizontally
 */
void flipHorizontal(int image[MAX_ROW][MAX_COLUMN], int rows, int columns){

    int aux[MAX_ROW][MAX_COLUMN], r, c;

        for(r = 0; r < rows; r++)
            for(c = 0; c < columns; c++)
                aux[r][c] = image[r][columns - c];

        for(r = 0; r < rows; r++)
            for(c = 0; c < columns; c++)
                image[r][c] = aux[r][c];

}

/**
 * Flips the image vertically
 */
void flipVertical(int image[MAX_ROW][MAX_COLUMN], int rows, int columns){

    int aux[MAX_ROW][MAX_COLUMN], r, c;

    for(r = 0; r < rows; r++)
        for(c = 0; c < columns; c++)
            aux[r][c] = image[rows - r][c];

    for(r = 0; r < rows; r++)
        for(c = 0; c < columns; c++)
            image[r][c] = aux[r][c];

}

/**
 * Performs a 90 degree clockwise rotation on the image provided
 */
void rotate(int image[MAX_ROW][MAX_COLUMN], int *rows, int *columns){

    int aux[MAX_ROW][MAX_COLUMN], r, c, i, j, pot;

    // Inserts the "image" matrix (already rotated) into the "aux" matrix
    for(i = 0, c = 0; c < *columns; c++, i++)
        for(j = 0, r = *rows - 1; r >= 0; r--, j++)
            aux[i][j] = image[r][c];

    // Copies the "aux" matrix into the "image" matrix
    for(r = 0; r < *rows; r++)
        for(c = 0; c < *columns; c++)
            image[r][c] = aux[r][c];

    // Updates matrix boundaries
    pot = *rows;
    *rows = *columns;
    *columns = pot;

}

/**
 * Crops the image according to the new coordinates of the upper left  
 * corner (xsup, ysup) and the lower right corner (xinf, yinf).
 */
void crop(int image[MAX_ROW][MAX_COLUMN], int *rows, int *columns, int xsup, int ysup, int xinf, int yinf){

    int aux[MAX_ROW][MAX_COLUMN], r, c, i, j;

    // Copies the part to be cropped into the "aux" matrix
    for(r = xsup, i = 0; r <= xinf; r++, i++)
        for(c = ysup, j = 0; c <= yinf; c++, j++)
            aux[i][j] = image[r][c];

    // Inserts the cropped part into the "image" matrix
    for(i = 0, r = xsup; i <= xinf; i++, r++)
        for(j = 0, c = yinf; j <= yinf; j++, c++)
            aux[i][j] = image[r][c];

    // Updates "image" matrix boundaries
    *rows = xinf + 1;
    *columns = yinf + 1;

}

/**
 * Applies the median filter to the image passed as argument
 */
void filterMedian(int image[MAX_ROW][MAX_COLUMN], int rows, int columns, int windowSize){

    int i, j;                           // Coordinates of the elements of the "image" matrix. The elements are traversed to get their neighbors
    int r, c;                           // Coordinates of the neighbors of an element of the "image" matrix. The neighbors are stored in the "aux" vector
    int aux[MAX];                       // Auxiliary vector
    int med[MAX_ROW][MAX_COLUMN];       // Median matrix
    int k;                              // "k" is the normalization of the window size
    int cont;                           // "cont" is used to insert the neighbors into the "aux" vector, it indicates the size of this vector


    k = windowSize / 2;

    // Get the neighbors and stores them into the "aux" vector
    for(i = 0; i < rows; i++){
        for(j = 0; j < columns; j++){
            cont = 0;
            for(r = i - k; r <= i + k; r++){
                if(r >= 0 && r < rows){
                    for(c = j - k; c <= j + k; c++){
                        if(c >= 0 && c < columns){
                        aux[cont] = image[r][c];
                        cont++;
                        }
                    }
                }
            }
            insertionSort(cont, aux);          // Sorts the "aux" vector
            med[i][j] = aux[cont / 2];         // Calculates the median of the values in the "aux" vector and assigns them to the "med" matrix
        }
    }

    // Copies the "med" matrix to the "image" matrix
    for(i = 0; i < rows; i++)
        for(j = 0; j < columns; j++)
            image[i][j] = med[i][j];

}

/**
 * Applies the mean filter to the image passed as argument
 */
void filterMean(int image[MAX_ROW][MAX_COLUMN], int rows, int columns, int windowSize){

    int i, j;                                  // Coordinates of the elements of the "image" matrix. The elements are traversed to get their neighbors
    int r, c;                                  // Coordinates of the neighbors of an element of the "image" matrix. The neighbors are stored in the "aux" vector
    int aux[MAX];                              // Auxiliary vector
    int mean[MAX_ROW][MAX_COLUMN];             // Mean matrix
    int k;                                     // "k" is the normalization of the window size
    int cont;                                  // "cont" is used to insert the neighbors into the "aux" vector, it indicates the size of this vector
    int res;                                   // "res" is the mean of the values ​​of the "aux" vector
    int t;                                     // "t" is an auxiliary variable to read the "aux" array

    k = windowSize / 2;

    // Get the neighbors and stores them into the "aux" vector
    for(i = 0; i < rows; i++){
        for(j = 0; j < columns; j++){
            cont = 0;
            for(r = i - k; r <= i + k; r++){
                if(r >= 0 && r < rows){
                    for(c = j - k; c <= j + k; c++){
                        if(c >= 0 && c < columns){
                        aux[cont] = image[r][c];
                        cont++;
                        }
                    }
                }
            }
            insertionSort(cont, aux);          // Sorts the "aux" vector
            res = 0;                           // Resets the mean
            for(t = 0; t < cont; t++){         // Computes the mean of the values ​​in the "aux" vector and assigns them to the "mean" matrix
                res = aux[t] + res;
            }
            res = res / cont;
            mean[i][j] = res;                  // Element of the "mean" matrix receives the arithmetic mean of the values ​​of the "aux" vector
        }
    }

    // Updates the values ​​of the "image" matrix by replacing them with the values ​​of the "mean" matrix
    for(i = 0; i < rows; i++)
        for(j = 0; j < columns; j++)
            image[i][j] = mean[i][j];

}

/**
 * Applies the erosion filter to the image passed as argument
 */
void filterErosion(int image[MAX_ROW][MAX_COLUMN], int rows, int columns, int windowSize){

    int i, j;                                  // Coordinates of the elements of the "image" matrix. The elements are traversed to get their neighbors
    int r, c;                                  // Coordinates of the neighbors of an element of the "image" matrix. The neighbors are stored in the "aux" vector
    int aux[MAX];                              // Auxiliary vector
    int eros[MAX_ROW][MAX_COLUMN];             // Erosion (smallest neighbor value) matrix
    int k;                                     // "k" is the normalization of the window size
    int cont;                                  // "cont" is used to insert the neighbors into the "aux" vector, it indicates the size of this vector
 

    k = windowSize / 2;

    // Get the neighbors and stores them into the "aux" vector
    for(i = 0; i < rows; i++){
        for(j = 0; j < columns; j++){
            cont = 0;
            for(r = i - k; r <= i + k; r++){
                if(r >= 0 && r < rows){
                    for(c = j - k; c <= j + k; c++){
                        if(c >= 0 && c < columns){
                        aux[cont] = image[r][c];
                        cont++;
                        }
                    }
                }
            }
            insertionSort(cont, aux);          // Sorts the "aux" vector
            eros[i][j] = aux[0];               // Element of the "eros" matrix receives the smallest value of the "aux" vector
        }
    }

    // Updates the values ​​of the "image" matrix by replacing them with the values ​​of the "eros" matrix
    for(i = 0; i < rows; i++)
        for(j = 0; j < columns; j++)
            image[i][j] = eros[i][j];

}

/**
 * Applies the dilation filter to the image passed as argument
 */
void filterDilation(int image[MAX_ROW][MAX_COLUMN], int rows, int columns, int windowSize){

    int i, j;                                  // Coordinates of the elements of the "image" matrix. The elements are traversed to get their neighbors
    int r, c;                                  // Coordinates of the neighbors of an element of the "image" matrix. The neighbors are stored in the "aux" vector
    int aux[MAX];                              // Auxiliary vector
    int dilat[MAX_ROW][MAX_COLUMN];            // Dilation (highest neighbor value) matrix
    int k;                                     // "k" is the normalization of the window size
    int cont;                                  // "cont" is used to insert the neighbors into the "aux" vector, it indicates the size of this vector

    k = windowSize / 2;

    // Get the neighbors and stores them into the "aux" vector
    for(i = 0; i < rows; i++){
        for(j = 0; j < columns; j++){
            cont = 0;
            for(r = i - k; r <= i + k; r++){
                if(r >= 0 && r < rows){
                    for(c = j - k; c <= j + k; c++){
                        if(c >= 0 && c < columns){
                        aux[cont] = image[r][c];
                        cont++;
                        }
                    }
                }
            }
            insertionSort(cont, aux);          // Sorts the "aux" vector
            dilat[i][j] = aux[cont - 1];       // Element of the "dilat" matrix receives the highest value of the "aux" vector
        }
    }

    // Updates the values ​​of the "image" matrix by replacing them with the values ​​of the "dilat" matrix
    for(i = 0; i < rows; i++)
        for(j = 0; j < columns; j++)
            image[i][j] = dilat[i][j];

}

/**
 * Converts all matrix values greater than or equal to "k" to 255 and the rest to 0 
 */
void thresholding(int image[MAX_ROW][MAX_COLUMN], int rows, int columns, int k){

    int i,j;                                   // Matrix traversal indexes                              

    for(i = 0; i< rows; i++)
        for(j = 0; j < columns; j++){
            if(image[i][j] >= k)
                image[i][j] = 255;
            else
                image[i][j] = 0;
        }

}


/**
 * Applies the Edge #1 (Dilation - Erosion) filter to the image passed as argument
 */
void filterEdge1(int image[MAX_ROW][MAX_COLUMN], int rows, int columns, int windowSize){

    int i, j;                                  // Matrix traversal indexes
    int eros[MAX_ROW][MAX_COLUMN];             // Erosion matrix

    // Copies the image matrix to the "eros" matrix
    for(i = 0; i < rows; i++)
        for(j = 0; j < columns; j++)
            eros[i][j] = image[i][j];


    filterDilation(image, rows, columns, windowSize);
    filterErosion(eros, rows, columns, windowSize);

    // Inserts the difference between "image" and "eros" matrices in the "image" matrix
    for(i = 0; i < rows; i++)
        for(j = 0; j < columns; j++)
            image[i][j] = image[i][j] - eros[i][j];

}

/**
 * Applies the Edge #2 (Original - Erosion) filter to the image passed as argument
 */
void filterEdge2(int image[MAX_ROW][MAX_COLUMN], int rows, int columns, int windowSize){

    int i, j;                                  // Matrix traversal indexes         
    int eros[MAX_ROW][MAX_COLUMN];             // Erosion matrix

    // Copies the "image" matrix to the "eros" matrix
    for(i = 0; i < rows; i++)
        for(j = 0; j < columns; j++)
            eros[i][j] = image[i][j];

    filterErosion(eros, rows, columns, windowSize);

    // Inserts the difference between "image" and "eros" matrices in the "image" matrix
    for(i = 0; i < rows; i++)
        for(j = 0; j < columns; j++)
            image[i][j] = image[i][j] - eros[i][j];

}

/**
 * Applies the Edge #3 (Dilation - Original) filter to the image passed as argument
 */
void filterEdge3(int image[MAX_ROW][MAX_COLUMN], int rows, int columns, int windowSize){

    int i, j;                                  // Matrix traversal indexes   
    int dilat[MAX_ROW][MAX_COLUMN];            // Dilation matrix

    // Copies the "image" matrix to the "dilat" matrix
    for(i = 0; i < rows; i++)
        for(j = 0; j < columns; j++)
            dilat[i][j] = image[i][j];

    filterDilation(dilat, rows, columns, windowSize);

    // Inserts the difference between "dilat" and "image" matrices in the "image" matrix
    for(i = 0; i < rows; i++)
        for(j = 0; j < columns; j++)
            image[i][j] = dilat[i][j] - image[i][j];

}


void compare(char fileName[MAX_NAME], int image[MAX_ROW][MAX_COLUMN], int rows, int columns){

    int i, j;                                  // Coordinates of the elements of the "image" matrix
    int compRows, compColumns,  compHighest;   // rows, columns and highest shade of grey of the matrix to be compared to the "image" matrix
    int compImage[MAX_ROW][MAX_COLUMN];        // Matrix to be compared to 

    load(fileName, compImage, &compRows, &compColumns, &compHighest);

    if(rows != compRows || columns != compColumns){
        printf("The matrices have different dimensions");
        return;
    }

    else{
        for(i = 0; i < rows; i++)
            for(j = 0; j < columns; j++){
                if(image[i][j] != compImage[i][j]){
                    printf("The matrices have different values in position %d,%d", i, j);
                    return;
                }
            }
    }
    
    printf("The matrices are the same");

}



/* ////////////////////////////////////////////////////////////////
//                                                               //
//  WRITE YOUR CUSTOM AUXILIARY FUNCTIONS HERE                   //
//                                                               //
//////////////////////////////////////////////////////////////// */

// Sorts ascending the elements of a vector via insertion method **/
void insertionSort(int n, int v[MAX]){
   int i, j, x;
   for (j = 1; j < n; j++) {
      x = v[j];
      for (i = j-1; i >= 0 && v[i] > x; --i)
         v[i+1] = v[i];
      v[i+1] = x;
   }
}


/***********************************************************/
/**                 HELPER FUNCTIONS                      **/
/***********************************************************/


/* ////////////////////////////////////////////////////////////////
//                                                               //
//  GIVEN FUNCTIONS: you don't need to implement the following   //
//                   functions. They are already coded.          //
//                                                               //
//////////////////////////////////////////////////////////////// */



/* ////////////////////////////////////////////////////////////////
//                                                               //
//  INPUT/OUTPUT FUNCTIONS                                       //
//                                                               //
//                                                               //
//                                                               //
//////////////////////////////////////////////////////////////// */

/**
 * Displays available commands 
 */
void help(){
  printf(
	 "H - help\n"
	 "l - load\n"
	 "C - compare\n"
	 "x - crop\n"
	 "1 - edge filter #1\n"
	 "2 - edge filter #2\n"
	 "3 - edge filter #3\n"
	 "d - dilation filter\n"
	 "e - erosion filter\n"
	 "M - mean filter\n"
	 "m - median filter\n"
	 "n - negative\n"
	 "h - flip horizontal\n"
	 "v - flip vertical\n"
	 "r - rotate\n"
	 "p - print\n"
	 "s - save\n"
     "E - exit\n"
	 );
}


char readCommand(){
  char command;

  printf("\n");

  printf("Enter a command: ");

  scanf("%c", &command);
  while (command == SPACE || command == TAB || command == ENTER)
      scanf("%c", &command);

  return command;
}

/**
 * Loads a PGM file
 */
void load(char fileName[MAX_NAME], int image[MAX_ROW][MAX_COLUMN], int *rows, int *columns, int *highestValue){
  int result = FAILURE;

  while (result == FAILURE)
    {
      printf("Enter the input file name: ");
      scanf("%s", fileName);
      result = readPgm(fileName, image, rows, columns, highestValue);
    }
}


/**----------------------------------------------
   Reads a PGM file.
   name_prefix  : pgm file prefix
   image        : matrix corresponding to the read image
   rows         : number of matrix rows
   columns      : number of matrix columns
   max_value    : maximum value in the matrix
   ---------------------------------------------- */
int readPgm(char name_prefix[MAX_NAME], int image[MAX_ROW][MAX_COLUMN], int *rows, int *columns, int *highestValue){
  FILE *arq;
  char key[128];
  int i, j, aux;
  char fname[MAX_NAME];

  /* concatenates the filename */
  strcpy(fname, name_prefix);
  strcat(fname,".pgm");

  /* open the input file for reading */
  arq = fopen(fname, "r");
  if (arq == NULL){
    printf("File open error %s\n",fname);
    return FAILURE;
  }

  /* read header data */
  aux = fscanf(arq, "%s", key);
  if (aux != 1){
    printf("File read error %s \n",fname);
    fclose(arq);
    return FAILURE;
  }

  if(strcmp(key,"P2") != 0) {
    printf("Unknown file type\n");
    fclose(arq);
    return FAILURE;
  }

  aux = fscanf(arq, "%d %d %d", columns, rows, highestValue);
  if (aux != 3) {
    printf("Bad file format\n");
    fclose(arq);
    return FAILURE;
  }

  /* read the matrix (image) that follows */
  for(i = 0; i < *rows; i++) {
    for(j = 0; j < *columns; j++) {
      fscanf(arq, "%d", &image[i][j]);
    }
  }

  fclose(arq);

  printf("File %s loaded sucessfully.\n", fname);

  return SUCCESS;
}


/**----------------------------------------------
   Writes a PGM file.
   name_prefix  : pgm file prefix
   image        : matrix corresponding to the read image
   rows         : number of matrix rows
   columns      : number of matrix columns
   max_value    : maximum value in the matrix
   ---------------------------------------------- */
int writePgm(char name_prefix[MAX_NAME], int image[MAX_ROW][MAX_COLUMN], int rows, int columns, int highestValue){
  FILE *arq;
  int i, j;
  char fname[MAX_NAME];

  // generates the file name
  strcpy(fname, name_prefix);
  strcat(fname,".pgm");

  // opens the file in write mode
  arq = fopen(fname, "w");
  if (arq == NULL){
    printf("File open error %s\n",fname);
    return FAILURE;
  }

  // writes header data
  fprintf(arq, "P2\n");
  fprintf(arq, "%d %d\n%d\n", columns, rows, highestValue);

  // writes the matrix (image) that follows
  for (i = 0; i < rows; i++) {
    for (j = 0; j < columns; j++) {
      fprintf(arq, "%d ", image[i][j]);
    }
    fprintf(arq, "\n");
  }

  fclose(arq);

  printf("File %s written successfully.\n", fname);

  return SUCCESS;
}


int readWindowSize(){
  int size = 0;
  while (size == 0) {
    printf("Enter the size of the window: ");
    scanf("%d", &size);
    if (size < 3 || size > WINDOW_MAX) {
      printf("Invalid window size. The window size must be between 3 and %d.\n", WINDOW_MAX);
      size = 0;
    }
  }
  return size;
}

/*/////////////////////////////////////////////////////////////////
//                                                               //
//  HELPER FUNCTIONS PROVIDED                                    //
//                                                               //
//                                                               //
//                                                               //
//////////////////////////////////////////////////////////////// */


void logCommand(char commands[MAX_COMMANDS], int* numOfCommands, char command){
  commands[*numOfCommands] = command;
  (*numOfCommands)++;
  commands[*numOfCommands] = '\0';
}


int getHighestValue(int image[MAX_ROW][MAX_COLUMN], int rows, int columns){
  int i, j;
  int max = image[0][0];
  for (i = 0; i < rows; i++) {
    for (j = 0; j < columns; j++) {
      if (image[i][j] > max) {
	max = image[i][j];
      }
    }
  }
  return max;
}


