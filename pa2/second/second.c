#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define UNASSIGNED 0

int hasMultipleSolutions(int[][9],int,int);
void printGrid(int[][9]);
int checkRow(int[][9],int,int,int);
int checkColumn(int[][9],int,int,int);
int checkSquare(int[][9],int,int,int);
int isValid(int[][9],int,int,int);
int solveSudoku(int[][9],int);
int totalUnassigned(int[][9]);

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
	int unassigned = totalUnassigned(grid);
	if(solveSudoku(grid,unassigned)){
		printGrid(grid);
	}else{
		printf("no-solution\n");
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
       	
// checks if position in grid has multiple options 	
int hasMultipleSolutions(int grid[][9], int row, int column){
	int num;
	int count = 0; 
	for(num = 1; num <=9; num++){
		if(isValid(grid,row,column,num) == 1){
			count++;
		}
	}
	if(count == 1){
		return 0;
	}else{
		return 1;
	}
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
	
int solveSudoku(int grid[][9],int unassigned){
	int total = totalUnassigned(grid);
	while(total != 0){
		int row;
		int col;
		int check = total;
		for(row = 0; row < 9; row++){
			for(col = 0; col < 9; col++){
				if(grid[row][col] == 0){ //blank cell found
					if(hasMultipleSolutions(grid,row,col) == 0){ //unique cell found	
						int value;
						for(value = 1; value <= 9; value++){
							if(isValid(grid,row,col,value)){
								grid[row][col] = value;
								//reset counters
								//row = 0; 
								//col = 0;
								total = total -1;
							}
						}
					}else{ //has multiple solutions so continue iterating
						continue;
					}
				}else{ //filled in cell so keep iterating
					continue;
				}
			}
		}
		if(check == total){
			return 0;
		}
	}

	int check = totalUnassigned(grid);
	if(check > 0){
		return 0;
	}
	else {
		return 1;
	}

}
