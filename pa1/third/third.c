#include <stdio.h>
#include <stdlib.h>

#define SIZE 10000

typedef struct node{
	int data;
	int key;
	struct node* next;
}node;

typedef struct hashtable{
	int size;
	struct node** row;
}hashtable;

int hash(int);
void search(hashtable*,int);
void insert(hashtable*,node*,int);
hashtable* create(int);

int main(int argc, char** argv){
	FILE* fp;
	fp = fopen(argv[1], "r");
	if(fp == NULL){
		printf("error\n");
		return 0;
	}
	hashtable* maintable = create(SIZE);
	char op;
	int num;
	while(fscanf(fp,"%c\t%d\n", &op, &num) != EOF){
		if(op == 'i'){
			node* newNode = (node*) malloc(sizeof(node));
			newNode->key = hash(num);
			newNode->data = num;
			newNode->next = NULL;
			insert(maintable,newNode,num);
		}else if(op == 's'){
			search(maintable,num);
		}else{
			printf("error\n");
			return 0;
		}
	}
	return 0;
}

int hash(int code){
	int hashKey = abs((code) % SIZE);
	return hashKey;
}

void insert(hashtable* maintable,node* newNode,int number){
	int index = newNode->key;
	if(maintable->row[index] == NULL){
		maintable->row[index] = newNode;
		printf("inserted\n");
		return;
	}else if(maintable->row[index]->data == number){
		printf("duplicate\n");
		return;
	}
	node* ptr = maintable->row[index];
	while(ptr->next !=NULL){
		if(ptr->next->data == number){
			printf("duplicate\n");
			return;
		}
		ptr = ptr->next;
	}
	ptr->next = newNode;
	printf("inserted\n");
	return;
}
				
		
void search(hashtable* table, int number){
	int index = hash(number);
	if(table->row[index] == NULL){
		printf("absent\n");
		return;
	}
	node* ptr;
	for(ptr = table->row[index]; ptr != NULL; ptr = ptr->next){
		if(ptr->data == number){
			printf("present\n");
			return;
		}
	}
	printf("absent\n");
	return;
}

hashtable* create(int size){
	hashtable* maintable = (hashtable*) malloc(sizeof(hashtable));
	maintable->size = size;
	maintable->row = malloc(sizeof(node) * size);
	for(int i = 0; i < size; i++){
		maintable->row[i] = NULL;
	}
	return maintable;
}
