/*
 * Filename: ../include/token.h
 * Auther: Zhang Wenda <vaaandark@foxmail.com>
 * Creation time: 2021-11-02 15:23:01
 * Latest change: 2021-11-13 00:46:55
 * License: GPL-2.0
 */

#ifndef TOKEN_H_
#define TOKEN_H_

#include "hssh.h"

extern struct hssh_info *info;
extern char *PS1;

struct tokens {
	char **splited_command;
	int splited_command_num;
	int token_num;
};

struct tokens split_by_pipe(char *command);

struct single_command *split_single_command(struct tokens tok);

#endif /* TOKEN_H_ */
