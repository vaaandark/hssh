/*
 * Filename: echo.c
 * Auther: Zhang Wenda <vaaandark@foxmail.com>
 * Creation time: 2021-11-01 00:15:45
 * Latest change: 2021-11-03 20:10:45
 * License: GPL-2.0
 * Description: 
 */

#include "../include/echo.h"

void hssh_echo(int argc, char *argv[])
{
	if (argc == 1) {
		puts("\n");
		return;
	}
	int i;
	for (i = 1; i < argc - 1; ++i) {
		printf("%s ", argv[i]);
	}
	printf("%s\n", argv[i]);
}