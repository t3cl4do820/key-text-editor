/*
 * File: key.c
 * Project: key text editor
 * Author: t3cl4do820
*/

#include <stdio.h>
#include <string.h> // for strlen()
#include <ncurses.h>
#include "include/interface/interface.h"
#include "include/utils/utils.h"

void init_key_old(char *argv);

void init_new_key();

int main(int argc, char **argv)
{
	if (argc < 2){
		printf("DEBUUUG \n");
		return 1;
	}

	char *content = open_file(argv[1]);
	for (int i = 0; i < strlen(content); i++) {	
		 printf("%c", content[i]);
	}

	printf("\n");
	return 0;
}



void init_key_old(char *argv)
{

	if (argv == NULL)
	{

	}

	char buffer[1024] = {0};

	FILE *file = fopen(&argv[1], "r");

	fread(buffer, 1024, 1, file);

	initscr();
	
	printw("%s", buffer);

	while(1) {
		int c = getch();
		if (c == 'q') 
			break;
	}

	endwin();

	fclose(file);
	return;
}

void init_new_key()
{
	initscr();
	while(1){
		int c = getch();
		if(c == 'q'){
			break;
		}
	}

	endwin();
}
