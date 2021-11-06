/*
 * Filename: cmd.c
 * Auther: Zhang Wenda <vaaandark@foxmail.com>
 * Creation time: 2021-11-01 21:20:37
 * Latest change: 2021-11-04 10:04:00
 * License: GPL-2.0
 * Description: the implementation of executing the commands 
 */

#include "../include/cmd.h"

bool exec_built_in_command(int argc, char *argv[])
{
	if (strcmp(argv[0], "exit") == 0) {
		hssh_exit();
	} else if (strcmp(argv[0], "pwd") == 0) {
		hssh_pwd();
	} else if (strcmp(argv[0], "echo") == 0) {
		hssh_echo(argc, argv);
	} else if (strcmp(argv[0], "cd") == 0) {
		hssh_cd(argc, argv);
	} else {
		return FALSE;
	}
	return TRUE;
}

void exec_external_command(int argc, char *argv[])
{
	char **aargv = (char**)malloc(sizeof(char*) * (argc + 1));
	int i;
	for (i = 0; i < argc; ++i) {
		aargv[i] = argv[i];
	}
	aargv[i] = NULL;
	execvp(aargv[0], aargv);
	free(aargv);
}

void another_line(int fuck_num)
{
	puts("\n");
}