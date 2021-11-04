/*
 * Filename: ../include/ls.h
 * Auther: Zhang Wenda <vaaandark@foxmail.com>
 * Creation time: 2021-11-03 23:15:45
 * Latest change: 2021-11-03 23:15:45
 * License: GPL-2.0
 */

#ifndef LS_H_
#define LS_H_

#include <stdio.h>
#include <dirent.h>
#include <unistd.h>

void print_dir (DIR *dir);

void hssh_ls(int argc, char *argv[]);

#endif /* LS_H_ */