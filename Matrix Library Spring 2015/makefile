
BINS=matrixTest

all : $(BINS)

matrixTest : matrixTest.o matrixOps.o
	gcc -Wall -g matrixTest.o matrixOps.o -o matrixTest `pkg-config --libs gsl` -lm

matrixTest.o : matrixTest.c matrixOps.h
	gcc -Wall -g -c matrixTest.c

matrixOps.o : matrixOps.c matrixOps.h
	#gcc -Wall -g -c matrixOperations.c
	gcc -Wall -g -c matrixOps.c `pkg-config --cflags gsl` -lm

clean :
	rm -f $(BINS) *.o *.dat

