#include <stdio.h>
#include <stdlib.h>

typedef struct node{
	int data;
	struct node* left;
	struct node* right;
}Treenode;

Treenode* root = NULL;

void search(int);
void insert(Treenode*, int);
void delete(int);
int findMinNode(Treenode*);

int findMinNode(Treenode* start){
	Treenode* ptr = start;
	while(ptr->left != NULL){
		ptr = ptr->left;
	}
	return ptr->data;
}

void search(int key){
	if(root == NULL){ 
		printf("absent\n");
		return ;
	}
	Treenode* ptr = root;
	int depth = 1;
	int absentCheck = 0;
	while(ptr != NULL){
		if(ptr->data == key){
			printf("present %d\n", depth);
			absentCheck = 1;
			return;
		}else if(ptr->data > key){
			depth++;
			ptr = ptr->left;
		}else if(ptr->data < key){
			depth++;
			ptr = ptr->right;
		}
	}
	if(absentCheck == 0){
		printf("absent\n");
	}
}

void insert(Treenode* newNode , int key){
	int depth = 1;
	if(root == NULL){
		root = newNode;
		printf("inserted %d\n", depth);
		return;
	}
	Treenode* ptr = root;
	Treenode* parent = NULL;
	while(ptr != NULL){ 
		if(ptr->data == key){
		 	printf("duplicate\n");
			return;
		}else if(ptr->data > key){
			parent = ptr;
			ptr = ptr->left;
		}else{
			parent = ptr;
			ptr = ptr->right;
		}
		depth++;
	}
	if(ptr == NULL){
		if(parent->data > key){
			parent->left = newNode;
			printf("inserted %d\n", depth);
		}else{
			parent->right = newNode;
			printf("inserted %d\n", depth);
		}
	}
	return;
}

void delete(int key){
	if(root == NULL){
		printf("fail\n");
		return;
	}
	Treenode* ptr = root;
	Treenode* parent = NULL;
	while(ptr != NULL){
		if(ptr->data > key){
			parent = ptr;
			ptr = ptr->left;
		}else if(ptr->data < key){
			parent = ptr;
			ptr = ptr->right;
		}else if(ptr->data == key){
			if(ptr->right != NULL && ptr->left != NULL){
					int newData = findMinNode(ptr->right);
					delete(newData);
					ptr->data = newData;
					return;
				}
			else if(ptr->right == NULL && ptr->left == NULL){ 
				if(parent == NULL){ 
					root = NULL;
					printf("success\n");
					return;
				}
				if(parent->data > key){
					parent->left = NULL;
					free(ptr);
					printf("success\n");
					return;
				}
				if(parent->data < key){
					parent->right = NULL;
					free(ptr);
					printf("success\n");
					return;
				}
			}else if(ptr->right == NULL || ptr->left == NULL){ 
				if(ptr->right != NULL){
					if(parent == NULL){
						root = ptr->right;
						free(ptr);
						printf("success\n");
						return;
					}
					if(ptr == parent->right){
						parent->right = ptr->right;
						free(ptr);
						printf("success\n");
						return;
					}else{
						parent->left = ptr->right;
						free(ptr);
						printf("success\n");
						return;
					}
				}else{
					if(parent == NULL){
						root = ptr->left;
						free(ptr);
						printf("success\n");
						return;
					}
					if(ptr == parent->right){
						parent->right = ptr->left;
						free(ptr);
						printf("success\n");
						return;
					}else{
						parent->left = ptr->left;
						free(ptr);
						printf("success\n");
						return;
					}
				}
			}
		}
	}
	printf("fail\n");
}

int main(int argc, char** argv){
	FILE* fp;
	fp = fopen(argv[1],"r");
	if(fp == NULL){
		printf("error\n");
		exit(0);
	}
	char op;
	int num;
	while(fscanf(fp,"%c\t%d\n", &op, & num) != EOF){
		if(op == 'i'){
			Treenode* newNode = (Treenode*) malloc(sizeof(Treenode));
			newNode->data = num;
			newNode->left = NULL;
			newNode->right = NULL;
			insert(newNode,num);
		}else if(op == 's'){
			search(num);
		}else if(op == 'd'){
			delete(num);
		}else{
			printf("error\n");
			exit(0);
		}
	}	
	return 0;
}
