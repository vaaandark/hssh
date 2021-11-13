/*
 * Filename: get_input.c
 * Auther: Zhang Wenda <vaaandark@foxmail.com>
 * Creation time: 2021-11-01 18:36:08
 * Latest change: 2021-11-13 10:07:20
 * License: GPL-2.0
 */

#include "../include/cmd.h"
#include "../include/token.h"

struct hssh_info *info;
bool is_exit;
bool is_signal;
bool back_ground;
char *command;
char *PS1;

void exec_single_command(struct single_command single_cmd, bool must_fork);
void exec_command_with_pipes(struct single_command *single_cmd);
void free_memory();

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
		} else if (strlen(command) == 0) {
			free(command);
			command = NULL;
			continue;
		}
		struct tokens tok = split_by_pipe(command);
		info->single_command_num = tok.splited_command_num;
		info->single_cmd = split_single_command(tok);
		if (strcmp(tok.splited_command[tok.token_num - 2], "&") == 0) {
			back_ground = TRUE;
		}
		struct single_command *ssingle_cmd = info->single_cmd;
		free(command);
		command = NULL;
		struct single_command *single_cmd = info->single_cmd;
		exec_command_with_pipes(single_cmd);
		free_memory();
		
	}
	return 0;
}

void exec_single_command(struct single_command single_cmd, bool must_fork)
{
	struct redirct_symbol *redir_symbl = single_cmd.redir_symbl;
	int out_bak = dup(fileno(stdout));
	int in_bak = dup(fileno(stdin));
	while (redir_symbl) {
		if (redir_symbl->type == OUTPUT) {
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
	if (must_fork) {
		pid_t child = fork();
		if (child == 0) {
			signal(SIGINT, SIG_DFL);
			exec_command(single_cmd.argc, single_cmd.argv);
			exit(1);
		} else  {
			signal(SIGINT, another_line);
			wait(NULL);
		}
	} else {
		if (exec_built_in_command(single_cmd.argc, single_cmd.argv) == FALSE) {
			exec_external_command(single_cmd.argc, single_cmd.argv);
		}
	}

	dup2(out_bak, fileno(stdout));
	close(out_bak);
	dup2(in_bak, fileno(stdin));
	close(in_bak);
}

void exec_command_with_pipes(struct single_command *single_cmd)
{
	int input_bak = dup(fileno(stdin));
	int output_bak = dup(fileno(stdout));

	pid_t child;

	int fdin = dup(fileno(stdin)), fdout;
	while (single_cmd) {
		dup2(fdin, fileno(stdin));
		close(fdin);

		bool is_last = (!single_cmd->next) ? TRUE : FALSE;
		if (is_last) {
			fdout = dup(output_bak);
		} else {
			int fdspipe[2];
			pipe(fdspipe);
			fdout = fdspipe[1];
			fdin = fdspipe[0];
		}

		dup2(fdout, fileno(stdout));
		close(fdout);

		if (is_last) {
			exec_single_command(*single_cmd, FALSE);
			if (back_ground) {
				int status;
				waitpid(child, &status, 0);
			}
		} else {
			child = fork();
			if (child == 0) {
				bool must_fork = (single_cmd->next) ? TRUE : FALSE;
				exec_single_command(*single_cmd, must_fork);
				exit(1);
			} else {
				signal(SIGINT, another_line);
				wait(NULL);		
			}
		}

		single_cmd = single_cmd->next;
	}
	
	dup2(input_bak, fileno(stdin));
	close(input_bak);
	dup2(output_bak, fileno(stdout));
	close(output_bak);

}

void free_memory()
{
	struct single_command *single_cmd = info->single_cmd;
	while (single_cmd) {
		struct single_command *del = single_cmd;
		single_cmd = single_cmd->next;
		int i;
		for (i = 0; i < del->argc; ++i) {
			if (del->argv[i]) {
				free(del->argv[i]);
			}
		}
		struct redirct_symbol *redir_symbl = del->redir_symbl;
		while (redir_symbl) {
			free(redir_symbl->opt_file_name);
			redir_symbl = redir_symbl->next;
		}
		free(del);
	}
}
