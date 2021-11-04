/*
 * Filename: get_input.c
 * Auther: Zhang Wenda <vaaandark@foxmail.com>
 * Creation time: 2021-11-01 20:36:18
 * Latest change: 2021-11-01 20:36:18
 * License: GPL-2.0
 * Description: the implementation of getting the input from stdin
 */

#include "../include/get_input.h"

char *get_input(int buffer_size)
{
	char *command = (char*)malloc(sizeof(char) * buffer_size);

	char c = getchar();
	if (c == EOF) {
		command[0] = c;
		return command;
	} else {
		command[0] = c;
	}
	int pos = 1;
	for (;;pos++) {
		c = getchar();

		switch (c) {
		case '\n':
			command[pos] = '\0';
			return command;
		case EOF:
			command[pos] = '\0';
			break;
		default:
			command[pos] = c;
		}

		if (pos + 1 >= buffer_size) {
			buffer_size *= 2;
			command = realloc(command, buffer_size);
		}
	}
}
