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

struct token {
	char *part;
	struct token* next;
};

void push_token(struct token **header, struct token **cur_token, struct token *new_token);

struct special_characters *push_spcl_ch(struct special_characters *cur, int argc);

struct token *init_token(char *p);

void split(char *command);

#endif /* TOKEN_H_ */
