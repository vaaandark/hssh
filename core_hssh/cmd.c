/*
 * Filename: cmd.c
 * Auther: Zhang Wenda <vaaandark@foxmail.com>
 * Creation time: 2021-11-01 21:20:37
 * Latest change: 2021-11-04 10:04:00
 * License: GPL-2.0
 * Description: the implementation of executing the commands 
 */

#include "../include/cmd.h"

void exec_command(int argc, char *argv[])
{
	int i;
	if (argv[0][0] == EOF) {
		hssh_exit();
		printf("\n");
	} else if (strcmp(argv[0], "exit") == 0) {
		hssh_exit();
	} else if (strcmp(argv[0], "pwd") == 0) {
		hssh_pwd();
	} else if (strcmp(argv[0], "echo") == 0) {
		hssh_echo(argc, info->argv);
	} else if (strcmp(argv[0], "cd") == 0) {
		hssh_cd(argc, info->argv);
	}
}
