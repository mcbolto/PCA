// matrix test
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "matrixOps.h"

int main (void) {
	int dimx, dimy, iteration;
	matrix_t *A;
	matrix_t *B;
	matrix_t *B_t;
	matrix_t *C;
	int val;
	FILE *f;
		
	for(iteration=1; iteration < 5; iteration++)
	{
		for(dimx=2; dimx < 300; dimx += 30)
		{
			for(dimy=2; dimy < 500; dimy += 50)
			{
				A = m_initialize (FILL, dimx, dimy);
				B = m_initialize (FILL, dimy, dimx);
	
				d_generateRandomMatrix(A);
				d_generateRandomMatrix(B);
					
				d_matlab_print(A, "test.m", "a");
				d_matlab_print(B, "test.m", "b");
				
				//Test Transpose
				B_t = m_transpose(B);
				d_matlab_print(B_t, "test.m", "c");
				d_matlab_function("d = round((b.') * 1e4)/1e4;", "transpose", iteration, "test.m");
				
				printf("multiplication\n");
				//Test Multiplication
				C = m_matrix_multiply(A, B, B->numCols);
				d_matlab_print(C, "test.m", "c");
				d_matlab_function("d = round((a * b) * 1e4)/1e4;", "multiplication", iteration,  "test.m");
				
				printf("division\n");
				//Test Division
				//C = m_matrix_division(A, B_t);
				//d_matlab_print(C, "test.m", "c");
				//d_matlab_function("d = round((a / b.') * 1e4)/1e4;", "division", iteration,  "test.m");
				
				printf("subtract\n");
				//Test subtract
				C = m_dot_subtract(A,B_t);
				d_matlab_print(C, "test.m", "c");
				d_matlab_function("d = round((a - b.') * 1e4)/1e4;", "subtraction", iteration,  "test.m");
				
				printf("add\n");
				//Test add
				C = m_dot_add(A,B_t);
				d_matlab_print(C, "test.m", "c");
				d_matlab_function("d = round((a + b.') * 1e4)/1e4;", "addition", iteration,  "test.m");
				
				printf("dotdivision\n");
				//Test dotdivision
				C = m_dot_division(A, B_t);
				d_matlab_print(C, "test.m", "c");
				d_matlab_function("d = round((a ./ b.') * 1e4)/1e4;", "dotdivision", iteration,  "test.m");
				
				printf("reshape\n");
				//Reshape (to make square)
				m_free(A);
				A = m_initialize(FILL, dimx, dimx);
				d_generateRandomMatrix(A);
				d_matlab_print(A, "test.m", "a");
				
				printf("sqrtm\n");
				//Test sqrtm
				//C = m_sqrtm(A);
				//d_matlab_print(C, "test.m", "c");
				//d_matlab_function("d = round(sqrtm(a) * 1e4)/1e4;", "sqrtm", iteration,  "test.m");
				
				printf("norm\n");
				//Test norm
				val = m_norm(A, 1);
				f = fopen("test.m", "a");
				fprintf(f, "c = %d;\n", val);
				fclose(f);
				d_matlab_function("d = round(norm(a, 1) * 1e4)/1e4;", "norm", iteration, "test.m");
				
				printf("cov\n");
				//Test covariance
				C = m_covariance(A);
				d_matlab_print(C, "test.m", "c");
				d_matlab_function("d = round(cov(a, 1) * 1e4)/1e4;", "covariance", iteration, "test.m");
				
				printf("det\n");
				//Test determinant
				val = m_determinant(A);
				f = fopen("test.m", "a");
				fprintf(f, "c = %d;\n", val);
				fclose(f);
				d_matlab_function("d = round(det(a) * 1e4)/1e4;", "determinant", iteration,  "test.m");
				
				m_free (A);
				m_free (B);
				m_free (B_t);
				m_free (C);
				printf("%d%% of the way complete.\n", 100*iteration/5);
			}
		}
	}

	return 0;
}

