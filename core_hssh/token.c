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

struct special_characters *push_spcl_ch(struct special_characters *cur, int argc, char ch)
{
	struct special_characters *spcl_ch = (struct special_characters*)malloc(sizeof(struct special_characters));
	spcl_ch->next = NULL;
	spcl_ch->pos = argc;
	if (!info->spcl_ch) {
		info->spcl_ch = spcl_ch;
	} else {
		cur->next = spcl_ch;
	}
	switch (ch) {
	case '|':
		spcl_ch->ch_type = PIPE;
		break;
	case '>':
		spcl_ch->ch_type = OUTPUT_REDIRECT;
		break;
	case '<':
		spcl_ch->ch_type = INPUT_REDIRECT;
		break;
	default:
		break;
	}
	return spcl_ch;
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
	struct special_characters *cur = NULL;
	for (pos = 0; command[pos] != '\0'; pos++) {
		char ch = command[pos];
		if (!has_begun) {
			if (is_excape) {
				char *s = (char*)malloc(sizeof(char) * cur_token_size);
				s[0] = ch;
				++cur_token_pos;

				if (is_redirct) {
					cur->opt_file_name = s;
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
					cur = push_spcl_ch(cur, argc, ch);
					has_begun = FALSE;
					break;
				case '>':
				case '<':
					cur = push_spcl_ch(cur, argc, ch);
					is_redirct = TRUE;
					has_begun = FALSE;
					break;
				case '\\':
					is_excape = TRUE;
					break;
				default:
					char *s = (char*)malloc(sizeof(char) * cur_token_size);
					s[0] = ch;
					if (is_redirct) {
						cur->opt_file_name = s;
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
							cur->opt_file_name[cur_token_pos] = '\0';
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
						cur_token->part[cur_token_pos] = '\0';

						cur = push_spcl_ch(cur, argc, ch);

						cur_token_pos = 0;
						has_begun = FALSE;

						break;
					case '<':
					case '>':
						cur_token->part[cur_token_pos] = '\0';

						cur = push_spcl_ch(cur, argc, ch);

						cur_token_pos = 0;
						has_begun = FALSE;

						is_redirct = TRUE;

						break;
					default:
						if (is_redirct) {
							cur->opt_file_name[cur_token_pos] = ch;
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
			cur->opt_file_name[cur_token_pos] = '\0';
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
