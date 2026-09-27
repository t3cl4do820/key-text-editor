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
#include <sys/ioctl.h>
#include <linked_list.h>

typedef struct Cursor {
	int x, y;
	Node *current_line;
} Cursor;

int main(int argc, char **argv)
{
	struct termios old_term, new_term;

	if (tcgetattr(STDIN_FILENO, &old_term) == -1) {
		fprintf(stderr, "Error to save the old terminal configs \n");
		return -1;
	}
	
	new_term = old_term;

	/* Enable Raw Mode */
	new_term.c_lflag &= ~(ECHO | ICANON);
	new_term.c_cc[VMIN] = 1; /* read() only can read one byte */
	new_term.c_cc[VTIME] = 0; /* wait for a byte to read it */

	/* Size of terminal */
	struct winsize ws;
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws);

	int rows = ws.ws_row;
	int col = ws.ws_col;

	tcsetattr(STDIN_FILENO, TCSAFLUSH, &new_term);

	/* Draw the Window */
	write(STDOUT_FILENO, "\x1b[2J", 4); /* Clear the window */

	write(STDOUT_FILENO, "\x1b[1;1H", 6); /* Move the cursor */

	/* read some thing */
	char c;
	read(STDIN_FILENO, &c, 1);

	/* Exit */
	if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &old_term) == -1) {	
		fprintf(stderr, "Error to restore the terminal configs \n");
		return -1;
	}

	printf("%c \n", c);

	return 0;
}
