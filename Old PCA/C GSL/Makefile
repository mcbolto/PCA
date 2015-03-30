####################################################################################################
#   Makefile
#
#   edited by: William Halsey
#   whalsey@g.clemson.edu
#
#   Description: This file is use to build the executable 'pca.' This is a cuda implementation of
#   the PCA algorithm.
#
#   Last edited: Jul. 16 2013
#   Edits: changed the file paths to libraries
#
compiler = gcc
flags = -Wall -g -O3
lib = -lgsl -lgslcblas -lm -lpthread
libpath = -L/usr/local/lib

all: clean totalprogram cleanup

objects: grayscale.o pca.o ppm.o matrix_ops.o

cleanup: 
	rm -rf *.o

totalprogram: grayscale.o pca.o ppm.o matrix_ops.o
	$(compiler) $(flags) $(libpath) grayscale.o pca.o ppm.o matrix_ops.o -o pca $(lib)
    
grayscale.o: grayscale.c
	$(compiler) $(flags) -c grayscale.c

matrix_ops.o: matrix_ops.c
	$(compiler) $(flags) -c matrix_ops.c 

pca.o: pca.c
	$(compiler) $(flags) -c pca.c 

ppm.o: ppm.c
	$(compiler) $(flags)  -c ppm.c 

clean:
	rm -rf *.o pca
