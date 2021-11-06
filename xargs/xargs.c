/*
 * Filename: xargs/xargs.c
 * Auther: Zhang Wenda <vaaandark@foxmail.com>
 * Creation time: 2021-11-06 13:41:31
 * Latest change: 2021-11-06 13:41:31
 * License: GPL-2.0
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define MAXARGUAMENTNUM 16
#define MAXARGUAMENTSIZE 16

typedef unsigned int bool;
#define TRUE 1
#define FALSE 0

int main(int argc, char *argv[])
{
	int arg_num = MAXARGUAMENTNUM;
	int arg_size = MAXARGUAMENTSIZE;
	char **new_argv = (char**)malloc(sizeof(char*) * (arg_num + argc));
	int i;
	for (i = 0; i < argc; ++i) {
		new_argv[i] = argv[i];
	}
	char ch = getchar();
	
	bool has_begun = FALSE;
	int token_pos = i;
	int pos = 0;
	while (ch != '\0') {
		if (has_begun) {
			switch (ch) {
			case ' ':
			case '\t':
			case '\n':
				new_argv[token_pos][pos] = '\0';
				int arg_size = MAXARGUAMENTSIZE;
				has_begun = FALSE;
				pos = 0;
				break;
			default:
				if (pos + 1 == arg_size) {
					arg_size += MAXARGUAMENTSIZE;
					new_argv[token_pos] = realloc(new_argv[token_pos], sizeof(arg_size));
				}
				new_argv[token_pos][pos] = ch;
				++pos;
				break;
			}
		} else {
			switch (ch) {
			case ' ':
			case '\t':
			case '\n':
				break;
			default:
				char *token = (char*)malloc(sizeof(char) * arg_size);
				token[0] = ch;
				if (arg_num + argc == 1 + token_pos) {
					arg_num += MAXARGUAMENTNUM;
					new_argv = realloc(new_argv, sizeof(char*) * (arg_num + argc));
				}
				new_argv[token_pos] = token;
				++token_pos;
				++pos;
				break;
			}
		}
		ch = getchar();
	}
	new_argv[token_pos + 1] = NULL;
	execvp(new_argv[1], new_argv + 1);
	for (i = argc; i < arg_num + argc; ++i) {
		free(new_argv[i]);
	}
	free(new_argv);
	return 0;
}
