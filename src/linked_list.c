/*
 * File: linked_list.c
 * Project: key text editor
 * Author: t3cl4do820
 * Copyright (C) 2026 Lucas Rabello (t3cl4do820)
 * SPDX-License-Identifier: GPL-3.0-only
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <linked_list/linked_list.h>

void add_line(char *line, List *list)
{
	Node *current = NULL;
	if (list->head == NULL) {
		list->head = makenode(line);
	} else {
		current = list->head;
		while (current->next != NULL) {
			current = current->next;
		}
		current->next = makenode(line);
	}
}

void delete_line(char *line, List *list)
{
	Node *current = list->head;
	Node *previous = NULL;
	while (current != NULL) {
		if (strcmp(current->line, line) == 0) {
			if (previous == NULL) {
				list->head = current->next;
			} else {
				previous->next = current->next;
			}
			free(current);
			return;
		}
		previous = current;
	}
}

List* makelist()
{
	List *list = malloc(sizeof(List));
	if (list == NULL) {
		perror("Error to use malloc in 'makelist' function.");
		exit(1);
	}
	list->head = NULL;
	return list;
}

Node* makenode(char *line)
{
	Node *node = malloc(sizeof(Node));
	if (node == NULL) {
		perror("Error to use malloc in 'makenode' function.");
		exit(1);
	}
	node->line = line;
	node->line_count++;
	node->next = NULL;
	return node;
}

void destroy_list(List *list)
{
	Node *current = list->head;
	Node *next = current;
	while (current != NULL) {
		next = current->next;
		free(current);
		current = next;
	}
	free(list);
}
