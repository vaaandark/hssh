/*
 * Filename: get_input.c
 * Auther: Zhang Wenda <vaaandark@foxmail.com>
 * Creation time: 2021-11-01 18:36:08
 * Latest change: 2021-11-05 00:07:20
 * License: GPL-2.0
 */

#include "../include/cmd.h"
#include "../include/token.h"

struct hssh_info *info;
bool is_exit;
bool is_signal;
char *command;
char *PS1;

void free_mem(void);

int main(void)
{
	hssh_init();
	while (is_exit == FALSE) {
		hssh_update();
		command = readline(PS1);
		add_history(command);
		if (!command) {
			printf("exit\n");
			break;
		}
		split(command);
		free(command);
		command = NULL;
		// int i;
		// for (i = 0; i < info->argc; ++i) {
		// 	printf("%s\n", info->argv[i]);
		// }
		// struct redirct_symbol *re = info->redir_symbl;
		// while (re) {
		// 	printf("重定向，位置为第%d个，文件为%s\n", re->pos, re->opt_file_name);
		// 	re = re->next;
		// }
		// struct pipe_symbol *pp = info->pipe_symbl;
		// while (pp) {
		// 	printf("管道符，位置为第%d个\n", pp->pos);
		// 	pp = pp->next;
		// }

		struct redirct_symbol *redir_symbl = info->redir_symbl;
		int out_bak = dup(fileno(stdout));
		int in_bak = dup(fileno(stdin));
		while (redir_symbl) {
			if (redir_symbl->type == OUTPUT_REDIRECT) {
				int fd = open(redir_symbl->opt_file_name, O_CREAT | O_WRONLY, 0644);
				dup2(fd, fileno(stdout));
				close(fd);
			} else {
				int fd = open(redir_symbl->opt_file_name, O_RDONLY);
				if (fd < 0) {
					printf("hssh: no such file or directory: %s\n", redir_symbl->opt_file_name);
					break;
				}
				dup2(fd, fileno(stdin));
				close(fd);
			}
			redir_symbl = redir_symbl->next;
		}

		if (!info->pipe_symbl) {
			if (!exec_built_in_command(info->argc, info->argv)) {
				/* if the command is not the built-in command */
				pid_t child = fork();
				if (child == 0) {
					signal(SIGINT, SIG_DFL);
					exec_external_command(info->argc, info->argv);
					hssh_exit();
				} else  {
					signal(SIGINT, another_line);
					wait(NULL);
				}
			}
		}
		while (info->pipe_symbl) {
			int fds[2];
			pipe(fds);
			if (!info->pipe_symbl->next) {

			} else {

			}
		}

		dup2(out_bak, fileno(stdout));
		close(out_bak);
		dup2(in_bak, fileno(stdin));
		close(in_bak);

		free_mem();
		
	}
	return 0;
}

void free_mem(void)
{
	if (command) {
		free(command);
	}
	int i;
	for (i = 0; i < info->argc; ++i) {
		free(info->argv[i]);
	}
	if (info->argv) {
		free(info->argv);
		info->argv = NULL;
	}
	while (info->pipe_symbl) {
		struct pipe_symbol *del_pipe = info->pipe_symbl;
		info->pipe_symbl = info->pipe_symbl->next;
		free(del_pipe);
	}
	info->pipe_symbl = NULL;
	while (info->redir_symbl) {
		struct redirct_symbol *del_redir = info->redir_symbl;
		info->redir_symbl = info->redir_symbl->next;
		free(del_redir->opt_file_name);
		free(del_redir);
	}
	info->redir_symbl = NULL;
}