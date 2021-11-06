/*
 * Filename: hssh.h
 * Auther: Zhang Wenda <vaaandark@foxmail.com>
 * Creation time: 2021-10-31 16:25:58
 * Latest change: 2021-11-03 20:25:58
 * License: GPL-2.0
 * Description: 
 */

#ifndef HSSH_H_
#define HSSH_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pwd.h>
#include <sys/types.h>
#include <signal.h>
#include <fcntl.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "hsshdef.h"
#include "color.h"

#define MAXUSERIDSIZE	16
#define MAXHOSTNAMESIZE	16
#define MAXPATHSIZE	64
#define MAXPROMPTSIZE 265
#define BUFFERSIZE	64
#define ARGVSIZE	4
#define TOKENSIZE	16

extern bool is_exit;
extern bool is_signal;

extern char *PS1;

enum redir_type {
	OUTPUT_REDIRECT = 0,
	INPUT_REDIRECT
};

struct pipe_symbol {
	int pos;
	struct pipe_symbol *next;
};

struct redirct_symbol {
	int pos;
	struct redirct_symbol *next;
	enum redir_type type;
	char *opt_file_name;
};


struct hssh_info {
	char user_id[MAXUSERIDSIZE];
	char hostname[MAXHOSTNAMESIZE];
	char work_dir[MAXPATHSIZE];
	char home_dir[MAXPATHSIZE];
	char **argv;
	char argc;
	struct pipe_symbol *pipe_symbl;
	struct redirct_symbol *redir_symbl;
};

struct env_path {
	char *path;
	struct env_path *next;
};


extern struct hssh_info *info;

void hssh_init(void);

void hssh_update(void);

extern struct env_path *env_path_header;

void get_env();

void get_env_path(FILE env_file);

#endif /* HSSH_H_ */
