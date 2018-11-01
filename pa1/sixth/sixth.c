#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define TRUE 1
#define FALSE 0


int findSecondVowel(char*,int);
int isFirstCharVowel(char*);

int isFirstCharVowel(char* input){
	if(input[0] == 'a' || input[0] == 'e' || input[0] == 'i' || input[0] == 'o' || input[0] == 'u' || input[0] == 'A' || input[0] == 'E' || input[0] == 'I' || input[0] == 'O' || input[0] == 'U'){
		return 1;
	}else{
		return 0;
	}
}

int findSecondVowel(char* input, int len){
	for(int i = 1; i < len; i++){
		if(input[i] == 'a' || input[i] == 'e' || input[i] == 'i' || input[i] == 'o' || input[i] == 'u' || input[i] == 'A'|| input[i] == 'E' || input[i] == 'I' || input[i] == 'O' || input[i] == 'U' ){
			return i;
	
		}
	}
	return len;
}


int main(int argc, char** argv){
	if(argc < 2){
		printf("error");
	}
	int i,len;
	for(i = 1; i < argc; i++){
		char* input = argv[i];
		len = strlen(input);
		if(isFirstCharVowel(input) == 1){
			char* output = (char*) malloc(sizeof(char) * (len + 4));
			strcpy(output,input);
			strcat(output, "yay");
			printf("%s ", output);
		}else{
			char* output = (char*) malloc(sizeof(char) * (len + 3));
			strncpy(output,input + findSecondVowel(input,len), len - findSecondVowel(input,len));
			strncat(output,input,findSecondVowel(input,len));
			strcat(output,"ay");
			printf("%s ", output);
		}
			
			
	}
	printf("\n");
	return 0;
}
		
	
