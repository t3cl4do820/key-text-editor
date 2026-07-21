/*
 * File: linked_list.h
 * Project: key text editor
 * Author: t3cl4do820
 * Copyright (C) 2026 Lucas Rabello (t3cl4do820)
 * SPDX-License-Identifier: GPL-3.0-only
*/

#ifndef LINKED_LIST_H
#define LINKED_LIST_H

typedef struct Node {
	char *line;
	int line_count;
	struct Node *next;
} Node;

typedef struct List {
	Node *head;
} List;

void add_line(char *line, List *list);

List* makelist();

Node* makenode(char *line);

void destroy_list(List *list);

void delete_line(char *line, List *list);

#endif
