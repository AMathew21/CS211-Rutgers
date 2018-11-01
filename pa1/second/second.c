#include <stdio.h>
#include <stdlib.h>

typedef struct node{
	int data;
	struct node* next;
} Node;

Node* head = NULL;

void insertNode(Node*,int);
void deleteNode(int);
void printList(Node*);
int countNodes(Node*);

int countNodes(Node* ptr){
	if(ptr == NULL){
		return 0;
	}
	int count = 0;
	while(ptr != NULL){
		count++;
		ptr = ptr->next;
	}
	return count;
}

void printList(Node* ptr){
	if(ptr == NULL){
		return;
	}
	while(ptr != NULL){
		printf("%d\t", ptr->data);
		ptr = ptr->next;
	}
	printf("\n");
}

int main(int argc, char** argv){
	if(argc < 2){
		printf("error\n");
		return 0;
	}
	char ch;
	int data;
	FILE *fp;
	fp = fopen(argv[1], "r");
	if(fp == NULL){
		printf("error\n");
		return 0;
	}
	while(fscanf(fp, "%c\t%d\n", &ch, &data) != EOF){
		if(ch == 'i'){
			Node* newNode = (Node*) malloc(sizeof(Node));
			newNode->data = data;
			newNode->next = NULL;
			insertNode(newNode,data);
		}else if(ch == 'd'){
			deleteNode(data);
		}else{
			printf("error\n");
			return 0;
		}
	}
	int numberOfNodes = countNodes(head);
	printf("%d\n", numberOfNodes);
	printList(head);
	fclose(fp);
	return 0;
}

void insertNode(Node* newNode, int value){
	if(head == NULL){
		head = newNode;
		return;
	}
	Node* ptr = head;
	Node* prev = NULL;
	while(ptr != NULL){
		if(ptr->data > value){ /* insert node at front of list */
			if(prev == NULL){
				newNode->next = ptr;
				head = newNode;
				return;
			}else{
				prev->next = newNode;
				newNode->next = ptr;
				return;
			}
		}else if(ptr->data < value){
			if(ptr->next == NULL){
				ptr->next = newNode;
				return;
			}else{
				prev = ptr;
				ptr = ptr->next;
			}
		}else if(ptr->data == value){
			return;
		}
	}
	
}

void deleteNode(int value){
	if(head == NULL){
		return;
	}
	Node* ptr = head;
	Node* prev = NULL;
	while(ptr != NULL ){
		if(ptr->data > value){
			prev = ptr;
			ptr = ptr->next;
		}else if(ptr->data < value){
			prev = ptr;
			ptr = ptr->next;
		}else if(ptr->data == value){
			if(prev == NULL){ /* delete head */
				if(ptr->next == NULL){ /*head is only node */
					head = NULL;
					return;
				}else{
					head = ptr->next;
					ptr = NULL;
					free(ptr);
					return;
				}
			}else if(ptr->next == NULL){ /* delete last node */
				prev->next = NULL;
				ptr = NULL;
				free(ptr);
				return;
			}else{
				prev->next = ptr->next;
				ptr = NULL;
				free(ptr);
				return;
			}
		}
	}
}
	
	
