#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0

void printGrid(int[][9]);
int checkRow(int[][9],int,int,int);
int checkColumn(int[][9],int,int,int);
int checkSquare(int[][9],int,int,int);
int isValid(int[][9],int,int,int);
int solveSudoku(int[][9],int,int);
int totalUnassigned(int[][9]);
int numberUnassigned(int[][9],int,int);

int main(int argc, char** argv){
	int i,j;
	int grid[9][9];
	
	FILE* fp;
	fp = fopen(argv[1], "r");
	
	if(fp == NULL){
		printf("error\n");
		return 0;
	}
	for(i = 0; i < 9; i++){
		for(j = 0; j < 9; j++){
			char c;
			fscanf(fp,"%c\t",&c);
				if(c == '-'){
					grid[i][j] = 0;
			}else{
				int num = c - '0';
				grid[i][j] = num;
			}
		}
		fscanf(fp,"\n");
	}
	if(solveSudoku(grid,0,0)){
		for(i = 0; i < 9; i++){
			for(j = 0; j < 9; j++){
				printf("%d\t",grid[i][j]);
			}
			printf("\n");
		}
	}
	return 0;
}

void printGrid(int grid[][9]){
	int i,j;
	for(i = 0; i < 9; i++){	
		for(j = 0; j < 9; j++){
			printf("%d\t", grid[i][j]);
		}
	printf("\n");
	}
}

int checkRow(int grid[][9], int row, int column, int number){
	int i;
	for(i = 0; i < 9; i++){
		if(grid[row][i] == number){
			return 1;
		}
	}
	return 0;
}

int checkColumn(int grid[][9], int row, int column, int number){
	int i;
	for(i = 0; i < 9; i++){
		if(grid[i][column] == number){
			return 1;
		}
	}
	return 0;
}

int checkSquare(int grid[][9], int row, int column, int number){
	row =  (row/3)*3;
	column = (column/3)*3;
	int i,j;
	for(i = row; i < row + 3; i++){
		for(j = column; j < column + 3; j++){
			if(grid[i][j] == number){
				return 1;
			}
		}
	}
	return 0;
}

int isValid(int grid[][9],int row,int column, int number){
	if(checkRow(grid,row,column,number)){
		return 0;
	}
	if(checkColumn(grid,row,column,number)){
		return 0;
	}
	if(checkSquare(grid,row,column,number)){
		return 0;
	}
	return 1; //number can be placed in grid
}			
	
int solveSudoku(int grid[][9],int row, int column){
	int total = totalUnassigned(grid);
	while(total != 0){

	if(grid[row][column] != 0){
		if(column == 8){
			return solveSudoku(grid,row+1,0);
		}else{
			return solveSudoku(grid,row,column+1);
		}
	}else if(grid[row][column] == 0){
		int num;
		for(num = 1; num <= 9; num++){
			if(isValid(grid,row,column,num)){
				grid[row][column] = num;
				total--;
				if(column == 8){
					if(solveSudoku(grid,row+1,0)){
						return 1;
					}else{
						grid[row][column] = 0;
					}
				}else{
					if(solveSudoku(grid,row,column+1)){
						return 1;
					}else{
						grid[row][column] = 0;
					}
				}
			}
		}
		return 0;
		
	}
}
	return 1;
}
						
int totalUnassigned(int grid[][9]){
	int i,j;
	int total = 0;
	for(i = 0; i < 9; i++){
		for(j = 0; j < 9; j++){
			if(grid[i][j] == 0){
				total++;
			}
		}
	}
	return total;
}

