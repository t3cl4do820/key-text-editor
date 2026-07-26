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
		printf("add lines: %s", buffer);
	}

	initscr();
	noecho();

	int max_lines, max_columns;
	getmaxyx(stdscr, max_lines, max_columns);

	int window_height = 30;
	int window_width = 40;
	int lines_mid = (max_lines - window_height) / 2;
	int columns_mid = (max_columns- window_width) / 2;

	WINDOW *window = newwin(
			window_height,
			window_width,
			lines_mid,
			columns_mid	
		);

	box(window, 0, 0);
	mvwprintw(window, 1, 1, "key text editor");
	refresh();
	wrefresh(window);
	
	getch();
	endwin();
}
