#include <stdio.h>
#include <stdlib.h>

double** finalCalc(double**,double**,int,int);
double** inverse(double**,int,int);
double** multiply(double**,int,int,double**,int,int);
double** transpose(double**, int, int);
void freeMatrix(double**,int);
void printMatrix(double**, int, int);
int main(int argc, char** argv){
	FILE* training;
	training = fopen(argv[1],"r");
	if(training == NULL){
		printf("error\n");
		return 0;
	}
	
	FILE* test;
	test = fopen(argv[2], "r");
	if(test == NULL){
		printf("error\n");
		return 0;
	}
	int atrNum; /*columns */
	int trainingData; /*rows */
	int testData;
	
	
	fscanf(training,"%d\n", &atrNum);
	fscanf(training,"%d\n", &trainingData);
	fscanf(test,"%d\n", &testData);
	
	int i,j;
	/*matrix to hold training data except last column */
	double** trainingMatrix = (double**) malloc(sizeof(double*) * trainingData);
		for(i = 0; i < trainingData; i++){
			trainingMatrix[i] = (double*) malloc(sizeof(double) * (atrNum + 1));
		}
	 /*matrix to hold last column of training data */	
	double** matrixY = (double**) malloc(sizeof(double*) * trainingData);
		for(i = 0; i <trainingData; i++){
			matrixY[i] = (double*) malloc(sizeof(double) * 1);
		}
	/*fill in trainingMatrix. First column should be all ones */
	for(i = 0; i < trainingData; i++){
		for(j = 1; j <=atrNum; j++){
			fscanf(training,"%lf%*[,]", &trainingMatrix[i][j]);
		}
		/*fill in matrixY with last element of each row */
		fscanf(training,"%lf%*[,]", &matrixY[i][0]);
		fscanf(training,"\n");
	}
	
	/*fill in first column of training matrix with one */
	for(i = 0; i < trainingData; i++){
		trainingMatrix[i][0] = 1.0;
	}
	
	 double** testMatrix = (double**) malloc(sizeof(double*) * testData);
	 	for(i = 0; i < testData; i++){
	 		testMatrix[i] = (double*) malloc(sizeof(double) * atrNum);
	 	}
	 	
	 for(i = 0; i < testData; i++){
	 	for(j = 0; j < atrNum; j++){
	 		fscanf(test, "%lf%*[,]", &testMatrix[i][j]);
	 	}
	 	fscanf(test,"\n");
	 }
	
	double** result = (double**) malloc(sizeof(double*) * (atrNum + 1));
		for(i = 0; i < atrNum + 1; i++){
			result[i] = (double*) malloc(sizeof(double) * 1);
		}
		
	result = finalCalc(trainingMatrix,matrixY,trainingData,atrNum+1);
	
	double value = 0;
	double** final = (double**) malloc(sizeof(double*) * testData);
		for(i = 0; i < testData; i++){
			final[i] = (double*) malloc(sizeof(double) * 1);
		}
		
	for(i = 0; i < testData; i++){
		value = result[0][0];
		for(j = 0; j < atrNum; j++){
			value = value + (testMatrix[i][j] * result[1 + j][0]);
		}
		final[i][0] = value;
		printf("%0.0f\n",final[i][0]);
	}
	
	freeMatrix(trainingMatrix,trainingData);
	freeMatrix(matrixY,trainingData);
	freeMatrix(testMatrix,testData);
	freeMatrix(result,atrNum + 1);
	freeMatrix(final,testData);
	
	
	return 0;
	
}
	
void printMatrix(double** matrix, int row, int column){
	int i,j;
	for(i = 0; i < row; i++){
		for(j = 0; j < column; j++){
			printf("%lf\t", matrix[i][j]);
		}
		printf("\n");
	}
}
	

double** transpose(double** matrix, int row, int column){
	int i,j;
	double** result = (double**) malloc(sizeof(double*) * column);
		for(i = 0; i < column; i++){
			result[i] = (double*) malloc(sizeof(double) * row);
		}
	
	
	for(i = 0; i < column; i++){
		for(j = 0; j < row; j++){
			result[i][j] = matrix[j][i];
		}
	}
	return result;
	
}

double** multiply(double** matrix1, int r1, int c1, double** matrix2,int r2,int c2){
	int i,a,b,c;
	double num = 0;
	double** result;
	if(c1 != r2){
		printf("error\n");
		return 0;
	}
	result = (double**) malloc(sizeof(double*) * r1);
	for(i = 0; i < r1; i++){
		result[i] = (double*) malloc(sizeof(double) * c2);
	}
	for(a = 0; a < r1; a++){
		for(b = 0; b < c2; b++){
			for(c = 0; c < r2; c++){
				num +=  matrix1[a][c] * matrix2[c][b];
			}
			result[a][b] = num;
			num = 0;
		}
	}
	return result;
}

double** inverse(double** matrix, int row, int column){
	int i,j;
	double** augment = (double**) malloc(sizeof(double*) * row);
		for(i = 0; i < row; i++){
			augment[i] = (double*) malloc(sizeof(double) * (column * 2));
		}
	/* fill in augment matrix with OG matrix */	
	for(i = 0; i < row; i++){
		for(j = 0; j < column; j++){
			augment[i][j] = matrix[i][j];
		}
	}
	
	/* fill in augmented matrix with identity matrix */
	for(i = 0; i < row; i++){
		for(j = column; j < (column*2); j++){
			if(i == (j-column)){ /*insert 1.0 at pivot of identity matrix */
				augment[i][j] = 1.0;
			}else{
				augment[i][j] = 0;
			}
		}
	}
	
	/*Gausian Elimination Forward Pass */
	int k,l,m,n;
	for(i = 0; i < row; i++){
		for(j = 0; j < column; j++){
			if(i == j){ /*pivot column */
				double coeff1 = augment[i][j];
				for(k = 0; k < (column * 2); k++){
					augment[i][k] = augment[i][k]/coeff1;
				}
				for(l = i + 1; l < row; l++){
					double coeff2 = augment[l][j];
					for(m = 0; m < (column * 2); m++){
						augment[l][m] = augment[l][m]/coeff2;
					}
					for(n = 0; n < (column * 2); n++){
						augment[l][n] = augment[l][n] - augment[j][n];
					}
				}
				
			}		
		}
	}
	//printMatrix(augment,row,column*2);
	//printf("\n");
	/*backwards pass time */
	
	for(i = row-1; i >= 0; i--){
		for(j = column-1; j >= 0; j--){
			if(i != j && augment[i][j] != 0){
				double coeff = augment[i][j];
				for(k = 0; k < (column * 2); k++){
					augment[i][k] = augment[i][k] - (coeff * augment[j][k]);
				}
			}
		}
	}
	//printMatrix(augment,row,column*2);
	//printf("\n");
	/* inverse matrix */
	
	double** inverse = (double**) malloc(sizeof(double*) * row);
		for(i = 0; i < row; i++){
			inverse[i] = (double*) malloc(sizeof(double) * column);
		}
	
	for(i = 0; i < row; i++){
		for(j = 0; j < column; j++){
			inverse[i][j] = augment[i][j + column];
		}
	}
	
	return inverse;
	
}

double** finalCalc(double** trainingMatrix,double** matrixY, int row, int column){
	int i;
	double** transposed = (double**) malloc(sizeof(double*) * column);
		for(i = 0; i < column; i++){
			transposed[i] = (double*) malloc(sizeof(double) * row);
		}
		
	double** xtranspose = (double**) malloc(sizeof(double*) * column);
		for(i = 0; i < column; i++){
			xtranspose[i] = (double*) malloc(sizeof(double) * row);
		}
	
	double** inversed = (double**) malloc(sizeof(double*) * column);
		for(i = 0; i < column; i++){
			inversed[i] = (double*) malloc(sizeof(double) * column);
		}
		
	double** inverseT = (double**) malloc(sizeof(double*) * column);
		for(i = 0; i < column; i++){
			 inverseT[i] = (double*) malloc(sizeof(double) * row);
		}
		
	double** result = (double**) malloc(sizeof(double*) * column);
		for(i = 0; i < column; i++){
			result[i] = (double*) malloc(sizeof(double) * 1);
		}
		
	transposed = transpose(trainingMatrix,row,column);
	//printMatrix(transposed,column,row);
	//printf("\n");
	
	xtranspose = multiply(transposed,column,row,trainingMatrix,row,column);
	//printMatrix(xtranspose,column,column);
	//printf("\n");
	
	inversed = inverse(xtranspose,column,column);
	//printMatrix(inversed,column,column);
	//printf("\n");
	
	inverseT = multiply(inversed,column,column,transposed,column,row);
	//printMatrix(inverseT,column,row);
	//printf("\n");
	
	result = multiply(inverseT,column,row,matrixY,row,1);
	//printMatrix(result,column,1);
	//printf("\n");
	
	return result;
}
	
void freeMatrix(double** matrix,int row){
	int i;
	for(i = 0; i < row; i++){
		free(matrix[i]);
	}
	free(matrix);
}

