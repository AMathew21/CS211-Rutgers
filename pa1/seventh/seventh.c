#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char* argv[]){
	if(argc < 2){
		printf("error\n");
		return 0;
	}
	char* output = (char*) malloc(sizeof(char) * (argc));
	for(int i = 0; i < (argc - 1); i++){
		char* str = argv[i + 1];
		int len = strlen(str);
		*(output + i) = str[len - 1];
	}
	*(output + argc - 1) = '\0';
	printf("%s\n", output);
	free(output);
	return 0;
}
