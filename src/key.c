/*
 * File: key.c
 * Project: key text editor
 * Author: t3cl4do820
 * Copyright (C) 2026 Lucas Rabello (t3cl4do820)
 * SPDX-License-Identifier: MIT
*/

#include <asm-generic/ioctls.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linked_list.h>

static int read_only = 0;

struct TermConfig {
	int rows, columns;
};

static struct termios old_term, new_term;

struct Cursor {
	int x, y;
	Node *current_line;
};

static void enable_raw_mode(struct termios *term)
{
	term->c_iflag &= ~(ICRNL | IXON | BRKINT | INPCK | ISTRIP); 
	term->c_oflag &= ~(OPOST);
	term->c_cflag |= (CS8);
	term->c_lflag &= ~(ECHO | ICANON | ISIG | IEXTEN);
	term->c_cc[VMIN] = 1; /* read() only can read one byte */
	term->c_cc[VTIME] = 0; /* wait for a byte to read it */
}

static struct TermConfig set_terminal_config(void)
{
	struct winsize ws;
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws);
	return (struct TermConfig) {
		.rows = ws.ws_row,
		.columns = ws.ws_col,
	};
}

static void editor_process_key()
{
	/* read something */
	char c;
	while (1) {
		read(STDIN_FILENO, &c, 1);
		switch (c) {
			case 'q':
				write(STDOUT_FILENO, "\x1b[?1049l", 8); /* Back to the window */

				/* exit */
				if (tcsetattr(STDIN_FILENO, TCSANOW, &old_term) == -1) {	
					fprintf(stderr, "Error to restore the terminal configs \n");
					exit(1);
				}
				exit(0);
				break;
			default:
				write(STDOUT_FILENO, &c, sizeof(char));
		}
	}
}

static void help()
{
	printf(
		""
		);
}

/* int for errors */
static void init_editor()
{
	if (tcgetattr(STDIN_FILENO, &old_term) == -1) {
		fprintf(stderr, "Error to save the old terminal configs \n");
		exit(1);
	}
	
	new_term = old_term;

	enable_raw_mode(&new_term);
	
	struct TermConfig t = set_terminal_config();
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &new_term);

	/* Draw the Window */
	write(STDOUT_FILENO, "\x1b[?1049h", 8); /* Enter in alternative buffer */

	write(STDOUT_FILENO, "\x1b[1;1H", 6); /* Move the cursor */

	editor_process_key();
}

static void editor_open(const char *file_name)
{

}

static void editor_open_empty(void)
{

}


int main(int argc, char **argv)
{
	if (strcmp(argv[1], "--help") == 0 || strcmp(argv[1], "-h") == 0) {
		help();
		return 0;
	}
	init_editor(); /* set the configs */
	if (argc >= 2) {
		editor_open(argv[1]);
		return 0;
	}

	editor_open_empty();

	return 0;
}
