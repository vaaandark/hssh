/*
 * Filename: token.c
 * Auther: Zhang Wenda <vaaandark@foxmail.com>
 * Creation time: 2021-11-02 15:22:55
 * Latest change: 2021-11-03 18:13:15
 * License: GPL-2.0
 */

#include "../include/token.h"

struct token *init_token(char *p)
{
	struct token *t = (struct token*)malloc(sizeof(struct token)); 
	t->part = p;
	t->next = NULL;
	return t;
}

void push_token(struct token **header, struct token **cur_token, struct token *new_token)
{
	if (*cur_token) {
		(*cur_token)->next = new_token;
		(*cur_token) = new_token;
	} else {
		*cur_token = new_token;
		if (!(*header)) {
			*header = new_token;
		}
	}
}

struct redirct_symbol *push_redir_symbl(struct redirct_symbol *redir_cur, int argc, char ch)
{
	struct redirct_symbol *redir_symbl = (struct redirct_symbol*)malloc(sizeof(struct redirct_symbol));
	redir_symbl->next = NULL;
	redir_symbl->pos = argc;
	switch (ch) {
	case '>':
		redir_symbl->type = OUTPUT_REDIRECT;
		break;
	case '<':
		redir_symbl->type = INPUT_REDIRECT;
		break;
	default:
		break;
	}
	if (!info->redir_symbl) {
		info->redir_symbl = redir_symbl;
	} else {
		redir_cur->next = redir_symbl;
	}
	return redir_symbl;
}

struct pipe_symbol *push_pipe_symbl(struct pipe_symbol *pipe_cur, int argc)
{
	struct pipe_symbol *pipe_symbl = (struct pipe_symbol*)malloc(sizeof(struct pipe_symbol));
	pipe_symbl->next = NULL;
	pipe_symbl->pos = argc;
	if (!info->pipe_symbl) {
		info->pipe_symbl = pipe_symbl;
	} else {
		pipe_cur->next = pipe_symbl;
	}
	return pipe_symbl;
}

void split(char *command)
{
	int argc = 0, pos;
	char **argv = (char**)malloc(ARGVSIZE * sizeof(char*));
	bool is_excape = FALSE;
	bool has_begun = FALSE;
	bool is_redirct = FALSE;
	struct token *cur_token = NULL;
	struct token *header= NULL;
	int cur_token_pos = 0;
	int cur_token_size = TOKENSIZE;
	struct pipe_symbol *pipe_cur = NULL;
	struct redirct_symbol *redir_cur = NULL;
	for (pos = 0; command[pos] != '\0'; ++pos) {
		char ch = command[pos];
		if (!has_begun) {
			if (is_excape) {
				char *s = (char*)malloc(sizeof(char) * cur_token_size);
				s[0] = ch;
				++cur_token_pos;

				if (is_redirct) {
					redir_cur->opt_file_name = s;
				} else {
					struct token *tok = init_token(s);
					++argc;
					push_token(&header, &cur_token, tok);
				}

				has_begun = TRUE;
				is_excape = FALSE;
			} else {
				switch (ch) {
				case ' ':
				case '\t':
					break;
				case '|':
					pipe_cur = push_pipe_symbl(pipe_cur, argc);
					break;
				case '>':
				case '<':
					redir_cur = push_redir_symbl(redir_cur, argc, ch);
					is_redirct = TRUE;
					break;
				case '\\':
					is_excape = TRUE;
					break;
				default:
					char *s = (char*)malloc(sizeof(char) * cur_token_size);
					s[0] = ch;
					if (is_redirct) {
						redir_cur->opt_file_name = s;
					} else {
						struct token *tok = init_token(s);
						++argc;
						push_token(&header, &cur_token, tok);
					}

					has_begun = TRUE;
					++cur_token_pos;
					break;
				}
			}
		} else {
			if (pos >= cur_token_size - 1) {
				cur_token_size += TOKENSIZE;
				cur_token->part = realloc(cur_token->part, cur_token_size * sizeof(char));
			}
			if (is_excape) {
				cur_token->part[cur_token_pos] = ch;
				++cur_token_pos;
				is_excape = FALSE;
			} else {
				switch (ch) {
					case ' ':
					case '\t':
						if (is_redirct) {
							redir_cur->opt_file_name[cur_token_pos] = '\0';
							is_redirct = FALSE;
						} else {
							cur_token->part[cur_token_pos] = '\0';
						}
						cur_token_pos = 0;
						has_begun = FALSE;
						break;
					case '\\':
						is_excape = TRUE;
						break;
					case '|':
						if (is_redirct) {
							redir_cur->opt_file_name[cur_token_pos] = '\0';
							is_redirct = FALSE;
						} else {
							cur_token->part[cur_token_pos] = '\0';
						}

						pipe_cur = push_pipe_symbl(pipe_cur, argc);

						cur_token_pos = 0;
						has_begun = FALSE;

						break;
					case '<':
					case '>':
						if (is_redirct) {
							redir_cur->opt_file_name[cur_token_pos] = '\0';
						} else {
							cur_token->part[cur_token_pos] = '\0';
						}

						redir_cur = push_redir_symbl(redir_cur, argc, ch);

						cur_token_pos = 0;
						has_begun = FALSE;

						is_redirct = TRUE;

						break;
					default:
						if (is_redirct) {
							redir_cur->opt_file_name[cur_token_pos] = ch;
						} else {
							cur_token->part[cur_token_pos] = ch;
						}
						++cur_token_pos;
				}
			}
		}
	}

	if (has_begun) {
		if (is_redirct) {
			redir_cur->opt_file_name[cur_token_pos] = '\0';
		} else {
			cur_token->part[cur_token_pos] = '\0';
		}
	}


	info->argc = argc;
	info->argv = (char**)malloc(sizeof(char*) * argc);
	
	int i;
	for (i = 0; i < argc; i++) {
		info->argv[i] = header->part;
		struct token *del = header;
		header = header->next;
		free(del);
	}
}
