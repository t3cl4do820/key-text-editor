/*
 * File: interface.c
 * Project: key text editor
 * Author: t3cl4do820
 * Copyright (C) 2026 Lucas Rabello (t3cl4do820)
 * SPDX-License-Identifier: GPL-3.0-only
*/

#include <stdio.h>
#include <ncurses.h>
#include <interface/interface.h>
#include <linked_list/linked_list.h>

void init_key(FILE *file)
{
	// read line by line of the file and add in Linked List
	List *list = makelist();

	char buffer[256]; 
	while (fgets(buffer, 256, file) != NULL) {
		add_line(buffer, list);
	}

	initscr();
	noecho();

	int max_lines, max_columns;
	getmaxyx(stdscr, max_lines, max_columns);
	int bar_height = 3;

	WINDOW *bar = newwin(
			bar_height,
			max_columns,
			max_lines - bar_height,
			0	
		);

	box(bar, 0, 0);

	refresh();
	wrefresh(bar);
	

	// wclrtoeol(bar); // to clear all chars of the line

	move(0, 0);
	int row= 0;
	Node *current = list->head;

	while (current != NULL) {
		mvprintw(row, 0, "%s", current->line);
		refresh();
		current = current->next;
		row++;
	}
	move(0, 0);
	wrefresh(bar);
	getch();
	endwin();
}
