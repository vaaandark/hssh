/*
 * Filename: ../touch/touch.c
 * Auther: Zhang Wenda <vaaandark@foxmail.com>
 * Creation time: 2021-11-04 23:44:45
 * Latest change: 2021-11-04 23:44:45
 * License: GPL-2.0
 */

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	if(argc == 1) {
		printf("touch: missing file operand\n");
		return(1);
	}
	int i;
	for (i = 1; i < argc; ++i) {
		FILE *file = NULL;
		file = fopen(argv[i], "w");
		if (!file) {
			printf("touch: %s: can not creat\n", argv[i]);
			continue;
		}
		fclose(file);
	}
	return(0);
}

