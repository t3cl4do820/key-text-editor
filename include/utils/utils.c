/*
 * File: utils.c
 * Project: key text editor
 * Author: t3cl4do820
 */
#include <stdio.h>
#include "./utils.h"

char buffer[256] = {0};

char* open_file(char *name)
{
	FILE *file = fopen(name, "r");
	
	fread(buffer, 256, 1, file);

	// printf("Content: %s \n", buffer);

	return buffer;
}
