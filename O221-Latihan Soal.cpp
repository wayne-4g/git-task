#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Data {
	char name[30];
	int age;
	char desc[100];
	char code[10];
	Data *next;
	Data *prev;
}*head = NULL, *tail = NULL;

Data *createNewNode (char name[30], int age, char desc[100], char code[10]) {
	Data *newNode = (Data*) malloc (sizeof(Data));
	
	strcpy (newNode->name, name);
	newNode->age = age;
	strcpy (newNode->desc, desc);
	strcpy (newNode->code, code);
	
	newNode->next = NULL;
	newNode->prev = NULL;
	
	return newNode;
}

void pushHead (Data *newNode) {
	if (head == NULL) {
		head = tail = newNode;
	} else {
		newNode->next = head;
		head->prev = newNode;
		head = newNode;
	}
}

void pushTail (Data *newNode) {
	if (tail == NULL) {
		head = tail = newNode;
	} else {
		newNode->prev = tail;
		tail->next = newNode;
		tail = newNode;
	}
}

void pushRed (Data *newNode) {
	Data *curr = head;
	
	if (head == NULL) {
		head = tail = newNode;
	} else {
		while (curr != NULL && (strcmp(curr->code, "Green") != 0 && strcmp(curr->code, "Yellow") != 0)) {
			curr = curr->next;
		}
		
		if (curr != NULL) {
			if (curr == head) {
				pushHead (newNode);
			} else {
				newNode->next = curr;
				newNode->prev = curr->prev;
				curr->prev->next = newNode;
				curr->prev = newNode;
			}
		} else {
			pushTail (newNode);
		}
	}
}

void pushYellow (Data *newNode) {
	Data *curr = head;
	
	if (head == NULL) {
		head = tail = newNode;
	} else {
		while (curr != NULL && strcmp(curr->code, "Green") != 0) {
			curr = curr->next;
		}
		
		if (curr != NULL) {
			if (curr == head) {
				pushHead (newNode);
			} else {
				newNode->next = curr;
				newNode->prev = curr->prev;
				curr->prev->next = newNode;
				curr->prev = newNode;
			}
		} else {
			pushTail (newNode);
		}
	}
}

void insert (Data *newNode, char code[10]) {
	if (strcmp (code, "Red") == 0) {
		pushRed (newNode);
	} else if (strcmp (code, "Yellow") == 0) {
		pushYellow (newNode);
	} else if (strcmp (code, "Green") == 0) {
		pushTail (newNode);
	}
}

void nextQueue () {
	Data *curr = head;
	
	if (head == NULL) {
		printf ("There is no queue yet!\n");
		printf ("Press Enter to continue...\n"); getchar();
		return;
	}
	
	printf ("The next patient is:\n");
	printf ("%-14s: Mr. %s\n", "Name", head->name);
	printf ("%-14s: %d\n", "Age", head->age);
	printf ("%-14s: %s\n", "Description", head->desc);
	printf ("%-14s: %s\n", "Code", head->code);
	
	printf ("Press Enter to continue..."); getchar();
	
	if (head == tail) {
		free(curr);
		head = tail = NULL;
	} else {
		head = curr->next;
		head->prev = NULL;
		curr->next = NULL;
		free(curr);
	}
}

void view () {
	Data *curr = head;
	int i = 1;
	
	printf ("Patient List:\n");
	printf ("-------------------------------------------------------------------------------------------------------------\n");
	printf ("|%-4s| %-26s| %-5s| %-56s| %-8s|\n", "No", "Name", "Age", "Description", "Code");
	printf ("-------------------------------------------------------------------------------------------------------------\n");
	
	while (curr != NULL) {
		printf ("|%-4d| %-26s| %-5d| %-56s| %-8s|\n", i, curr->name, curr->age, curr->desc, curr->code);
		i++;
		curr = curr->next;
	}
	
	printf ("Press Enter to continue ..."); getchar();
}

void menu () {
	int select, age;
	char name[30], desc[100], code[10];
	
	printf ("Bluejack Hospital\n");
	printf ("=================\n");
	printf ("1. Insert\n");
	printf ("2. View\n");
	printf ("3. Next Queue\n");
	printf ("4. Exit\n");
	printf (">> ");
	
	scanf ("%d", &select); getchar();
	
	switch (select) {
		case 1:
			do {
				printf ("Input patient name[4-25]: ");
				scanf ("%[^\n]", name); getchar();
			} while (strlen (name) < 4 || strlen (name) > 25);
			
			do {
				printf ("Input patient age[>= 0]: ");
				scanf ("%d", &age); getchar();
			} while (age < 0);
			
			do {
				printf ("Input description[>= 6 characters]: ");
				scanf ("%[^\n]", desc); getchar();
			} while (strlen (desc) < 6);
			
			do {
				printf ("Input code[Red|Yellow|Green]: ");
				scanf ("%s", code); getchar();
			} while (strcmp (code, "Red") != 0 && strcmp (code, "Yellow") != 0 && strcmp (code, "Green") != 0);
			
			insert (createNewNode (name, age, desc, code), code);
			
			printf ("\nInsert success!"); getchar();
			
			system ("cls");
			menu();
		case 2:
			view ();
			system ("cls");
			menu();
		case 3:
			nextQueue ();
			system ("cls");
			menu();
		case 4:
			exit(0);
	}
}

int main () {
	
	menu();
	
	return (0);
}
