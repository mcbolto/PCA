
BINS=recognition createPCADatabase matrixTest ppmTest

all : $(BINS)

recognition : recognition.o matrixOperations.o
	#gcc -Wall -g recognition.o matrixOperations.o -o recognition
	gcc -Wall -g recognition.o matrixOperations.o -o recognition `pkg-config --libs gsl`

ppmTest : ppmTest.o matrixOperations.o
	#gcc -Wall -g ppmTest.o matrixOperations.o -o ppmTest 
	gcc -Wall -g ppmTest.o matrixOperations.o -o ppmTest `pkg-config --libs gsl`

createPCADatabase : createPCADatabase.o matrixOperations.o
	#gcc -Wall -g createPCADatabase.o matrixOperations.o -o createPCADatabase
	gcc -Wall -g createPCADatabase.o matrixOperations.o -o createPCADatabase `pkg-config --libs gsl`

matrixTest : matrixTest.o matrixOperations.o
	#gcc -Wall -g matrixTest.o matrixOperations.o -o matrixTest
	gcc -Wall -g matrixTest.o matrixOperations.o -o matrixTest `pkg-config --libs gsl`

recognition.o : recognition.c matrix.h
	#gcc -Wall -g -c recognition.c
	gcc -Wall -g -c recognition.c `pkg-config --cflags gsl`

createPCADatabase.o : createPCADatabase.c matrix.h
	gcc -Wall -g -c createPCADatabase.c 

matrixTest.o : matrixTest.c matrix.h
	gcc -Wall -g -c matrixTest.c

ppmTest.o : ppmTest.c matrix.h
	gcc -Wall -g -c ppmTest.c
	
matrixOperations.o : matrixOperations.c matrix.h
	#gcc -Wall -g -c matrixOperations.c
	gcc -Wall -g -c matrixOperations.c `pkg-config --cflags gsl`

clean :
	rm -f $(BINS) *.o *.dat
