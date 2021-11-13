/*
 * Filename: ../ls/ls.c
 * Auther: Zhang Wenda <vaaandark@foxmail.com>
 * Creation time: 2021-11-03 23:15:37
 * Latest change: 2021-11-13 21:32:13
 * License: GPL-2.0
 * etc: ls命令的参数应该是由一个长整型各个bit位来存储，目前如果直接实现 -a -l
 * 会导致之后的拓展性不强
 */

#include "../include/ls.h"

void print_dir (DIR *dir) {
	struct dirent *file;
	while ((file = readdir(dir))) {
		if (file->d_name[0] != '.') {
			printf("%s  ", file->d_name);
		}
	}
	printf("\n");
}

int main(int argc, char *argv[])
{
	DIR *dir;
	if (argc == 1) {
		dir = opendir(".");
		print_dir(dir);
	} else if (argc == 2) {
		if (argv[1][0] == '-') {
		}
		dir = opendir(argv[1]);
		if (!dir) {
			printf("ls: cannot access \'%s\': No such file or directory\n");
			return(1);
		}
		print_dir(dir);
	} else {
		int i;
		for (i = 1; i < argc; i++) {
			dir = opendir(argv[i]);
			if (!dir) {
				printf("ls: cannot access \'%s\': No such file or directory\n");
				continue;
			}
			printf("%s:\n", argv[i]);
			print_dir(dir);
		}
	}
	if (dir) {
		closedir(dir);
	}
	return(0);
}