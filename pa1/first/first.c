#include <stdio.h>
#include <stdlib.h>
int main(int argc, char** argv){
	int size;
	FILE* fp;
	fp = fopen(argv[1], "r");
	if(fp == NULL){
		printf("error\n");
		exit(0);
		return 0;
	}
	fscanf(fp, "%d\n", &size);
	int output[size];
	int i;
	for(i = 0; i < size; i++){
		fscanf(fp,"%d\t", &output[i]);
	}
	int temp;
	int j;
	for(i = 0; i < size; i++){
		for(j = i + 1; j < size; j++){
			if(output[i] % 2 != 0 && output[j] % 2 == 0){
				temp = output[j];
				output[j] = output[i];
				output[i] = temp;
			}
		}
	}
	int count = 0;
	for(i = 0; i < size; i++){
		if(output[i] % 2 == 0){
			count++;
		}
	}
	
	for(i = 0; i <= count; i++){
		for(j = i + 1; j < count; j++){
			if(output[j] < output[i]){
				temp = output[j];
				output[j] = output[i];
				output[i] = temp;
			}
		}
	}
	for(i = count; i < size; i++){
		for(j = i + 1; j < size; j++){
			if(output[j] < output[i]){
				temp = output[j];
				output[j] = output[i];
				output[i] = temp;
			}
		}
	}
		
				
	for(j = 0; j < size; j++){
		printf("%d\t", output[j]);
	}
	printf("\n");
	return 0;
}

