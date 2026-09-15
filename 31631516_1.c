#include <stdio.h>
int main() {
	int n;
	int matrix1[100][100], matrix2[100][100], result_matrix[100][100];
	// Open matrix1.bin and matrix2.bin for reading
	FILE *f1 = fopen("matrix1.bin", "rb");
	FILE *f2 = fopen("matrix2.bin", "rb");
	if (f1 == NULL || f2 == NULL){
		printf("error matrix does not work");
		return 1;
	}
	// Read the dimension of the matrices
	int n2;
	fread(&n, sizeof(int), 1, f1);
	fread(&n2, sizeof(int), 1, f2);
	
	if (n != n2) {
		printf("error the demensions are different");
		fclose(f1);
		fclose(f2);
		return 1;
	}

	if (n > 100 || n <= 0) {
		printf("error invalid matrix size");
		fclose(f1);
		fclose(f2);
		return 1;
	}
	// Read the elements of the matrices
	for (int i = 0; i < n; i++) {
       		for (int j = 0; j < n; j++) {
            		fread(&matrix1[i][j], sizeof(int), 1, f1);
            		fread(&matrix2[i][j], sizeof(int), 1, f2);
        	}
    	}
	// Close the input files (can also be closed later below)
	fclose(f1);
	fclose(f2);
	// Perform matrix multiplication
	for (int i = 0; i < n; i++) {
	        for (int j = 0; j < n; j++) {
	    		result_matrix[i][j] = 0;
            		for (int k = 0; k < n; k++) {
                		result_matrix[i][j] += matrix1[i][k] * matrix2[k][j];
            		}
        	}
    	}
	printf("result matrix:\n");
	for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                        printf("%d ", result_matrix[i][j]);
                }
		printf("\n");
        }

	// Open result.bin for writing
	FILE *fout = fopen("result.bin", "wb");
	// Write the dimension of the result_matrix
	fwrite(&n, sizeof(int), 1, fout);
	// Write the elements of the result_matrix
	for (int i = 0; i < n; i++) {
        	for (int j = 0; j < n; j++) {
            		fwrite(&result_matrix[i][j], sizeof(int), 1, fout);
        	}
    	}
	// Close the output file
	fclose(fout);
	printf("program finished.");
	return 0;
}
