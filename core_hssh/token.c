/*
 * Filename: token.c
 * Auther: Zhang Wenda <vaaandark@foxmail.com>
 * Creation time: 2021-11-02 15:22:55
 * Latest change: 2021-11-13 00:25:15
 * License: GPL-2.0
 */

#include "../include/token.h"

struct tokens split_by_pipe(char *command)
{
	int tokennum = TOKENNUM;
	int tokensize = tokensize;
	char **splited_command = (char**)malloc(sizeof(char*) * tokennum);
	int cur_token_pos = 0;
	int cur_char_pos = 0;
	int splited_command_num = 0;
	bool has_begun = FALSE;
	bool is_escape = FALSE;
	int i;
	for (i = 0; command[i] != '\0'; ++i) {
		char ch = command[i];
		/* 如果一个词未开始输入 */
		if (has_begun == FALSE) {
			/* 如果这个字符被转义了 */
			if (is_escape == TRUE) {
				char *tok = (char*)malloc(sizeof(char) * tokensize);
				tok[0] = ch;
				splited_command[cur_token_pos] = tok;
				++cur_char_pos;
				has_begun = TRUE;

				is_escape = FALSE;
			} else {
				switch (ch) {
				case ' ':
				case '\t':
					break;
				case '\\':
					is_escape = TRUE;
					break;
				/* 管道符号，向字符串数组中添加一个空指针 */
				case '|':
					splited_command[cur_token_pos] = NULL;
					++cur_token_pos;
					++splited_command_num;
					break;
				case '>':
				case '<':
					has_begun = FALSE;

					char *token = (char*)malloc(sizeof(char) * 2);
					token[0] = ch;
					token[1] = '\0';
					splited_command[cur_token_pos] = token;

					++cur_token_pos;

					break;
				default:
					char *tok = (char*)malloc(sizeof(char) * tokensize);
					tok[0] = ch;
					splited_command[cur_token_pos] = tok;
					has_begun = TRUE;

					++cur_char_pos;
					break;
				}
			}
		/* 如果一个词已经开始输入 */		
		} else {
			/* 如果这个字符被转义了 */
			if (is_escape == TRUE) {
				splited_command[cur_token_pos][cur_char_pos] = ch;
				++cur_char_pos;
				is_escape = FALSE;
			} else {
				switch (ch) {
				/* 空白字符，代表这个词的输入已经结束 */
				case ' ':
				case '\t':
					splited_command[cur_token_pos][cur_char_pos] = '\0';
					cur_char_pos = 0;
					// printf("遇到空白字符，当前词的输入结束，当前词为: %s\n", splited_command[cur_token_pos]);
					++cur_token_pos;
					has_begun = FALSE;
					break;
				/* 管道符号，代表这个词和这小段部分的命令的输入已经结束 */
				case '|':
					/* 先结束当前词 */
					splited_command[cur_token_pos][cur_char_pos] = '\0';
					cur_char_pos = 0;
					++cur_token_pos;
					has_begun = FALSE;
					
					/* 再添加一个空指针 */
					splited_command[cur_token_pos] = NULL;
					++cur_token_pos;

					++splited_command_num;

					break;
				case '>':
				case '<':
					splited_command[cur_token_pos][cur_char_pos] = '\0';
					cur_char_pos = 0;
					++cur_token_pos;
					has_begun = FALSE;

					char *tok = (char*)malloc(sizeof(char) * 2);
					tok[0] = ch;
					tok[1] = '\0';
					splited_command[cur_token_pos] = tok;

					++cur_token_pos;

					break;
				case '\\':
					is_escape = TRUE;
					break;
				default:
					splited_command[cur_token_pos][cur_char_pos] = ch;
					++cur_char_pos;
					break;
				}
			}
		}
	}

	/* 如果一个词还没有终止符就已经结束 */
	if (has_begun == TRUE) {
		splited_command[cur_token_pos][cur_char_pos] = '\0';
		has_begun = FALSE;
		++cur_token_pos;
	}

	splited_command[cur_token_pos] = NULL;
	++splited_command_num;
	++cur_token_pos;
	
	struct tokens tok = {
		.splited_command = splited_command,
		.splited_command_num = splited_command_num,
		.token_num = cur_token_pos
	};

	return tok;
}

struct single_command *split_single_command(struct tokens tok)
{
	struct single_command *head_single_cmd = NULL;
	struct single_command *cur_single_cmd = NULL;
	int i = 0;
	for (; i < tok.token_num; ++i) {
		struct single_command *new_single_cmd = (struct single_command*)malloc(sizeof(struct single_command));
		new_single_cmd->argv = (char**)malloc(sizeof(char*) * TOKENNUM);
		new_single_cmd->redir_symbl = NULL;
		struct redirct_symbol *cur_redir_symbl = NULL;
		int k = 0;
		for (; tok.splited_command[i] != NULL; ++i) {
			if (strcmp(tok.splited_command[i], "<") == 0) {
				struct redirct_symbol *new_redir_symbl = (struct redirct_symbol*)malloc(sizeof(struct redirct_symbol));
				new_redir_symbl->opt_file_name = strdup(tok.splited_command[++i]);
				new_redir_symbl->type = INPUT;
				new_redir_symbl->next = NULL;
				if (cur_redir_symbl == NULL) {
					new_single_cmd->redir_symbl = cur_redir_symbl = new_redir_symbl;
				} else {
					cur_redir_symbl->next = new_redir_symbl;
					cur_redir_symbl = new_redir_symbl;
				}
			} else if (strcmp(tok.splited_command[i], ">") == 0) {
				struct redirct_symbol *new_redir_symbl = (struct redirct_symbol*)malloc(sizeof(struct redirct_symbol));
				new_redir_symbl->opt_file_name = strdup(tok.splited_command[++i]);
				new_redir_symbl->type = OUTPUT;
				new_redir_symbl->next = NULL;
				if (cur_redir_symbl == NULL) {
					new_single_cmd->redir_symbl = cur_redir_symbl = new_redir_symbl;
				} else {
					cur_redir_symbl->next = new_redir_symbl;
					cur_redir_symbl = new_redir_symbl;
				}
			} else {
				new_single_cmd->argv[k] = strdup(tok.splited_command[i]);
				++k;
			}
		}
		new_single_cmd->argc = k;
		new_single_cmd->next = NULL;
		if (cur_single_cmd == NULL) {
			head_single_cmd = cur_single_cmd = new_single_cmd;
		} else {
			cur_single_cmd->next = new_single_cmd;
			cur_single_cmd = new_single_cmd;
		}
	}

	/* 释放内存空间 */
	for (i = 0; i < tok.token_num; ++i) {
		if (tok.splited_command[i] != NULL) {
			free(tok.splited_command[i]);
		}
	}

	return head_single_cmd;
}