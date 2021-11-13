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
#define MAXARGUAMENTSIZE 32

typedef unsigned int bool;
#define TRUE 1
#define FALSE 0

int main(int argc, char *argv[])
{
	int arg_num = MAXARGUAMENTNUM;
	int arg_size = MAXARGUAMENTSIZE;
	char **new_argv = (char**)malloc(sizeof(char*) * (arg_num + argc - 1));
	int i;
	for (i = 1; i < argc; ++i) {
		new_argv[i - 1] = argv[i];
	}
	--i;
	char ch;
	bool has_begun = FALSE;
	int token_pos = i;
	int pos = 0;
	while ((ch= getchar()) != '\n') {
		if (has_begun) {
			switch (ch) {
			case ' ':
			case '\t':
				new_argv[token_pos][pos] = '\0';
				arg_size = MAXARGUAMENTSIZE;
				has_begun = FALSE;
				pos = 0;
				++token_pos;
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
				break;
			default:
				char *token = (char*)malloc(sizeof(char) * arg_size);
				token[0] = ch;
				if (arg_num + argc == 1 + token_pos) {
					arg_num += MAXARGUAMENTNUM;
					new_argv = realloc(new_argv, sizeof(char*) * (arg_num + argc));
				}
				new_argv[token_pos] = token;
				has_begun = TRUE;
				++pos;
				break;
			}
		}
	}
	// for (i = 0; new_argv[i] != NULL; ++i) {
	// 	printf("第%d条命令是: %s\n", i, new_argv[i]);
	// }
	new_argv[token_pos + 1] = NULL;
	execvp(new_argv[0], new_argv);
	for (i = argc - 1; i < arg_num + argc - 1; ++i) {
		free(new_argv[i]);
	}
	free(new_argv);
	return 0;
}
