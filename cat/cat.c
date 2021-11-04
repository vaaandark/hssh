/*
 * Filename: cat/cat.c
 * Auther: Zhang Wenda <vaaandark@foxmail.com>
 * Creation time: 2021-11-04 23:34:36
 * Latest change: 2021-11-04 23:34:36
 * License: GPL-2.0
 */

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	if(argc == 1) {
		return(1);
	}
	int i;
	for (i = 1; i < argc; ++i) {
		FILE *file = NULL;
		file = fopen(argv[i], "r");
		if (!file) {
			printf("cat: %s: No such file or directory\n", argv[i]);
			continue;
		}

		char buff[256];
		while (fgets(buff, 256, file)) {
			printf("%s", buff);
		}
		fclose(file);
	}
	return(0);
}
