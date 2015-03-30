
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <assert.h>

#include "matrix.h"

int file_select(const struct dirent *entry);

int main (int argc, char **argv) {

	//char databasePath[] = "~//research//cPCA//images//";
	char databasePath[] = ".//images//";
	char filenameFilePath[] = "filenamesDB.dat";
	char projectedImagesFilePath[] = "testDB.dat";
	char *path = (char *) malloc (200 * sizeof (char));
	char header[4];
	
	unsigned long int i;
	unsigned long int imgWidth, imgHeight, pixMaxSize;
	unsigned long int numImages, numPixels;
	
	/* Get # of images and image names from directory */
	struct dirent **imageList;
    numImages = scandir(databasePath, &imageList, file_select, alphasort);
	if (numImages < 0) {
        perror("scandir");
		exit (1);
    }
	
	/* Get the size of the images */
	sprintf (path, "%s%s", databasePath, imageList[0]->d_name);
	FILE * sampleImage = fopen (path, "r");
	fscanf (sampleImage, "%s %lu %lu %lu", header, &imgHeight, &imgWidth, &pixMaxSize);
	fclose (sampleImage);
	assert (strcmp (header, "P6") == 0 && pixMaxSize == 255);
	
	/* Calculate number of pixels per image */
	numPixels = imgWidth * imgHeight;
	
	/* Allocate the Image array T */
	matrix_t *T = initializeMatrix (UNDEFINED, numPixels,numImages);
	
	// Load images into the matrix
	unsigned char *pixels = (unsigned char *) malloc (3 * numPixels * sizeof (unsigned char));
	for (i = 0; i < numImages; i++) {
		// Load image
		sprintf (path, "%s%s", databasePath, imageList[i]->d_name);
		loadPPMtoMatrixCol (path, T, i, pixels);
	}
	
	// Calculate the mean face
	matrix_t *m = calcMeanCol (T);
	
	/* Subtract the mean face from the regular images to produce normalized matrix A */
	matrix_t *A = T; // To keep naming conventions
	for (i = 0; i < numImages; i++) {
		subtractMatrixColumn (A, i, m, 0);
	}
	
	/* Calculate the surrogate matrix L */
	/* ----- L = (A')*A ----- */
	matrix_t *L = calcSurrogateMatrix (A);
	
	/* Calculate eigenvectors for L */
	matrix_t *L_eigenvectors = calcEigenvectorsSymmetric (L);
	
	/* Calculate Eigenfaces */
	/* ----- Eigenfaces = A * L_eigenvectors ----- */
	matrix_t *eigenfaces = matrixMultiply (A, NOT_TRANSPOSED, L_eigenvectors, NOT_TRANSPOSED, 0);

	/* Calculate Projected Images */
	/* ----- ProjectedImages = eigenfaces' * A ----- */
	matrix_t *projectedImages = matrixMultiply (eigenfaces, TRANSPOSED, A, NOT_TRANSPOSED, A->numCols);


	// Print the Projected Image matrix and the mean image
	FILE * out = fopen (projectedImagesFilePath, "w");
	/*fprintMatrix (out, projectedImages);
	fprintMatrix (out, eigenfaces);
	fprintMatrix (out, m); */
	
	fwriteMatrix (out, projectedImages);
	fwriteMatrix (out, eigenfaces);
	fwriteMatrix (out, m);


	// Write the filenames corresponding to each column
	FILE *filenamesFile = fopen (filenameFilePath, "w");
	for (i = 0; i < numImages; i++) {
		fprintf (filenamesFile, "%s\n", imageList[i]->d_name);
		free (imageList[i]);
	}
	free (imageList);

	// Save the mean image	-> this is more of for fun and to make sure
	//						-> the function I wrote worked
	writePPMgrayscale("meanImage.ppm", m, 0, imgHeight, imgWidth);
	
	/* COMMENT - could move these up to help memory */
	freeMatrix (A);
	freeMatrix (L);
	freeMatrix (L_eigenvectors);
	freeMatrix (eigenfaces);
	freeMatrix (projectedImages);
	freeMatrix (m);

	
	fclose (out);
	fclose (filenamesFile);

	free (path);
	free (pixels);

	return 0;
}


int file_select(const struct dirent *entry){
	
    if (strstr(entry->d_name, ".ppm") != NULL) {
        return 1;
    } else {
        return 0;
    }
}
