#include <stdio.h>
#include <stdlib.h>

#define FALSE 0
#define TRUE 1

int checkMagic(int**, int);
int dupeCheck(int**,int);

int checkMagic(int** matrix, int size){
	int diagonalSum = 0;
	int diagonalSum2 = 0;
	int rowSum;
	int columnSum;
	int i,j;
	for(i = 0; i < size; i++){
		diagonalSum += matrix[i][i];
		diagonalSum2 += matrix[i][size-1-i];
	}
	if(diagonalSum != diagonalSum2){
		return FALSE;
	}
			
	for(i = 0; i < size; i++){
		rowSum = 0;
		for(j = 0; j < size; j++){
			rowSum += matrix[i][j];
		}
		if(rowSum != diagonalSum){
			return FALSE;
		}
	}
	for(i = 0; i < size; i++){
		columnSum = 0;
		for(j = 0; j < size; j++){
			columnSum += matrix[j][i];
		}
		if(columnSum != diagonalSum){
			return FALSE;
		}
	}
	return TRUE;
}

int dupeCheck(int** matrix, int n){
	int a,b,c,d;
	for(a = 0; a < n; a++){
		for(b = 0; b < n; b++){
			for(c = a + 1; c < n; c++){
				 for(d = 0; d < n; d++){
				 	if(matrix[a][b] == matrix[c][d]){
				 		return FALSE;
				 	
				 }
				}
			}
		}
	}
	return TRUE;
}

int main(int argc, char* argv[]){
	FILE *fp;
	fp = fopen(argv[1], "r");
	if(fp == NULL){
		printf("error\n");
		return 0;
	}
	int n;
	fscanf(fp,"%d",&n);
	
	int** matrix = (int**) malloc(sizeof(int**) * n);
	for(int i = 0; i < n; i++){
		matrix[i] = (int*) malloc(sizeof(int*) * n);
	}
	for(int i = 0; i < n; i++){
		for (int j = 0; j < n; j++){
			fscanf(fp, "%d", &matrix[i][j]);
		}
	}
	
	if(checkMagic(matrix,n) == 1 && dupeCheck(matrix,n) == 1){
		printf("magic\n");
	}else{
		printf("not-magic\n");
	}
	
	for(int i = 0; i < n; i++){
		free(matrix[i]);
	}
	free(matrix);
	return 0;
}		
