/*
 * Filename: rm/rm.c
 * Auther: Zhang Wenda <vaaandark@foxmail.com>
 * Creation time: 2021-11-13 21:15:55
 * Latest change: 2021-11-13 21:15:55
 * License: GPL-2.0
 */

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	if (argc == 1) {
		printf("rm: missing operand\n");
		return 1;
	}
	int i;
	for (i = 1; i < argc; ++i) {
		if (remove(argv[i]) != 0) {
			printf("rm: cannnot remove \'%s\': No such file or directory\n", argv[i]);
		}
	}
	return 0;
}
