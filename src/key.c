/*
 * File: key.c
 * Project: key text editor
 * Author: t3cl4do820
 * Copyright (C) 2026 Lucas Rabello (t3cl4do820)
 * SPDX-License-Identifier: GPL-3.0-only 
*/

#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <linked_list.h>

typedef struct Cursor {
	int x, y;
	Node *current_line;
} Cursor;

int main(int argc, char **argv)
{
	struct termios old_term, new_term;

	if (tcgetattr(STDOUT_FILENO, &old_term) == -1) {
		fprintf(stderr, "Error to save the old terminal configs \n");
		return -1;
	}
	
	new_term = old_term;

	/* Enable Raw Mode */
	new_term.c_lflag &= ~(ECHO | ICANON);

	tcsetattr(STDOUT_FILENO, 0, &new_term);

	return 0;
}
