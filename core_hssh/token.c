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

struct special_characters *push_spcl_ch(struct special_characters *cur, int argc)
{
	struct special_characters *spcl_ch = (struct special_characters*)malloc(sizeof(struct special_characters));
	spcl_ch->next = NULL;
	spcl_ch->pos = argc;
	if (!info->spcl_ch) {
		info->spcl_ch = spcl_ch;
	} else {
		cur->next = spcl_ch;
	}
	return spcl_ch;
}

void split(char *command)
{
	int argc = 0, pos;
	char **argv = (char**)malloc(ARGVSIZE * sizeof(char*));
	bool is_excape = FALSE;
	bool has_begun = FALSE;
	struct token *cur_token = NULL;
	struct token *header= NULL;
	int cur_token_pos = 0;
	int cur_token_size = TOKENSIZE;
	struct special_characters *cur = NULL;
	for (pos = 0; command[pos] != '\0'; pos++) {
		char ch = command[pos];
		if (!has_begun) {
			if (is_excape) {
				char *s = (char*)malloc(sizeof(char) * cur_token_size);
				s[0] = ch;
				++cur_token_pos;

				struct token *tok = init_token(s);
				++argc;
				push_token(&header, &cur_token, tok);

				has_begun = TRUE;
				is_excape = FALSE;
			} else {
				switch (ch) {
				case ' ':
				case '\t':
					break;
				case '|':
				case '>':
				case '<':
					char *s1 = (char*)malloc(sizeof(char) * 2);
					s1[0] = ch;
					s1[1] = '\0';


					struct token *tok1 = init_token(s1);
					cur = push_spcl_ch(cur, argc);
					++argc;
					push_token(&header, &cur_token, tok1);

					break;
				case '\\':
					is_excape = TRUE;
					break;
				default:
					char *s2 = (char*)malloc(sizeof(char) * cur_token_size);
					s2[0] = ch;

					struct token *tok2 = init_token(s2);
					++argc;
					push_token(&header, &cur_token, tok2);

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
						cur_token->part[cur_token_pos] = '\0';
						cur_token_pos = 0;
						has_begun = FALSE;
						break;
					case '\\':
						is_excape = TRUE;
						break;
					case '|':
					case '<':
					case '>':
						cur_token->part[cur_token_pos] = '\0';

						char *s = (char*)malloc(sizeof(char) * 2);
						s[0] = ch;
						s[1] = '\0';

						struct token *tok = init_token(s);
						cur = push_spcl_ch(cur, argc);
						++argc;
						push_token(&header, &cur_token, tok);

						cur_token_pos = 0;
						has_begun = FALSE;

						break;
					default:
						cur_token->part[cur_token_pos] = ch;
						++cur_token_pos;
				}
			}
		}
	}

	if (has_begun) {
		cur_token->part[cur_token_pos] = '\0';
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
