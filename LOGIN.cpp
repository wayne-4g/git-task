#include <stdlib.h>
#include <stdio.h>


struct node{
	int number;
	node *next;
	node *prev;
}*head = NULL, *tail = NULL;


struct node *createnode(int number){
	struct node *newnode = (node*)malloc(sizeof(node));
	newnode->number = number;
	newnode->next = NULL;
	newnode->prev = NULL;
	
	return newnode;
}

void pushhead(node *newnode){
	if(head == NULL && tail == NULL){
		head = newnode;
		tail = newnode;
	}
	else{
		newnode->next = head;
		head->prev = newnode;
		
		head = newnode;
	}
}

void pushtail(node *newnode){
	if(head == NULL){
		head = tail = newnode;
	}
	else{
		tail->next = newnode;
		newnode->prev = tail;
		
		tail = newnode;
	}
}


void pushbefore(node *newnode, int target){
	node *curr = head;
	if(head == NULL){
		head = tail = newnode;
	}
	else{
		while(curr != NULL && curr->number != target){
			curr = curr->next;
		}
		if(curr != NULL){
			if(curr == head){
				pushhead(newnode);
			}
		else{
			newnode->next = curr;
			newnode->prev = curr->prev;
			curr->prev->next = newnode;
			curr->prev = newnode;
			}
		}
		else{
			printf("Number before is not found\n");
		}
	}
}

void pushafter(node *newnode, int target){
	node *curr = head;
	if(head == NULL){
		head = tail = newnode;
	}
	else{
		while(curr != NULL && curr->number != target){
			curr = curr->next;
		}
		if(curr != NULL){
			if(curr == tail){
				pushtail(newnode);
			}
			else{
				newnode->next = curr->next;
				newnode->prev = curr;
				curr->next->prev = newnode;
				curr->next = newnode;
			}
		}
		
	}
}

void pop(int target){
	node *curr = head;
	if(head == tail == target){
		free(curr);
		head = tail = NULL;
	}
	else{
		while(curr != NULL && curr->number != target){
			curr = curr->next;
		}
		if(curr != NULL){
			if(curr == head){
				head = curr->next;
				curr->next = NULL;
				free(curr);
				head->prev = NULL;				
			}
			else if(curr == tail){
				tail = curr->prev;
				curr->prev = NULL;
				free(curr);
				tail->next = NULL;
			}
			else{
				curr->prev->next = curr->next;
				curr->next->prev = curr->prev;
				curr->next = NULL;
				curr->prev = NULL;
				free(curr);
			}
		}
		else{
			printf("Target Not Found!\n");
			getchar();
		}
	}
}

void print(){
	node *curr = head;
	while(curr != NULL){
		if(curr == head){
			printf("NULL<-[%d]->", curr);
		}
		else if(curr == tail){
			printf("<-[%d]->NULL", curr);
		}
		else{
			printf("<-[%d]->", curr);
		}
	}
}
void menu(){
	int select;
	int number;
	printf("1. Push Head\n");
	printf("2. Push Tail\n");
	printf("1. Push Before\n");
	printf("1. Push After\n");
	scanf("%d", &select);
	switch(select){
		case 1:
			scanf("%d", &number);
			getchar();
			pushhead(createnode(number));
			break;
	}
	
	
}
int main(){
	
	
	
	return 0;
}
