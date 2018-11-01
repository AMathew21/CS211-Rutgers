#include <stdio.h>
#include <stdlib.h>

void printMatrix(int**,int,int);

int main(int argc, char** argv){
	int i,j,num;
	FILE* fp;
	fp = fopen(argv[1], "r");
	int r1,c1;
	fscanf(fp,"%d %d\n",&r1,&c1);
	int** matrix1, *arr1;
	matrix1 = (int**) malloc(sizeof(int*) * r1);
	for(i = 0; i < r1; i++){
		arr1 = (int*) malloc(sizeof(int) * c1);
		for(j = 0; j < c1; j++){
			fscanf(fp,"%d",&num);
			arr1[j] = num;
		}
		matrix1[i] = arr1;
	}
	int r2,c2;
	fscanf(fp,"%d %d\n",&r2,&c2);
	
	
	if(c1 != r2){
		printf("bad-matrices\n");
		exit(0);
	}
	
	int** matrix2, *arr2;
	matrix2 = (int**) malloc(sizeof(int*) * r2);
	for(i = 0; i < r2; i++){
		arr2 = (int*) malloc(sizeof(int) * c2);
		for(j = 0; j < c2; j++){
			fscanf(fp,"%d",&num);
			arr2[j] = num;
		}
		matrix2[i] = arr2;
	}
	
	int** result;
	result = (int**) malloc(sizeof(int*) * r1);
	for(i = 0; i < r1; i++){
		result[i] = (int*) malloc(sizeof(int) * c2);
	}
	int a,b,c;
	for(a = 0; a < r1; a++){
		for(b = 0; b < c2; b++){
			for(c = 0; c < r2; c++){
				result[a][b] = result[a][b] + matrix1[a][c] * matrix2[c][b];
			}
		}
	}
	
	printMatrix(result,r1,c2);
	for(i = 0; i < r1; i++){
		free(matrix1[i]);
	}
	for(i = 0; i < r2; i++){
		free(matrix2[i]);
	}
	for(i = 0; i < r1; i++){
		free(result[i]);
	}
	free(matrix1);
	free(matrix2);
	free(result);
	return 0;

}

void printMatrix(int** matrix, int r, int c){
	int i,j;
	for(i = 0; i < r; i++){
		for(j = 0; j < c; j++){
			printf("%d\t", matrix[i][j]);
		}
		printf("\n");
	}
	
}
