/*
 * Filename: built_in/kill.c
 * Auther: Zhang Wenda <vaaandark@foxmail.com>
 * Creation time: 2021-11-13 10:04:01
 * Latest change: 2021-11-13 10:04:01
 * License: GPL-2.0
 */

#include "../include/kill.h"

void hssh_kill(int argc, char *argv[])
{
	if (argc < 2) {
		printf("kill: not enough arguments\n");
		return;
	}
	int i;
	for (i = 1; i < argc; ++i) {
		int status = kill(atoi(argv[i]), SIGKILL);
		if (status != 0) {
			printf("kill: kill error\n");
		}
	}
}