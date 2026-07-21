/*
 * File: key.c
 * Project: key text editor
 * Author: t3cl4do820
 * Copyright (C) 2026 Lucas Rabello (t3cl4do820)
 * SPDX-License-Identifier: GPL-3.0-only 
*/

#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <interface/interface.h>

int main(int argc, char **argv)
{
	if (argc > 2){
		// open key without text loaded..
		return EXIT_FAILURE; // lol
	}

	FILE *file = fopen(argv[1], "r");

	printf("%s \n", argv[1]);

	if (file == NULL) {
		printf("Cant open the file %s \n", argv[1]);
		return EXIT_FAILURE;
	}

	printf("before function \n"	);
	init_key(file);
	printf("after function \n");

	return 0;
}
