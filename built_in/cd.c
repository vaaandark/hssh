/*
 * Filename: ../built_in/cd.c
 * Auther: Zhang Wenda <vaaandark@foxmail.com>
 * Creation time: 2021-11-02 13:03:01
 * Latest change: 2021-11-02 13:03:01
 * License: GPL-2.0
 */

#include "../include/cd.h"

void hssh_cd(int argc, char *argv[])
{
	if (argc > 2) {
		printf("cd: too many arguments\n");
	} else if (argc == 2) {
		int ret = chdir(argv[1]);
		if (ret != 0) {
			printf("cd: no such file or directory: %s\n", argv[1]);
		}
	} else {
		chdir(info->home_dir);
	}
}
