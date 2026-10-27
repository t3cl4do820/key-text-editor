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

#define VERSION "0.0.1"

struct TermConfig {
	int rows, columns;
};

struct Cursor {
	int num_line, num_column;
	Node *current_line;
};

static int read_only = 0;
static struct termios old_term, new_term;
static int line_count = 0;
static struct TermConfig t;
static int editor_empty = 0; /* remove this */

static void parse_flags(int argc, const char **argv);
static void enable_raw_mode(struct termios *term);
static struct TermConfig set_terminal_config(void);
static void editor_process_key(List *list);
static void help(void);
static void init_editor(void);
static void editor_open(const char *file_name, List *list);
static void editor_open_empty(List *list);
static void exit_and_restore_t(void);
static void move_cursor(int line, int column);

void move_cursor(int line, int column)
{
	char ansi_code[32];
	int len = snprintf(ansi_code, sizeof(ansi_code), "\x1b[%d;%dH", line, column);
	if (len > 0) {
		write(STDOUT_FILENO, ansi_code, (size_t)len);
	}
}

/* for errors */
void exit_and_restore_t()
{
	tcsetattr(STDOUT_FILENO, TCSANOW, &old_term);
	exit(1);
}

void parse_flags(int argc, const char **argv)
{
	char flag[] = "";
	int flag_exist = 0;
	for (int i = 1; i < argc; i++) {
		if (argv[i][0] != '-')
			continue;

		if (strcmp(argv[i], "--help") == 0 || strcmp(argv[i], "-h") == 0) {
			help();
			exit(0);
		}
		if (strcmp(argv[i], "--version") == 0 || strcmp(argv[i], "-v") == 0) {
			printf("Key version: %s \nBy t3cl4do820 \n", VERSION);
			exit(0);
		}
		if (strcmp(argv[i], "--read-only") == 0 || strcmp(argv[i], "-r") == 0) {
			read_only = 1;
			return;
		}
		flag_exist = 1;
		strcpy(flag, argv[i]);
	}
	if (flag_exist == 1) {
		fprintf(stderr, "Flag: %s not found! \n", flag);
		exit(1);
	}
	return;
}

void enable_raw_mode(struct termios *term)
{
	term->c_iflag &= ~(ICRNL | IXON | BRKINT | INPCK | ISTRIP); 
	term->c_oflag &= ~(OPOST);
	term->c_cflag |= (CS8);
	term->c_lflag &= ~(ECHO | ICANON | ISIG | IEXTEN);
	term->c_cc[VMIN] = 1; /* read() only can read one byte */
	term->c_cc[VTIME] = 0; /* wait for a byte to read it */
}

struct TermConfig set_terminal_config(void)
{
	struct winsize ws;
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws);
	return (struct TermConfig) {
		.rows = ws.ws_row,
		.columns = ws.ws_col,
	};
}

void editor_process_key(List *list)
{
	int num_line = 0, num_column = 0;
	struct Cursor *current_cursor = malloc(sizeof(struct Cursor));
	current_cursor->num_line = num_line;
	current_cursor->num_column = num_column;
	current_cursor->current_line = list->head;

	/* read char */
	/* notes: 1-based (+1 in move_cursor function) */
	char c;
	int max_col;
	while (1) {
		read(STDIN_FILENO, &c, 1);
		switch (c) {
			case 'q':
				write(STDOUT_FILENO, "\x1b[?1049l", 8); /* Back to the window */

				/* exit */
				if (tcsetattr(STDIN_FILENO, TCSANOW, &old_term) == -1) {	
					fprintf(stderr, "Error to restore the terminal configs \n");
					exit_and_restore_t();
				}
				exit(0);
				break;
			case 'l':
				if (editor_empty == 1) continue; /* remove this */
				if (current_cursor->num_column == current_cursor->current_line->size_line -1) continue;
				current_cursor->num_column++;
				// write(STDOUT_FILENO, "\x1b[1C", 4);
				move_cursor(current_cursor->num_line + 1, current_cursor->num_column + 1);
				break;
			case 'h':
				if (current_cursor->num_column == 0) continue;
				current_cursor->num_column--;
				// write(STDOUT_FILENO, "\x1b[1D", 4);
				move_cursor(current_cursor->num_line + 1, current_cursor->num_column + 1);
				break;
			case 'j':
				if (editor_empty == 1) continue; /* remove this */
				if (current_cursor->num_line == line_count - 2) continue;
				// if (current_cursor->current_line->next == NULL) continue;
				current_cursor->current_line = current_cursor->current_line->next;
				current_cursor->num_line++;
	
				max_col = current_cursor->current_line->size_line - 1;
				if (max_col < 0) max_col = 0;
				if (current_cursor->num_column > max_col)
					current_cursor->num_column = max_col;
				// write(STDOUT_FILENO, "\x1b[1B", 4);
				move_cursor(current_cursor->num_line + 1, current_cursor->num_column + 1);
				break;
			case 'k':
				if (current_cursor->num_line == 0) continue;
				current_cursor->current_line = current_cursor->current_line->previous;
				current_cursor->num_line--;

				max_col = current_cursor->current_line->size_line - 1;
				if (max_col < 0) max_col = 0;
				if (current_cursor->num_column > max_col)
					current_cursor->num_column = max_col;
				// write(STDOUT_FILENO, "\x1b[1A", 4);
				move_cursor(current_cursor->num_line + 1, current_cursor->num_column + 1);
				break;
			case ':':

				break;
			default:
				write(STDOUT_FILENO, &c, sizeof(char)); /* print the char */
		}
	}
}

void help()
{
	puts(
		"Key text editor by t3cl4do820 \n\n"
		"Flags: \n"
			"\t--help      | -h => This message \n"
			"\t--version   | -v => See key version \n"
			"\t--read-only | -r => Open a file to read only \n"
		);
}

/* set configs */
void init_editor()
{
	if (tcgetattr(STDIN_FILENO, &old_term) == -1) {
		fprintf(stderr, "Error to save the old terminal configs \n");
		exit_and_restore_t();
	}
	
	new_term = old_term;

	enable_raw_mode(&new_term);
	
	t = set_terminal_config();
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &new_term);

	/* Draw the Window */
	write(STDOUT_FILENO, "\x1b[?1049h", 8); /* Enter in alternative buffer */

	write(STDOUT_FILENO, "\x1b[1;1H", 6); /* Move the cursor */
}

void editor_open(const char *file_name, List *list)
{
	FILE *fp = fopen(file_name, "r");
	if (fp == NULL) {
		fprintf(stderr,
				"Error to open the file: %s \nIn function %s At line: %d",
				file_name, __func__, __LINE__);
		exit_and_restore_t();
	}

	/* read the file content and add in linked list */

	char buffer[256]; /* 256 bytes by line */
	while (fgets(buffer, 256, fp) != NULL) {
		add_line(buffer, list);
	}
	fclose(fp);

	Node *current = list->head;
	while (current != NULL) {
		write(STDOUT_FILENO, current->line, current->size_line);
		write(STDOUT_FILENO, "\r", 1);
		current = current->next;
		line_count++;
	}
	current = list->head; /* back to head */

	write(STDOUT_FILENO, "\x1b[1;1H", 6);

	editor_process_key(list);
}

void editor_open_empty(List *list)
{
	editor_empty = 1; /* remove this */
	editor_process_key(list);
}


int main(int argc, char **argv)
{
	parse_flags(argc, (const char **)argv);
	init_editor(); /* set the configs */
	List *list = makelist();
	if (argc >= 2) {
		editor_open(argv[1], list);
		return 0;
	}

	editor_open_empty(list);

	return 0;
}
