/*
 * File: linked_list.h
 * Project: key text editor
 * Author: t3cl4do820
*/

#ifndef LINKED_LIST_H
#define LINKED_LIST_H

typedef struct Node {
	char *line;
	int size;
	struct Node *next;
} Node;

typedef struct List {
	Node *head;
} List;

void add_line(char *line, List *list);

List* make_list();

Node* makenode(char *line);

void destroy_list(List *list);

void delete_line(char *line, List *list);

#endif
