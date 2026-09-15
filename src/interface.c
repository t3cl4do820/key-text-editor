/*
 * File: interface.c
 * Project: key text editor
 * Author: t3cl4do820
 * Copyright (C) 2026 Lucas Rabello (t3cl4do820)
 * SPDX-License-Identifier: GPL-3.0-only
*/

#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <interface/interface.h>
#include <linked_list/linked_list.h>
#include <string.h>

#define HEAD_FILE move(0, 0)
#define CMD_SIZE 5

typedef struct Cursor {
	int num_column;
	int num_line;
	Node *current_line;
} Cursor;

// sorry about that
static int line_count = 0;

// w, q, wq, wq! only
void lookup_command(char command[CMD_SIZE])
{
	if (strcmp(command, "q") == 0) {
		endwin();
		exit(0);
	}
}

// ta dando muita merda, dps voce tenta escrever tudo dentro de uma window, acho que assim fica mais facil de manipular os elementos...
// tu vai ter que mudar a barra tbm, fazer igual a do vim

// to exit use backspace or DEL char = 127
void command_mode(WINDOW *bar)
{
	mvwprintw(bar, 1, 1, ":");
	wrefresh(bar);
	// char buffer[CMD_SIZE];

	int ch;

	// nao to conseguindo fazer a mecanica de mostrar o que foi digitado usando o getch nesse loop ai
	// preciso coletar o input (que eh uma array) usando o getch

	// while ((ch = getch())) {
		mvprintw(1, 1, "daraa");	
	// }

	// for (int i = 0; i < CMD_SIZE; i++) {
	// 	while ((ch = getch())) {
	// 		// esc, backspace, del
	// 		switch (ch) {
	// 			case 27: // esc 
	// 				break;
	//
	// 			case 127: // del
	//
	// 				break;
	//
	// 			case 8: // backspace
	//
	// 				break;
	//
	// 			case 13: // parse the command
	// 				lookup_command(buffer);
	// 				break;
	//
	// 			default:
	// 				buffer[i] = ch;
	// 				break;
	// 		}			
	// 	}
	// }
}

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
	
	// wclrtoeol(bar); // to clear all chars of the line (for dd)

	HEAD_FILE;
	int row= 0;
	Node *current = list->head;

	// print all lines
	while (current != NULL) {
		mvprintw(row, 0, "%s", current->line);
		refresh();
		row++;
		current = current->next;
		line_count++;
	}
	current = list->head; // again
	HEAD_FILE;
	wrefresh(bar);

	// init the cursor
	Cursor *current_cursor = malloc(sizeof(Cursor));
	current_cursor->num_column = 0;
	current_cursor->num_line = 0;
	current_cursor->current_line = list->head;


	// the cursor move a column forward because the NULL char btw
	int max_col;
	while (1) {
		int ch = getch();
		if (ch == 'q') break;

		switch (ch) {
			case 'l':
				if (current_cursor->num_column == current_cursor->current_line->size_line -1) continue;
				current_cursor->num_column++;
				move(current_cursor->num_line, current_cursor->num_column);
				break;
			case 'h':
				if (current_cursor->num_column == 0) continue;
				current_cursor->num_column--;
				move(current_cursor->num_line, current_cursor->num_column);
				break;
			case 'j':
				if (current_cursor->num_line == line_count - 2) continue;
				current_cursor->current_line = current_cursor->current_line->next;
				current_cursor->num_line++;

				max_col = current_cursor->current_line->size_line - 1;
				if (max_col < 0) max_col = 0;
				if (current_cursor->num_column > max_col)
					current_cursor->num_column = max_col;
				move(current_cursor->num_line, current_cursor->num_column);
				break;
			case 'k':
				if (current_cursor->num_line == 0) continue;
				current_cursor->current_line = current_cursor->current_line->previous;
				current_cursor->num_line--;

				max_col = current_cursor->current_line->size_line - 1;
				if (max_col < 0) max_col = 0;
				if (current_cursor->num_column > max_col)
					current_cursor->num_column = max_col;
				move(current_cursor->num_line, current_cursor->num_column);
				break;
			case ':':
				command_mode(bar);
				break;
		}

	}
	endwin();
}


