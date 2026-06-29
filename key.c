/*
 * File: key.c
 * Project: key text editor
 * Author: t3cl4do820
*/

#include <stdio.h>
#include <ncurses.h>

int main(int argc, char **argv)
{
	if (argc < 2){
		printf("You need specify the file to open it. \n");
		return 1;
	}
	
	char buffer[1024] = {0};

	FILE *file = fopen(argv[1], "r"); // r -> read file

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
	return 0;
}

