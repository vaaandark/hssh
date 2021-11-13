/*
 * Filename: echo/extra_echo.c
 * Auther: Zhang Wenda <vaaandark@foxmail.com>
 * Creation time: 2021-11-13 16:54:45
 * Latest change: 2021-11-13 16:54:45
 * License: GPL-2.0
 */

#include <stdio.h>

int main(int argc, char *argv[])
{
	if (argc == 1) {
		puts("\n");
		return 0;
	}
	int i;
	for (i = 1; i < argc - 1; ++i) {
		printf("%s ", argv[i]);
	}
	printf("%s\n", argv[i]);
	return 0;
}