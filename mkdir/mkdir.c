/*
 * Filename: mkdir/mkdir.c
 * Auther: Zhang Wenda <vaaandark@foxmail.com>
 * Creation time: 2021-11-04 23:53:22
 * Latest change: 2021-11-04 23:53:22
 * License: GPL-2.0
 */

#include <sys/stat.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
	if (argc == 1) {
		printf("mkdir: missing operand\n");
		return 1;
	}
	int i;
	for (i = 1; i < argc; i++) {
		int res = mkdir(argv[i], 0777);
		if (res == -1) {
			printf("mkdir: cannot create directory \'%s\': File exists\n", argv[i]);
		}
	}
	return 0;
}