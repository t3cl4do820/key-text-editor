/*
 * File: key.c
 * Project: key text editor
 * Author: t3cl4do820
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h> // for strlen()
#include <ncurses.h>
#include <interface/interface.h>

void init_new_key();

int main(int argc, char **argv)
{
	if (argc < 2){
		// open key without text loaded..
		return EXIT_FAILURE; // lol
	}

	return 0;
}
