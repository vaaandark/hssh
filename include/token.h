/*
 * Filename: ../include/token.h
 * Auther: Zhang Wenda <vaaandark@foxmail.com>
 * Creation time: 2021-11-02 15:23:01
 * Latest change: 2021-11-03 18:15:01
 * License: GPL-2.0
 */

#ifndef TOKEN_H_
#define TOKEN_H_

#include "hssh.h"

extern struct hssh_info *info;
extern char *PS1;

struct token {
	char *part;
	struct token* next;
};

void push_token(struct token **header, struct token **cur_token, struct token *new_token);

struct redirct_symbol *push_redir_symbl(struct redirct_symbol *redir_cur, int argc, char ch);

struct pipe_symbol *push_pipe_symbl(struct pipe_symbol *pipe_cur, int argc);

struct token *init_token(char *p);

void split(char *command);

#endif /* TOKEN_H_ */
