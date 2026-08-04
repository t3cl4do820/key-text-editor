/*
 * File: utils.c
 * Project: key text editor
 * Author: t3cl4do820
 * Copyright (C) 2026 Lucas Rabello (t3cl4do820)
 * SPDX-License-Identifier: GPL-3.0-only
*/
#include <stdio.h>
#include <stdlib.h>
#include <linked_list/linked_list.h>
#include <utils/utils.h>

#define MAX_LINE_SIZE 256

char buffer[MAX_LINE_SIZE] = {0};

FILE* open_file(char *name_file)
{
	FILE *file_fd = fopen(name_file, "r");
	if (file_fd == NULL) {
		printf("Error to open the file %s\n", name_file); 
		exit(EXIT_FAILURE);
	}
	return file_fd;
}
