/*
 * Filename: ../include/cmd.h
 * Auther: Zhang Wenda <vaaandark@foxmail.com>
 * Creation time: 2021-11-01 21:20:37
 * Latest change: 2021-11-01 21:20:37
 * License: GPL-2.0
 * Description: the header file of executing the commands
 */

#ifndef CMD_H_
#define CMD_H_

#include <string.h>
#include <stdio.h>
#include "echo.h"
#include "exit.h"
#include "pwd.h"
#include "cd.h"
#include "ls.h"

extern struct hssh_info *info;

void exec_command(int argc, char *argv[]);

#endif /* CMD_H_ */
