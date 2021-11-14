/*
 * Filename: get_input.c
 * Auther: Zhang Wenda <vaaandark@foxmail.com>
 * Creation time: 2021-11-01 18:36:08
 * Latest change: 2021-11-13 10:07:20
 * License: GPL-2.0
 */

#include "../include/call_cmd.h"
#include "../include/token.h"

struct hssh_info *info;
bool is_exit;
char *command;
char *PS1;

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
		free(command);
		command = NULL;
		struct single_command *single_cmd = info->single_cmd;
		exec_command_with_pipes(single_cmd);
		free_memory_of_cmds();
		
	}
	return 0;
}
